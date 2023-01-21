#ifndef MENU
#define MENU

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Configuration/configuration.h"

//#define MDP 1234

void action_mae(unsigned char *etat_mae);
void evolution_mae(unsigned char *etat_mae);


//Differents etats de la mae
enum{ETAT_PRINCIPAL,
ETAT_UTILISATEUR,
ETAT_ADMISTRATEUR,
ETAT_MDP,
ETAT_SUPPRIME_BASE_INDEX,
ETAT_INDEXER_BASE,
ETAT_CONFIG,
ETAT_TEXTE,
ETAT_IMAGE,
ETAT_AUDIO,
ETAT_FERME_APPLI
};
#endif // !MENU