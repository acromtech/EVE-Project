#ifndef WRAPPERPFR_H
#define WRAPPERPFR_H

extern int autorisation_envoie_trame;
extern char typeTraitement; //Optimisation -> 1 octet suffit
extern char* requete;
extern char masterId;
extern char motorId;

//ADRESSE
#define CONNECTED                                   0x01 
#define INDEXATION_TEXTE                            0x10    //(TX_FRAME) Demande l'indexation des données textuelles (+ ACK)
#define INDEXATION_IMAGE                            0x11    //(TX_FRAME) Demande l'indexation des données photographique (+ ACK)
#define INDEXATION_SON                              0x12    //(TX_FRAME) Demande l'indexation des données sonores (+ ACK)
#define INDEXATION_ALL                              0x13    //(TX_FRAME) Demande l'indexation de toutes les données (+ ACK)
#define TEXTE_MOTCLE                                0x20    //(TX_FRAME) Demande de réaliser une recherche textuelle par mot clé (+ ACK)
#define TEXTE_FICHIER                               0x21    //(TX_FRAME) Demande de réaliser une recherche textuelle par fichier (+ ACK)
#define IMAGE_MOTCLE                                0x30    //(TX_FRAME) Demande de réaliser une recherche photographique par mot clé (+ ACK)
#define IMAGE_FICHIER                               0x31    //(TX_FRAME) Demande de réaliser une recherche photographique par fichier (+ ACK) 
#define SON_FICHIER                                 0x40    //(TX_FRAME) Demande de réaliser une recherche sonore par fichier (+ ACK)
#define SCORE_CHEMIN                                0x50    //(RX_FRAME) Récupère les données de résulats
#define STOP_BUS                                    0x60    //(TX_FRAME) Ordonne l'arret de la connection au bus virtuel (+ ACK)
#define ADDR_OPEN_MODE                              0x70    //(TX_FRAME) Demande l'ouverture ou non de l'indexation (+ ACK)

//STRUCTURE A ENVOYER (DATA)
typedef struct resListToSend{
    char score;         //Optimisation -> 1 octet suffit
    char* chemin;
    struct resListToSend* next;
}ResListToSend;

void startBus();
void traitementEffectue();
void attenteRequete();
void sendAllResBus(ResListToSend resListToSend);
void stopBus();

#endif

