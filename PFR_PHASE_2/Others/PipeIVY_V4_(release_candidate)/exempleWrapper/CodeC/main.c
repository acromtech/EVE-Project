#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"
#include "wrapperPFR.h"

#define ATTENTE_REQUETE 	0x01
#define TRAITEMENT 			0x02
#define ENVOI_RESULTATS 	0x03

ResListToSend filList(){
    ResListToSend resListToSend;
	resListToSend.score=100;
    resListToSend.chemin="./test1";
    resListToSend.next = malloc(sizeof(ResListToSend));
    resListToSend.next->score=89;
    resListToSend.next->chemin="./test2";
    resListToSend.next->next = malloc(sizeof(ResListToSend));
    resListToSend.next->next->score=70;
    resListToSend.next->next->chemin="./test3";
    resListToSend.next->next->next = malloc(sizeof(ResListToSend));
    resListToSend.next->next->next->score=56;
    resListToSend.next->next->next->chemin="./test4";
    resListToSend.next->next->next->next = malloc(sizeof(ResListToSend));
    resListToSend.next->next->next->next->score=52;
    resListToSend.next->next->next->next->chemin="./test5";
    resListToSend.next->next->next->next->next = NULL;
	return resListToSend;
}

int main(int argc, char**argv){

	masterId=atoi(argv[1]);		//ATTENTION : NE PAS OUBLIER DE RECUPERER LES ID
	motorId=atoi(argv[2]);		//ATTENTION : NE PAS OUBLIER DE RECUPERER LES ID

	ResListToSend resListToSend;
	char etat=ATTENTE_REQUETE;
	int boucle=1;
	
	startBus();

	while(boucle){
		switch(etat){
		case ATTENTE_REQUETE:
			sleep(1);
			if(typeTraitement!=-1) etat=TRAITEMENT;
			break;

		case TRAITEMENT:
			switch (typeTraitement){
			
			//Indexation
			case INDEXATION_ALL:
				//appel de la fonction d'indexation
				break;
			case INDEXATION_TEXTE:
				//appel de la fonction d'indexation
				break;
			case INDEXATION_IMAGE:
				//appel de la fonction d'indexation
				break;
			case INDEXATION_SON:
				//appel de la fonction d'indexation
				break;

			//Recherche
			case TEXTE_MOTCLE:
				//appel de la fonction de texte
				resListToSend=filList();
				break;
			case IMAGE_FICHIER:
				//appel de la fonction image
				resListToSend=filList();
				break;
			case SON_FICHIER:
				//appel de la fonction son
				resListToSend=filList();
				break;
			case SCORE_CHEMIN:
				sendAllResBus(resListToSend);
				break;
			case STOP_BUS:
				stopBus();
				return 0;
			
			//OpenMode
			case ADDR_OPEN_MODE:
				//appel de la fonction permettant l'activation de l'OpenMode
				break;
			
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
