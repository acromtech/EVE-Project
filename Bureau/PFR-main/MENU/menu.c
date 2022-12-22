#include<stdio.h>
#include "menu.h"

int fin = 1;

int selection_choix(int interval)
{
    char selection;

    scanf("%c",&selection);
    getchar();
    
    if((selection < '1' || selection > '0'+interval) && selection != '#')
        while(selection < '1' || selection > '0'+interval)
        {
            printf("Selection incorrect ! Veuillez rééssayer : \n");
            scanf("%c",&selection);
        }
    if(selection == '#')
        fin = 0;

    return selection - '0';
}

void menu_principal(void)
{
    int selections;

    printf("========================================================\n");
    printf("==============   MENU PRINCIPAL   ======================\n");
    printf("========================================================\n");
    puts("\n");
    printf("\tSelectionez l'opération à réaliser.\n");
    printf("\t\t1.  Menu utilisateur.\n");
    printf("\t\t2.  Menu d'Administration.\n");
    
    selections = selection_choix(2);
    action_menu_principal((char)selections);
}

void menu_administration(void)
{
    int ok, selections;

    printf("===========================================================\n");
    printf("=================   ADMINISTRATION   ======================\n");
    printf("===========================================================\n");
    printf("\tVeuillez vous authentifier : \n");
    
    ok = autentification();

    if(ok)
    {
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Vue utilisateur.\n");
        printf("\t\t2.  Modifier le mot de passe.\n");
        printf("\t\t3.  Supprimer la base d'indexation.\n");
        printf("\t\t4.  Indexer la base de fichiers.\n");
        printf("\t\t5.  Indexer un fichier.\n");
        printf("\t\t6.  Afficher la base d'indexation.\n");
        selections = selection_choix(6);
        action_menu_administration(selections);
    }
    menu_principal();
}

void menu_utilisateur(void)
{
    int selections;

    printf("===========================================================\n");
    printf("================   MENU UTILISATEUR   =====================\n");
    printf("===========================================================\n");
    
    {
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Rechercher dans la base de fichier.\n");
        printf("\t\t2.  Comparer des fichiers\n");
        printf("\t\t3.  Retour.\n");
        selections = selection_choix(3);
        action_menu_utilisateur(selections);
    }
}

void menu_recherche_utilisateur(void)
{
    int selections;

    printf("===========================================================\n");
    printf("=============   UTILISATEUR - RECHERCHE   =================\n");
    printf("===========================================================\n");
    
    {
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Rechercher par mot clé un fichier texte.\n");
        printf("\t\t2.  Rechercher par couleur une image.\n");
        printf("\t\t3.  Retour.\n");
        selections = selection_choix(3);
        action_menu_recherche_utilisateur(selections);
    }
}

void menu_comparaison_utilisateur(void)
{
    int selections;

    printf("===========================================================\n");
    printf("============   UTILISATEUR - COMPARAISON   ================\n");
    printf("===========================================================\n");
    
    {
        puts("\n");
        printf("\tSelectionez l'opération à réaliser.\n");
        printf("\t\t1.  Comparer un fichier image à la base d'image.\n");
        printf("\t\t2.  Comparer un fichier texte à la base de fichiers.\n");
        printf("\t\t3.  Comparer un fichier audio à la base de fichiers.\n");
        printf("\t\t4.  Retour.\n");
        selections = selection_choix(4);
        action_menu_comparaison_utilisateur(selections);
    }
}

void action_menu_principal(int selections) 
{
    switch (selections)
    {
        case 1: 
            menu_utilisateur();
            break;
        case 2: 
            menu_administration();
            break;
        default:
            fin = 0;
            break;
    }
}

void action_menu_utilisateur(int action)
{
    switch(action)
    {
        case 1:
            menu_recherche_utilisateur();
            break;
        case 2:
            menu_comparaison_utilisateur();
            break;
        case 3:
            menu_principal();
            break;
        default:
            puts("Mauvais choix !");
            menu_principal();
            break;
    }
}

void action_menu_administration(int action)
{
    switch(action)
    {
        case 1:
            menu_utilisateur();
            break;
        case 2:
            // appel fonction de modification de mdp;
            printf("Mot de passe modifier !\n");
            break;
        case 3:
            // appel fonction de suppression de la base d'indexation
            printf("Base d'indexation supprimer.\n");
            break;
        case 4:
            // appel fonction d'indexation de la base de fichiers
            printf("Base indexer\n.");
            break;
        case 5:
            // appel fonction d'indexation d'un fichier 
            printf("Fichier indexer.");
            break;
        case 6:
            // appel fonction d'affichage de la base d'index
            printf("Affichage de la base d'indexation.");
            break;
        default:
            menu_principal();
            puts("Mauvais choix !");
            break;
    }
}

void action_menu_recherche_utilisateur(int action)
{
    switch(action)
    {
        case 1:
            // appel fonction recherche fichier texte par mot cle
            printf("Fichier texte rechercher !\n");
            menu_recherche_utilisateur();
            break;
        case 2:
            // appel fonction recherche image par couleur
            printf("Fichier image rechercher !\n");
            menu_recherche_utilisateur();
            break;
        case 3:
            menu_utilisateur();
            break;
        default:
            puts("Mauvais choix !");
            menu_principal();
            break;
    }
}
void action_menu_comparaison_utilisateur(int action)
{
    switch(action)
    {
        case 1:
            // appel fonction comparaison fichier image
            printf("Comparaison image !\n");
            menu_comparaison_utilisateur();
            break;
        case 2:
            // appel fonction comparaison fichier texte
            printf("Comparaison texte !\n");
            menu_comparaison_utilisateur();
            break;
        case 3:
            // appel fonction comparaison fichier audio
            printf("Comparaison audio !\n");
            menu_comparaison_utilisateur();
            break;
        case 4:
            menu_utilisateur();
            break;
        default:
            puts("Mauvais choix !");
            menu_principal();
            break;
    }
}

int autentification()
{
    int ok = 1, mot_de_passe, repeat = 3;

    printf("\tEntrez votre mot de passe : (nombre d'essais restant : %d) \n: ", repeat);
    scanf("%d",&mot_de_passe);

    if(mot_de_passe != MDP)
    {
        repeat--;
        while (repeat > 0 && mot_de_passe != MDP)
        {
            printf("\tMot de passe invalide. Veuillez rééssayer (nombre d'essais restant : %d) : ",repeat);
            scanf("%d",&mot_de_passe);
            repeat--;
        }
    }

    repeat--;     
    if(repeat < 0)
    {
        printf("\tMot de passe invalide plus d'essais restant. \n");
        ok = 0;
    }
    return ok;
}