#ifndef MENU
#define MENU

#define MDP 1234
extern int fin;

void menu_principal(void);
void menu_administration(void);
void menu_utilisateur(void);
void menu_recherche_utilisateur(void);
void menu_comparaison_utilisateur(void);
void action_menu_principal(int);
void action_menu_utilisateur(int);
void action_menu_administration(int);
void action_menu_recherche_utilisateur(int);
void action_menu_comparaison_utilisateur(int);

int autentification(void);
int selection_choix(int);


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
ETAT_RECHERCHE,
};
#endif // !MENU