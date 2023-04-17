#include <stdio.h>
#include <stdlib.h>
#include "wrapperPFR.h"


#define ATTENTE_REQUETE 	0x01
#define TRAITEMENT 			0x02
#define ENVOI_RESULTATS 	0x03



void supprimer(char *name, baseDescripteur *bd, pathIdDesc *listeDescripteur, tableDescript *tableDescripteur, baseDescripteurImage *bdImage, listeDescripteurImage *listeImage){
    if(strcmp(name, "TEXTE") == 0){
        suprimerBaseMenu();
		indexationBase("../../BaseFichier/Texte/", bd, listeDescripteur, tableDescripteur);
    }
    else if (strcmp(name, "SON") == 0){
        rmDescripteurs("../FichierIndexation/Son/BaseDescripteursAudios/");
        remove("../FichierIndexation/Son/ListeDescripteursAudios.txt");
        autoIndexationAudio();
    }
    else if( strcmp(name, "IMAGE") == 0 ){
        indexerBaseImage(bdImage, listeImage);
    }
    else{
        // probleme
    }
}


descripteurEtScoreListe invertPile(descripteurEtScoreListe liste){
	descripteurEtScoreListe result = NULL;
	while(liste != NULL){
		result = empilerDescriipteurEtScore(result, liste->descripteur->path, liste->descripteur->id, liste->score);
		liste = liste->next;
	}
	return result;
}

descripteurEtScoreListeImage invertPileImage(descripteurEtScoreListeImage liste){
	descripteurEtScoreListeImage result = NULL;
	while(liste != NULL){
		result = empilerDescripteurEtScoreImage(result, liste->descripteur->path, liste->descripteur->id, liste->score);
		liste = liste->next;
	}
	return result;
}

ResListToSend* empilerResultatListe(ResListToSend* liste, char* path, int score){
    ResListToSend *tmp = calloc(1, sizeof(struct resListToSend));
    tmp->chemin = calloc(100, sizeof(char));
    tmp->score = score;
    strcpy(tmp->chemin, path);
    tmp->next = liste;
    liste = tmp;
	return tmp;
}

int main(int argc, char **argv){
	
	masterId=atoi(argv[1]);		//ATTENTION : NE PAS OUBLIER DE RECUPERER LES ID
	motorId=atoi(argv[2]);		//ATTENTION : NE PAS OUBLIER DE RECUPERER LES ID

	descripteurEtScoreListe liste_resListToSendTexte = NULL;
    descripteurEtScoreListeImage liste_resListToSendImage = NULL;
    baseDescripteurImage bdImage = initBaseDescripteurImage();
    listeDescripteurImage listeImage = initListeDescripteurImage();
    baseDescripteur bd = initBaseDescripteur();
    pathIdDesc listeDescripteur = initListeDescripteur();
    tableDescript tableDescripteur = NULL;
	resultatAudioScorePath resAudio;
	ResListToSend *pileRes = NULL;
    ResListToSend resListToSend;
    resListToSend.chemin = calloc(1, sizeof(char));
	
	char etat=ATTENTE_REQUETE;
	int boucle=1;
	
	startBus("127.255.255.255:2010");
	//etat = TRAITEMENT;
	//typeTraitement = INDEXATION_ALL;
	while(boucle){
		switch(etat){
		case ATTENTE_REQUETE:
			sleep(1);
			if(typeTraitement!=-1) etat=TRAITEMENT;
			break;

		case TRAITEMENT:
			switch (typeTraitement){
			case INDEXATION_ALL:
				supprimerDescripteur();
    			indexerBaseImage(&bdImage, &listeImage);
    			indexationBase("../../BaseFichier/Texte/", &bd, &listeDescripteur, &tableDescripteur);
				autoIndexationAudio();
				break;

			case TEXTE_MOTCLE:
				liste_resListToSendTexte = rechercheTexteMotCle(listeDescripteur, tableDescripteur, requete);
				while(liste_resListToSendTexte != NULL){
                    pileRes = empilerResultatListe(pileRes, liste_resListToSendTexte->descripteur->path, liste_resListToSendTexte->score);
					liste_resListToSendTexte = liste_resListToSendTexte->next;
                }
				break;
			
			case TEXTE_FICHIER:
				char *requeteComplete = (char*) calloc(strlen("../../BaseFichier/Texte/") + strlen(requete) + 1, sizeof(char)); // alloue de la mémoire pour la chaîne concaténée
    			sprintf(requeteComplete, "%s%s", "../../BaseFichier/Texte/", requete); // concatène les deux chaînes de caractères
				liste_resListToSendTexte = rechercheTexteCompare(bd, listeDescripteur, requeteComplete);
				
				while(liste_resListToSendTexte != NULL){
                    pileRes = empilerResultatListe(pileRes, liste_resListToSendTexte->descripteur->path, liste_resListToSendTexte->score);
					liste_resListToSendTexte = liste_resListToSendTexte->next;
                }
				break;
			
			case IMAGE_MOTCLE:
				liste_resListToSendImage = rechercheCouleur(bdImage, listeImage, requete);
				while(liste_resListToSendImage != NULL){
                    pileRes = empilerResultatListe(pileRes, liste_resListToSendImage->descripteur->path, liste_resListToSendImage->score);
					liste_resListToSendImage = liste_resListToSendImage->next;
                }
				break;

			case IMAGE_FICHIER:
				liste_resListToSendImage = rechercheHisto(bdImage, listeImage, "01");
				while(liste_resListToSendImage != NULL){
                    pileRes = empilerResultatListe(pileRes, liste_resListToSendImage->descripteur->path, liste_resListToSendImage->score);
					liste_resListToSendImage = liste_resListToSendImage->next;
                }
				break;

			case SON_FICHIER:
				resAudio = saisieRechercheAudio("jingle_fi.wav");
				break;

			case SUPPRIMER_DESCRIPTEUR:
				supprimer(requete, &bd, &listeDescripteur, &tableDescripteur, &bdImage, &listeImage);
				break;
			case INDEXATION_IMAGEIVY:
				indexationImage(requete, &bdImage, &listeImage, bd->taille, NB_LISTE);
				break;
			case INDEXATION_TEXTEIVY:
				indexationTexte(requete, bd->taille, &bd, &listeDescripteur, &tableDescripteur);
				break;
			case SCORE_CHEMIN:
				sendAllResBus(pileRes);
				pileRes = NULL;
				break;
			case STOP_BUS:
				stopBus();
				return 0;
			default:
				printf("\nC\tErreur : Traitement non effectué %x",typeTraitement);
				return 0;
			}
			traitementEffectue();
			etat=ATTENTE_REQUETE;
			break;

		default:
			printf("\nC\tErreur : Résultats non envoyés");
			return 0;
		}
	}
	return 0;
}