
					/*-------------------------------------------/
					/  AUTEUR : LALANNE Bastien                  /
                    /-------------------------------------------*/
                    
/* Rôle : Permet la modifcitaion, l'affichage et l'écriture des paramètres dans le .config*/


#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include "configuration.h"


// Permet de modifier la valeur d'un paramètre dans le .config en donnant la ligne et la nouvelle valeur
void editConfig(int nouvNumLigne, int nouvVal){
   
    int numLigne = 0;  // numéro de la ligne à lire
    char texte[256];    // nom du paramètre choisi
    int val = 0;        // valeur du paramètre choisi
    int nbrLigne = 0;  // nombre de ligne dans le .config

    // création de pointeur pour accéder au fichier
    FILE *ptrFichier1, *ptrFichier2;
    
    char fichierConfig[] = "../Configuration/.config";

    // ouverture du fichier en lecture seul
    ptrFichier1 = fopen(fichierConfig, "r");

    // si le fichier ne c'est pas ouvert on arrête tout
    if(ptrFichier1 == NULL){   
        
        exit(1);
    }

    fscanf(ptrFichier1, "%d %s %d", &numLigne, texte, &nbrLigne);

    // ouverture du fichier de copie
    ptrFichier2 = fopen("../Configuration/.config2", "w");
    
    // écriture de la première ligne du fichier 1 dans le fichier 2 
    fprintf(ptrFichier2, "%d %s %d\n", numLigne, texte, nbrLigne);

    // lecture dans le fichier d'origine
    while(fscanf(ptrFichier1, "%d %s %d",&numLigne, texte, &val)!=EOF){ 
        
        if(nouvNumLigne == numLigne){

            // écriture dans le fichier 2 du nom du paramètre et sa nouvelle valeur
            fprintf(ptrFichier2, "%d %s %d\n",numLigne, texte, nouvVal);

        }else{

            // écriture dans le fichier 2 des autres paramètres
            fprintf(ptrFichier2, "%d %s %d\n",numLigne, texte, val);
        }  
    }

    // fermeture des fichiers
    fclose(ptrFichier1);
    fclose(ptrFichier2);
    
    // suppression du fichier 1
    remove("../Configuration/.config");

    // renomme le fichier 2 en fichier 1
    rename("../Configuration/.config2", "../Configuration/.config");
}


// Interface pour modifier la valeur d'un paramètre dans le .config 
void saisieConfig(){
    
    int numLigne = 0;  // numéro de la ligne à lire
    char texte[256];    // nom du paramètre choisi
    int val = 0;        // valeur du paramètre choisi
    char nouvVal[10];  // récupère la nouvelle valeur saisie par l'utilisateur
    int nbrLigne = 0;  // nombre de ligne dans le .config
    char test_numLigne[2];
    
    // création de pointeur pour accéder au fichier
    FILE *ptrFichier1;
    
    char fichierConfig[] = "../Configuration/.config";

    // ouverture du fichier en lecture seul
    ptrFichier1 = fopen(fichierConfig, "r");

    // si le fichier ne c'est pas ouvert on arrête tout
    if(ptrFichier1 == NULL){   
       
        exit(1);
    }

    // affichage du .config
    affichConfig();

    fscanf(ptrFichier1, "%d %s %d", &numLigne, texte, &nbrLigne);
	
    do{

        rewind(ptrFichier1);
        __fpurge(stdin);
        printf("\n\nEntrez le numéro du paramètre qui doit être modifié : ");
        fgets(test_numLigne, sizeof test_numLigne, stdin);
        
        // purge le stdin si la saisie est trop longue
        __fpurge(stdin);

    }while(atoi(test_numLigne)<2 || atoi(test_numLigne)>nbrLigne);

    int nouvNumLigne = atoi(test_numLigne);
    fclose(ptrFichier1);
    
    do{

        printf("Entrez la nouvelle valeur pour le paramètre n° %d : ",nouvNumLigne);
        fgets(nouvVal, sizeof nouvVal, stdin);

    }while(atoi(nouvVal) == atoi("n"));
	
	editConfig(nouvNumLigne,atoi(nouvVal));

	affichConfig();
}


// Affichage du .config
void affichConfig(){
	
    int numLigne = 0;  // numéro de la ligne à lire
    char texte[256];    // nom du paramètre choisi
    int val = 0;        // valeur du paramètre choisi
    char nouvVal[10];  // récupère la nouvelle valeur saisie par l'utilisateur
    int nbrLigne = 0;  // nombre de ligne dans le .config

    // création de pointeur pour accéder au fichier
    FILE *ptrFichier1;
    
    char fichierConfig[] = "../Configuration/.config";

    // ouverture du fichier en lecture seul
    ptrFichier1 = fopen(fichierConfig, "r");

    // si le fichier ne c'est pas ouvert on arrête tout
    if(ptrFichier1 == NULL){

        exit(1);

    }

    fscanf(ptrFichier1, "%d %s %d", &numLigne, texte, &nbrLigne);

    for(int i=0; i<(nbrLigne - 1); i++){

        // lecture du nom et de la valeur du paramètre
        fscanf(ptrFichier1, "%d %s %d",&numLigne, texte, &val);

        // affichage sur le terminal
        printf("\n%d %s %d\n",numLigne, texte, val);
    }

    // fermeture du fichier
    fclose(ptrFichier1);
}


// Permet la récupération de la valeur du paramètre donner en paramètre
int config(char nom[]){

    int numLigne = 0;  // numéro de la ligne à lire
    char texte[256];    // nom du paramètre choisi
    int val = 0;        // valeur du paramètre choisi
    int nbrLigne = 0;  // nombre de ligne dans le .config
    
    // création de pointeur pour accéder au fichier
    FILE *ptrFichier1;
    
    char fichierConfig[] = "../Configuration/.config";

    // ouverture du fichier en lecture seul
    ptrFichier1 = fopen(fichierConfig, "r");

    // si le fichier ne c'est pas ouvert on arrête tout
    if(ptrFichier1 == NULL){   
        
        printf("Erreur, ouverture du fichier de configuration imposible");
        return -1;
    }

    fscanf(ptrFichier1, "%d %s %d", &numLigne, texte, &nbrLigne);

    for(int i=0; i<(nbrLigne - 1); i++){
        
        // lecture du nom et de la valeur du paramètre
        fscanf(ptrFichier1, "%d %s %d",&numLigne, texte, &val);

        // cherche une correspondance
        if((strcmp(texte, nom)) == 0){
            
            // fermeture du fichier
            fclose(ptrFichier1);

            // retourne la valeur du paramètre
            return val;

        }
    }

    // fermeture du fichier
    fclose(ptrFichier1);
    return -1;
}