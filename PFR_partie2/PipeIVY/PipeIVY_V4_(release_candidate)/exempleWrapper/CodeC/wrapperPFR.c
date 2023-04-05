#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "unistd.h"
#include "pcre.h"
#include "ivy.h"
#include "ivyloop.h"

#include "wrapperPFR.h"

int autorisation_envoie_trame=0;
char typeTraitement=-1;
char nombreResultatMax=0;
char* requete;
char masterId;
char motorId;

void* ivyThread(void* arg) {
    IvyMainLoop();
    return NULL;
}

void ack(){
	IvySendMsg("%d %d %d %d %d",masterId,motorId,typeTraitement,0xFF,0xFF);
}

void traitementEffectue(){
	IvySendMsg("%d %d %d %d %d",masterId,motorId,typeTraitement,0xFF,0xFE);
	typeTraitement=-1;
}

void callback (IvyClientPtr app, void *data, int argc, char **argv){
	typeTraitement=atoi(argv[0]);
	ack();
	if(typeTraitement==SCORE_CHEMIN){
		autorisation_envoie_trame=1;
	} else if(typeTraitement==TEXTE_FICHIER||typeTraitement==TEXTE_MOTCLE||typeTraitement==IMAGE_FICHIER||typeTraitement==IMAGE_MOTCLE||typeTraitement==SON_FICHIER){
		requete=calloc(50,sizeof(char));
		requete=argv[1];
		nombreResultatMax=atoi(argv[2]);
	}
}

void startBus(){
	//Initialisation du bus
	char* connected = calloc(50,sizeof(char));
	char* hote = calloc(1,sizeof(char));
	sprintf(connected,"%d %d %d %d %d",masterId,motorId,CONNECTED,0x00,0x00);
	sprintf(hote,"%d",motorId);
	IvyInit (hote,connected,0x00,0x00,0x00,0x00);

	//Abonnement aux différents messages motorId
	IvyBindMsg(callback,0,"^%d %d (.*) (.*) (.*)",motorId,masterId);

	//Lancement du bus espion dans un thread séparé
	IvyStart ("127.255.255.255:2010");
	pthread_t thread;
    pthread_create(&thread, NULL, ivyThread, NULL);
}

void sendAllResBus(ResListToSend resListToSend){

	//Déclaration et initialisation des variables
	int nbResSend = 0;
	ResListToSend* cpResListToSend = &resListToSend;

	//Envoie les trames si JAVA LUI DEMANDE (JAVA = Controleur)
	while(1){
		if(autorisation_envoie_trame){
			if(nbResSend<nombreResultatMax && cpResListToSend!=NULL){
				autorisation_envoie_trame=0;
				IvySendMsg("%d %d %d %d %s",masterId,motorId,SCORE_CHEMIN,cpResListToSend->score,cpResListToSend->chemin);
				cpResListToSend=cpResListToSend->next;
				nbResSend++;
			}
			else{
				traitementEffectue();
				return;
			}
		}
	}
}

void stopBus(){
	traitementEffectue();
	IvyStop();
}