	/*-------------------------------------------/
	/ AUTEUR : VESIN Emilien et LALANNE Bastien  /
    /-------------------------------------------*/
                    
#ifndef MODULE_rechercheAudio
#define MODULE_rechercheAudio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>


struct resultatAudio{
	int score;
	char *path;
};

//Compare un fichier audio avec tous les autres situés dans le repertoire
float comparaisonRepertoire(char *);
//Compare le fichier 1 avec le fichier 2
float comparaisonDeuxFichiers(char* , char* );
//Compare deux histogrammes
void comparaisonDeuxHistogrammes(int , int , int , char* , char* , int* , float* );
//Lance un fichier audio à partir de son nom avec vlc au temps correspondant
void lanceFichierAudio(char* fichierAudio,int resultat);
//Demande le fichier à comparer 
struct resultatAudio saisieRechercheAudio(char*);
//Affichage resultat
float resultatRechercheAudio(char* souhait);



#endif
