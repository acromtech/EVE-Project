#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"
#include "wrapperPFR.h"

ResListToSend remplir_table_score_test(){
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

	ResListToSend resListToSend;
	startBus();									//Démarre le bus
	resListToSend=remplir_table_score_test(); 	//Traitement du moteur de recherche (Dans le cas du test on ne fait que remplir la structure avec des valeurs indicatrices)
	sendAllResBus(resListToSend);				//Envoi tous les resultats sur le bus
	return 0;
}
