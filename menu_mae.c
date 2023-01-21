#include "menu_mae.h"

int fin = 1;
int selection;

int autentification()
{
    int ok = 1, mot_de_passe, repeat = 3, cle=config("motdePasse");

    //printf("\tmot de passe : %d\n",cle);
    printf("\tEntrez votre mot de passe (nombre d'essais restant %d) \n\t: ", repeat);
    scanf("%d", &mot_de_passe);

    if (mot_de_passe != cle)
    {
        repeat--;
        while (repeat > 0 && mot_de_passe != cle)
        {
            printf("\tMot de passe invalide. \n\tVeuillez rééssayer (nombre d'essais restant %d) \n\t: ", repeat);
            scanf("%d", &mot_de_passe);
            repeat--;
        }
    }

    if (repeat < 0)
    {
        printf("\t\e[1;31m| Mot de passe invalide plus d'essais restant. |\e[0m\n");//Texte en gras rouge
        ok = 0;
    }
    return ok;
}

int modifMotDePasse()//A MODIFIER !!!!!
{
    int test=0;
    printf("\r\n1 vrai sinon faux : ");
    scanf("%d", &test);
    if(test==1)
    {
        printf("\r\nMot de passe modifié !!!\n\n");
        return 1;
    }
    return -1;
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
        case 3:
            *etat_mae = ETAT_FERME_APPLI;
            break;
        }
        break;
    case ETAT_UTILISATEUR:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_PRINCIPAL;
            break;
        case 2:
            *etat_mae = ETAT_TEXTE;
            break;
        case 3:
            *etat_mae = ETAT_IMAGE;
            break;
        case 4:
            *etat_mae = ETAT_AUDIO;
            break;
        }
        break;

    case ETAT_ADMISTRATEUR:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_PRINCIPAL;
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
            *etat_mae = ETAT_CONFIG;
            break;
        case 6:
            *etat_mae = ETAT_UTILISATEUR;
            break;
        }
        break;

    case ETAT_MDP:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_ADMISTRATEUR;
            break;
        case 2:
            printf("\r\n\n| Changement de mot de passe |");
            int modif=modifMotDePasse();
            if(modif==-1)
            {
                printf("\r\n\n\e[1;31m| ECHEC ! |\e[0m\n\n");//Texte en gras rouge
                sleep(2);
            }
            break;
        case 3:
            *etat_mae = ETAT_FERME_APPLI;
            break;
        }
        break;

    case ETAT_SUPPRIME_BASE_INDEX:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_ADMISTRATEUR;
            break;
        case 2:
            printf("\r\n\n| Suppression de la base Indexée |\n\n");
            sleep(2);
            break;
        case 3:
            *etat_mae = ETAT_FERME_APPLI;
            break;
        }
        break;

    case ETAT_INDEXER_BASE:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_ADMISTRATEUR;
            break;
        case 2:
            printf("\r\n\n| Indexation lancée ... |\n\n");
            sleep(2);
            break;
        case 3:
            *etat_mae = ETAT_FERME_APPLI;
            break;
        }
        break;

    case ETAT_CONFIG:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_ADMISTRATEUR;
            break;
        case 2:
            printf("\r\n\n| Lancement de la modification du fichier config ... |\n\n");
            sleep(2);
            break;
        case 3:
            *etat_mae = ETAT_FERME_APPLI;
            break;
        }
        break;

    case ETAT_TEXTE:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_UTILISATEUR;
            break;
        case 2:
            printf("\r\n\n| 1ere méthode de recherche ??? |\n\n");
            sleep(2);
            break;
        case 3:
            printf("\r\n\n| 2eme méthode de recherche ??? |\n\n");
            sleep(2);
            break;
        case 4:
            *etat_mae = ETAT_FERME_APPLI;
            break;
        }
        break;

    case ETAT_IMAGE:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_UTILISATEUR;
            break;
        case 2:
            printf("\r\n\n| 1ere méthode de recherche Noir et Blanc |\n\n");
            sleep(2);
            break;
        case 3:
            printf("\r\n\n| 2eme méthode de recherche Couleur |\n\n");
            sleep(2);
            break;
        case 4:
            *etat_mae = ETAT_FERME_APPLI;
            break;
        }
        break;

    case ETAT_AUDIO:
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            *etat_mae = ETAT_UTILISATEUR;
            break;
        case 2:
            printf("\r\n\n| Recherche de la correspondance lancée ... |\n\n");
            sleep(2);
            break;
        case 3:
            *etat_mae = ETAT_FERME_APPLI;
            break;
        }
        break;

    case ETAT_FERME_APPLI:
        printf("\r\n\e[1;31m| Fermeture de l'application ... |\e[0m\n\n");
        exit(0);
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
        printf("\tSelectionez l'opération à réaliser.\n\n");
        printf("\t\t1.  Menu utilisateur.\n");
        printf("\t\t2.  Menu d'Administration.\n");
        printf("\t\t3.  Fermer l'application.\n");
        break;

    case ETAT_UTILISATEUR:
        printf("===========================================================\n");
        printf("================   MENU UTILISATEUR   =====================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n\n");
        printf("\t\t2.  TEXTE.\n");
        printf("\t\t3.  IMAGE.\n");
        printf("\t\t4.  AUDIO.\n");
        printf("\n\t\t1.  Retour.\n");
        break;

    case ETAT_ADMISTRATEUR:
        int ok;
        printf("===========================================================\n");
        printf("=================   ADMINISTRATION   ======================\n");
        printf("===========================================================\n");
        printf("\tVeuillez vous authentifier \n");
        ok = autentification();
        if (ok)
        {
            puts("\n");
            printf("\tSelectionez l'opération à réaliser.\n\n");
            printf("\t\t2.  Modifier le mot de passe.\n");
            printf("\t\t3.  Supprimer la base d'indexation (TEXTE, IMAGE et AUDIO).\n");
            printf("\t\t4.  Indexer la base de fichiers (TEXTE, IMAGE et AUDIO).\n");
            printf("\t\t5.  Modifer les paramètres d'indexation.\n");
            printf("\t\t6.  Vue utilisateur.\n");
            printf("\n\t\t1.  Retour.\n");
        }
        else{
            *etat_mae = ETAT_FERME_APPLI;
        }
        break;

    case ETAT_MDP:
        printf("===========================================================\n");
        printf("==============   MODIFICATION MOT DE PASSE   ==============\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\t\t2.  Modifer.\n");
        printf("\t\t3.  Fermer l'application.\n");
        printf("\n\t\t1.  Retour (Vous demandera de vous identifier à nouveau).\n");
        break;

    case ETAT_SUPPRIME_BASE_INDEX:
        printf("===========================================================\n");
        printf("============   SUPPRIMER LA BASE D'INDEXATION   ===========\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\t\t2.  Supprimer.\n");
        printf("\t\t3.  Fermer l'application.\n");
        printf("\n\t\t1.  Retour (Vous demandera de vous identifier à nouveau).\n");
        break;

    case ETAT_INDEXER_BASE:
        printf("===========================================================\n");
        printf("=============   INDEXER LA BASE DE FICHIERS   =============\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\t\t2.  Indexer.\n");
        printf("\t\t3.  Fermer l'application.\n");
        printf("\n\t\t1.  Retour (Vous demandera de vous identifier à nouveau).\n");
        break;

    case ETAT_CONFIG:
        printf("===========================================================\n");
        printf("===============   MODIFICATION PARAMETRES   ===============\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\t\t2.  Lancer la modification.\n");
        printf("\t\t3.  Fermer l'application.\n");
        printf("\n\t\t1.  Retour (Vous demandera de vous identifier à nouveau).\n");
        break;

    case ETAT_TEXTE:
        printf("===========================================================\n");
        printf("======================     TEXTE     ======================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\t\t2.  1ere méthode.\n");
        printf("\t\t3.  2eme méthode.\n");
        printf("\t\t4.  Fermer l'application.\n");
        printf("\n\t\t1.  Retour.\n");
        break;

    case ETAT_IMAGE:
        printf("===========================================================\n");
        printf("======================     IMAGE     ======================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\t\t2.  1ere méthode.\n");
        printf("\t\t3.  2eme méthode.\n");
        printf("\t\t4.  Fermer l'application.\n");
        printf("\n\t\t1.  Retour.\n");
        break;

    case ETAT_AUDIO:
        printf("===========================================================\n");
        printf("======================     AUDIO     ======================\n");
        printf("===========================================================\n");
        puts("\n");
        printf("\t\t2.  Recherche Jingle.\n");
        printf("\t\t3.  Fermer l'application.\n");
        printf("\n\t\t1.  Retour.\n");
        break;
    }
}
