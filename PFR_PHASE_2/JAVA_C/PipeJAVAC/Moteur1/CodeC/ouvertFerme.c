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
	
	startBus("127.255.255.255:2011");
	//etat = TRAITEMENT;
	//typeTraitement = SON_FICHIER;
	while(boucle){
		switch(etat){
		case ATTENTE_REQUETE:
			sleep(1);
			if(typeTraitement!=-1) etat=TRAITEMENT;
			break;

		case TRAITEMENT:
			switch (typeTraitement){
			case INDEXATION_ALL:printf("Début initialisation\n");
				supprimerDescripteur();
    			indexerBaseImage(&bdImage, &listeImage);
    			indexationBase("../../BaseFichier/Texte/", &bd, &listeDescripteur, &tableDescripteur);
				autoIndexationAudio();
				traitementEffectue();
				break;

			case SUPPRIMER_DESCRIPTEUR:
				supprimer(requete, &bd, &listeDescripteur, &tableDescripteur, &bdImage, &listeImage);
				traitementEffectue();
				break;

			case INDEXATION_IMAGEIVY:
				indexationImage(requete, &bdImage, &listeImage, bd->taille, NB_LISTE);
				traitementEffectue();
				break;

			case INDEXATION_TEXTEIVY:
				indexationTexte(requete, bd->taille, &bd, &listeDescripteur, &tableDescripteur);
				traitementEffectue();
				break;

			case SCORE_CHEMIN:
				sendAllResBus(pileRes);
				traitementEffectue();
				break;
                
			case STOP_BUS:
				stopBus();
				return 0;
			default:
				printf("\nC\tErreur : Traitement non effectué %x",typeTraitement);
				return 0;
			}
			etat=ATTENTE_REQUETE;
			break;

		default:
			printf("\nC\tErreur : Résultats non envoyés");
			return 0;
		}
	}
	return 0;
}