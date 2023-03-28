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

//IVY MAIN LOOP DANS UN THREAD SEPARE
void* ivyThread(void* arg) {
    IvyMainLoop();
    return NULL;
}

//FONCTIONS CALLBACK
void TX_Callback (IvyClientPtr app, void *data, int argc, char **argv){
	IvySendMsg("%d %d %d %d",JAVA,TX_FRAME,atoi(argv[0]),0);	//Acquitement
	typeTraitement=atoi(argv[0]);
	if(typeTraitement==TEXTE_FICHIER
	||typeTraitement==TEXTE_MOTCLE
	||typeTraitement==IMAGE_FICHIER
	||typeTraitement==IMAGE_MOTCLE
	||typeTraitement==SON_FICHIER){
		requete=calloc(50,sizeof(char));
		requete=argv[1];
		nombreResultatMax=atoi(argv[2]);
	}
	else if(typeTraitement==STOP_BUS)IvyStop();
}

void RX_Callback (IvyClientPtr app, void *data, int argc, char **argv){
	IvySendMsg("%d %d %d %d",JAVA,TX_FRAME,0,0);	//Acquitement
	typeTraitement=atoi(argv[0]);
	autorisation_envoie_trame=1;
}

//WRAPPER
/**
 * @brief Démarre le bus
 * 
 */
void startBus(){
	//Initialisation du bus
	char* connected = calloc(50,sizeof(char));
	char* hote = calloc(1,sizeof(char));
	sprintf(connected,"%d %d %d %d %d",JAVA,RX_FRAME,CONNECTED,0,0);
	sprintf(hote,"%d",C);
	IvyInit (hote,connected, 0, 0, 0, 0);

	//Abonnement aux différents messages TX ou RX
	IvyBindMsg(TX_Callback,0,"^%d %d (.*) (.*) (.*)",C,TX_FRAME);
	IvyBindMsg(RX_Callback,0,"^%d %d (.*)",C,RX_FRAME);

	//Lancement du bus espion dans un thread séparé
	IvyStart ("127.255.255.255:2010");
	pthread_t thread;
    pthread_create(&thread, NULL, ivyThread, NULL);
}

void traitementEffectue(){
	//Prévient JAVA que le C a fini le traitement
	IvySendMsg("%d %d %d %d",JAVA,TX_FRAME,typeTraitement,1);
	typeTraitement=-1;
}

/**
 * @brief Envoie la structure contenant 
 * la liste des score et leurs chemins respectifs à JAVA
 * 
 * @param ivyFrameBuffer 
 */
void sendAllResBus(ResListToSend resListToSend){

	//Déclaration et initialisation des variables
	int nbResSend = 0;
	ResListToSend* cpResListToSend = &resListToSend;

	//Envoie les trames si JAVA LUI DEMANDE (JAVA = Controleur)
	while(nbResSend<nombreResultatMax && cpResListToSend!=NULL){
		if(autorisation_envoie_trame){ //JAVA renvoi un feedback READY
			autorisation_envoie_trame=0;
			IvySendMsg("%d %d %d %d %s",JAVA,RX_FRAME,SCORE_CHEMIN,cpResListToSend->score,cpResListToSend->chemin);
			cpResListToSend=cpResListToSend->next;
			nbResSend++;
		}
	}

	//Envoi FIN indiquant la fin du traitement du C -> 0xFF
	IvySendMsg("%d %d %d %d %d",JAVA,RX_FRAME,SCORE_CHEMIN,0xFF,0xFF);
}

void stopBus(){
	IvySendMsg("%d %d %d %d",JAVA,TX_FRAME,0,0);
	IvyStop();
	typeTraitement=-1;
}