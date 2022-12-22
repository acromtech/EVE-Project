#ifndef MENU
#define MENU

#include <stdio.h>
#include <stdlib.h>

#define MDP 1234

void action_mae(unsigned char *etat_mae);
void evolution_mae(unsigned char *etat_mae);


//Differents etats de la mae
enum{ETAT_PRINCIPAL,
ETAT_UTILISATEUR,
ETAT_ADMISTRATEUR,
ETAT_MDP,
ETAT_SUPPRIME_BASE_INDEX,
ETAT_INDEXER_BASE,
ETAT_INDEXER_UN_FICHIER,
ETAT_AFFICHER_BASE,
ETAT_COMPARAISON,
ETAT_RECHERCHE
};
#endif // !MENU