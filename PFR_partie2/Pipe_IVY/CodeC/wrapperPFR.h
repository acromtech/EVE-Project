#ifndef WRAPPERPFR_H
#define WRAPPERPFR_H

//NB RES
#define NBLISTE 10

extern int autorisation_envoie_trame;
#define CONNECTED "A"
#define DISCONNECTED "K"

//TYPE DE TRAITEMENT - MOTEUR
extern char type_traitement;
#define AUCUN 'W'
#define MOTEUR_TEXTE 'T'
#define MOTEUR_IMAGE 'I'
#define MOTEUR_SON 'S'

//ABONNEMENT
#define REQUETE_TEXTE "^T (.*)"
#define REQUETE_IMAGE "^I (.*)"
#define REQUETE_SON "^S (.*)"
#define GO "^C"
#define STOP_BUS "^O (.*)"

//ENVOI
#define INIT "D"
#define READY "R"
#define SCORE "X"
#define CHEMIN "P"
#define FIN "F"

//STRUCTURE A ENVOYER
typedef struct ivyFrameBuffer{
    int score;
    char* chemin;
    struct ivyFrameBuffer* next;
}IvyFrameBuffer;

void startBus();
void sendAllResBus(IvyFrameBuffer descScore);
void stopBus();

#endif

