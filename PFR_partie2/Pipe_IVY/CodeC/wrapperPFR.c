#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "unistd.h"
#include "pcre.h"
#include "ivy.h"
#include "ivyloop.h"

#include "wrapperPFR.h"

int autorisation_envoie_trame=0;
char type_traitement=AUCUN;
MsgRcvPtr texteId;
MsgRcvPtr imageId;
MsgRcvPtr sonId;
MsgRcvPtr goId;
MsgRcvPtr stopId;

void* ivyThread(void* arg) {
    IvyMainLoop();
    return NULL;
}

//FONCTIONS CALLBACK
void GoCallback (IvyClientPtr app, void *data, int argc, char **argv){
	autorisation_envoie_trame=1;
}

void TRequestCallback (IvyClientPtr app, void *data, int argc, char **argv){
	printf("\nC\tREQUETE_TEXTE");
	type_traitement=MOTEUR_TEXTE;
}

void IRequestCallback (IvyClientPtr app, void *data, int argc, char **argv){
	printf("\nC\tREQUETE_IMAGE");
	type_traitement=MOTEUR_IMAGE;
}

void SRequestCallback (IvyClientPtr app, void *data, int argc, char **argv){
	printf("\nC\tREQUETE_SON");
	type_traitement=MOTEUR_SON;
}

void ByeCallback (IvyClientPtr app, void *data, int argc, char **argv){
	IvyStop();
}

//WRAPPER
/**
 * @brief Démarre le bus
 * 
 */
void startBus(){
	//Initialisation du bus
	IvyInit ("hoteC",CONNECTED, 0, 0, 0, 0);

	//Abonnement aux différents messages
	texteId = IvyBindMsg(TRequestCallback,0,REQUETE_TEXTE);
	imageId = IvyBindMsg(IRequestCallback,0,REQUETE_IMAGE);
	sonId = IvyBindMsg(SRequestCallback,0,REQUETE_SON);
	goId = IvyBindMsg(GoCallback,0,GO);
	stopId = IvyBindMsg(ByeCallback,0,STOP_BUS);

	//Lancement du bus espion dans un thread séparé
	IvyStart ("127.255.255.255:2010");
	pthread_t thread;
    pthread_create(&thread, NULL, ivyThread, NULL);
}

void sendOneResBus(int score, char* chemin){
	char* chaine = calloc(1024,sizeof(char));
	IvySendMsg("%s %d %s %s",SCORE,score,CHEMIN,chemin);
}

/**
 * @brief Envoie la structure contenant 
 * la liste des score et leurs chemins respectifs à JAVA
 * 
 * @param ivyFrameBuffer 
 */
void sendAllResBus(IvyFrameBuffer ivyFrameBuffer){

	//Déclaration et initialisation des variables
	int nb_res = 0;
	IvyFrameBuffer* cpIvyFrameBuffer = &ivyFrameBuffer;

	//Prévient JAVA que l'on a n paquets a lui envoyer
	IvySendMsg("%s %d",INIT,NBLISTE);

	//Prévient JAVA que le C est pret a envoyer les data
	IvySendMsg("%s",READY);
	
	//Envoie les trames si JAVA LUI DEMANDE (JAVA = Controleur)
	while(nb_res<NBLISTE && cpIvyFrameBuffer!=NULL){
		if(autorisation_envoie_trame){ //JAVA renvoi un feedback GO -> Change var globale go via CallBack GO
			sendOneResBus(cpIvyFrameBuffer->score,cpIvyFrameBuffer->chemin);
			printf("\nC\tScore : %d, Chemin : %s", cpIvyFrameBuffer->score, cpIvyFrameBuffer->chemin);
			cpIvyFrameBuffer=cpIvyFrameBuffer->next;
			nb_res++;
			autorisation_envoie_trame=0;
			IvySendMsg("%s",READY);
		}
	}

	IvySendMsg(FIN); //JAVA recois le feedback FIN et lance la procédure d'affichage des resultats
}

void stopBus(){
	IvySendMsg("%s",DISCONNECTED);
	IvyStop();
}