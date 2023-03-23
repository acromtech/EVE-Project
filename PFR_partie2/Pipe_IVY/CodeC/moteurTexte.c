#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"
#include "wrapperPFR.h"

IvyFrameBuffer remplir_table_score_test(){
    IvyFrameBuffer ivyFrameBuffer;
	ivyFrameBuffer.score=100;
    ivyFrameBuffer.chemin="./test1";
    ivyFrameBuffer.next = malloc(sizeof(IvyFrameBuffer));
    ivyFrameBuffer.next->score=89;
    ivyFrameBuffer.next->chemin="./test2";
    ivyFrameBuffer.next->next = malloc(sizeof(IvyFrameBuffer));
    ivyFrameBuffer.next->next->score=70;
    ivyFrameBuffer.next->next->chemin="./test3";
    ivyFrameBuffer.next->next->next = malloc(sizeof(IvyFrameBuffer));
    ivyFrameBuffer.next->next->next->score=56;
    ivyFrameBuffer.next->next->next->chemin="./test4";
    ivyFrameBuffer.next->next->next->next = malloc(sizeof(IvyFrameBuffer));
    ivyFrameBuffer.next->next->next->next->score=52;
    ivyFrameBuffer.next->next->next->next->chemin="./test5";
    ivyFrameBuffer.next->next->next->next->next = NULL;
	return ivyFrameBuffer;
}

int main(int argc, char**argv){

	IvyFrameBuffer ivyFrameBuffer;
	startBus();									//Démarre le bus
	ivyFrameBuffer=remplir_table_score_test(); 	//Traitement du moteur de recherche (Dans le cas du test on ne fait que remplir la structure avec des valeurs indicatrices)
	sendAllResBus(ivyFrameBuffer);				//Envoi tous les resultats sur le bus
	return 0;
}
