#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"
#include "wrapperPFR.h"

#define ATTENTE_REQUETE 'R'
#define TRAITEMENT 'T'
#define ENVOI_RESULTATS 'S'

IvyFrameBuffer remplir_table_score_test(){
    IvyFrameBuffer descScore;
	descScore.score=100;
    descScore.chemin="./test1";
    descScore.next = malloc(sizeof(IvyFrameBuffer));
    descScore.next->score=89;
    descScore.next->chemin="./test2";
    descScore.next->next = malloc(sizeof(IvyFrameBuffer));
    descScore.next->next->score=70;
    descScore.next->next->chemin="./test3";
    descScore.next->next->next = malloc(sizeof(IvyFrameBuffer));
    descScore.next->next->next->score=56;
    descScore.next->next->next->chemin="./test4";
    descScore.next->next->next->next = malloc(sizeof(IvyFrameBuffer));
    descScore.next->next->next->next->score=52;
    descScore.next->next->next->next->chemin="./test5";
    descScore.next->next->next->next->next = NULL;
	return descScore;
}

int main(int argc, char**argv){
	IvyFrameBuffer ivyFrameBuffer;
	IvyFrameBuffer* cpIvyFrameBuffer;
	char etat=ATTENTE_REQUETE;
	int boucle=1;

	startBus();
	printf("\nC\tBus ON");
	type_traitement=AUCUN;

	while(boucle){
		switch(etat){

		case ATTENTE_REQUETE:
			sleep(1);
			printf("\nC\tAttente requete");
			if(type_traitement!=AUCUN) etat=TRAITEMENT;
			break;

		case TRAITEMENT:
			switch (type_traitement){
			case MOTEUR_TEXTE:
				printf("\nC\tTraitement Texte");
				//appel de la fonction de texte
				ivyFrameBuffer=remplir_table_score_test();
				break;
			case MOTEUR_IMAGE:
				printf("\nC\tTraitement Image");
				//appel de la fonction image
				ivyFrameBuffer=remplir_table_score_test();
				break;
			case MOTEUR_SON:
				printf("\nC\tTraitement Son");
				//appel de la fonction son
				ivyFrameBuffer=remplir_table_score_test();
				break;
			default:
				printf("\nC\tErreur : Traitement non effectué");
				return 0;
			}
			etat=ENVOI_RESULTATS;
			break;

		case ENVOI_RESULTATS:
			sendAllResBus(ivyFrameBuffer);
			boucle=0;
			break;
		default:
			printf("\nC\tErreur : Résultats non envoyés");
			return 0;
		}
	}
	return 0;
}
