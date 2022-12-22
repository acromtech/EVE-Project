#include "menu_mae.h"

int fin = 1;
int selection;

int autentification()
{
    int ok = 1, mot_de_passe, repeat = 3;

    printf("\tEntrez votre mot de passe : (nombre d'essais restant : %d) \n: ", repeat);
    scanf("%d", &mot_de_passe);

    if (mot_de_passe != MDP)
    {
        repeat--;
        while (repeat > 0 && mot_de_passe != MDP)
        {
            printf("\tMot de passe invalide. Veuillez rééssayer (nombre d'essais restant : %d) : ", repeat);
            scanf("%d", &mot_de_passe);
            repeat--;
        }
    }

    repeat--;
    if (repeat < 0)
    {
        printf("\tMot de passe invalide plus d'essais restant. \n");
        ok = 0;
    }
    return ok;
}

void evolution_mae(unsigned char *etat_mae)
{
    switch (*etat_mae)
    {
    case ETAT_PRINCIPAL:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_UTILISATEUR;
            break;
        case 2:
            *etat_mae = ETAT_ADMISTRATEUR;
            break;
        }
        break;
    case ETAT_UTILISATEUR:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_RECHERCHE;
            break;
        case 2:
            *etat_mae = ETAT_COMPARAISON;
            break;
        case 3:
            *etat_mae = ETAT_PRINCIPAL;
            break;
        }
        break;

    case ETAT_ADMISTRATEUR:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_UTILISATEUR;
            break;
        case 2:
            *etat_mae = ETAT_MDP;
            break;
        case 3:
            *etat_mae = ETAT_SUPPRIME_BASE_INDEX;
            break;
        case 4:
            *etat_mae = ETAT_INDEXER_BASE;
            break;
        case 5:
            *etat_mae = ETAT_INDEXER_UN_FICHIER;
            break;
        case 6:
            *etat_mae = ETAT_AFFICHER_BASE;
            break;
        case 7:
            *etat_mae = ETAT_PRINCIPAL;
            break;
        }
        break;

    case ETAT_MDP:
        break;

    case ETAT_SUPPRIME_BASE_INDEX:
        break;

    case ETAT_INDEXER_BASE:
        break;

    case ETAT_INDEXER_UN_FICHIER:
        break;

    case ETAT_AFFICHER_BASE:
        break;

    case ETAT_COMPARAISON:
        break;

    case ETAT_RECHERCHE:
        break;

    default:
        *etat_mae = ETAT_PRINCIPAL;
        break;
    }
}

////////////////////////////////////////////////////
////		_____________________________		////
////		|							|		////
////		|		ACTION MAE			|		////
////		|___________________________|		////
////											////
////////////////////////////////////////////////////

void action_mae(unsigned char *etat_mae)
{
    switch (*etat_mae)
    {
    case ETAT_PRINCIPAL:
        printf("========================================================\n");
        printf("==============   MENU PRINCIPAL   ======================\n");
        printf("========================================================\n");
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Menu utilisateur.\n");
        printf("\t\t2.  Menu d'Administration.\n");
        break;

    case ETAT_UTILISATEUR:
        printf("===========================================================\n");
        printf("================   MENU UTILISATEUR   =====================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Rechercher dans la base de fichier.\n");
        printf("\t\t2.  Comparer des fichiers\n");
        printf("\t\t3.  Retour.\n");
        break;

    case ETAT_ADMISTRATEUR:
        int ok;
        printf("===========================================================\n");
        printf("=================   ADMINISTRATION   ======================\n");
        printf("===========================================================\n");
        printf("\tVeuillez vous authentifier : \n");
        ok = autentification();
        if (ok)
        {
            puts("\n");
            printf("\tSelectionez l'opération à réaliser.\n");
            printf("\t\t1.  Vue utilisateur.\n");
            printf("\t\t2.  Modifier le mot de passe.\n");
            printf("\t\t3.  Supprimer la base d'indexation.\n");
            printf("\t\t4.  Indexer la base de fichiers.\n");
            printf("\t\t5.  Indexer un fichier.\n");
            printf("\t\t6.  Afficher la base d'indexation.\n");
        }
        break;

    case ETAT_MDP:
        printf("\r\nmodif mdp\r\n");
        printf("===========================================================\n");
        printf("=================   ADMINISTRATION   ======================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Vue utilisateur.\n");
        printf("\t\t2.  Modifier le mot de passe.\n");
        printf("\t\t3.  Supprimer la base d'indexation.\n");
        printf("\t\t4.  Indexer la base de fichiers.\n");
        printf("\t\t5.  Indexer un fichier.\n");
        printf("\t\t6.  Afficher la base d'indexation.\n");

        *etat_mae = ETAT_ADMISTRATEUR;
        break;

    case ETAT_SUPPRIME_BASE_INDEX:
        printf("\r\nEtat supprimer base indexer\r\n");

        printf("===========================================================\n");
        printf("=================   ADMINISTRATION   ======================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Vue utilisateur.\n");
        printf("\t\t2.  Modifier le mot de passe.\n");
        printf("\t\t3.  Supprimer la base d'indexation.\n");
        printf("\t\t4.  Indexer la base de fichiers.\n");
        printf("\t\t5.  Indexer un fichier.\n");
        printf("\t\t6.  Afficher la base d'indexation.\n");
        *etat_mae = ETAT_ADMISTRATEUR;
        break;

    case ETAT_INDEXER_BASE:
        printf("\r\nEtat indexer base\r\n");
        printf("===========================================================\n");
        printf("=================   ADMINISTRATION   ======================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Vue utilisateur.\n");
        printf("\t\t2.  Modifier le mot de passe.\n");
        printf("\t\t3.  Supprimer la base d'indexation.\n");
        printf("\t\t4.  Indexer la base de fichiers.\n");
        printf("\t\t5.  Indexer un fichier.\n");
        printf("\t\t6.  Afficher la base d'indexation.\n");
        *etat_mae = ETAT_ADMISTRATEUR;
        break;

    case ETAT_INDEXER_UN_FICHIER:
        printf("\r\nEtat indexer un fichier\r\n");
        printf("===========================================================\n");
        printf("=================   ADMINISTRATION   ======================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Vue utilisateur.\n");
        printf("\t\t2.  Modifier le mot de passe.\n");
        printf("\t\t3.  Supprimer la base d'indexation.\n");
        printf("\t\t4.  Indexer la base de fichiers.\n");
        printf("\t\t5.  Indexer un fichier.\n");
        printf("\t\t6.  Afficher la base d'indexation.\n");
        *etat_mae = ETAT_ADMISTRATEUR;
        break;

    case ETAT_AFFICHER_BASE:
        printf("\r\nAfficher base\r\n");
        printf("===========================================================\n");
        printf("=================   ADMINISTRATION   ======================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Vue utilisateur.\n");
        printf("\t\t2.  Modifier le mot de passe.\n");
        printf("\t\t3.  Supprimer la base d'indexation.\n");
        printf("\t\t4.  Indexer la base de fichiers.\n");
        printf("\t\t5.  Indexer un fichier.\n");
        printf("\t\t6.  Afficher la base d'indexation.\n");
        *etat_mae = ETAT_ADMISTRATEUR;
        break;

    case ETAT_COMPARAISON:
        printf("\r\nEtat comparaison\r\n\n\n");
        printf("===========================================================\n");
        printf("================   MENU UTILISATEUR   =====================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Rechercher dans la base de fichier.\n");
        printf("\t\t2.  Comparer des fichiers\n");
        printf("\t\t3.  Retour.\n");
        *etat_mae = ETAT_UTILISATEUR;
        break;

    case ETAT_RECHERCHE:
        printf("\r\n Etat recherche\r\n\n\n");
        printf("===========================================================\n");
        printf("================   MENU UTILISATEUR   =====================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Rechercher dans la base de fichier.\n");
        printf("\t\t2.  Comparer des fichiers\n");
        printf("\t\t3.  Retour.\n");
        *etat_mae = ETAT_UTILISATEUR;
        break;
    }
}
