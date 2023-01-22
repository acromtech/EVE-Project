  

					/*-------------------------------------------/
					/  AUTEUR : VESIN Emilien LALANNE Bastien    /
                    /-------------------------------------------*/
                    
/* Rôle : Indexation des fichiers audios */


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#include "indexation_Audio.h"
#include "../Configuration/configuration.h"

char* cheminAudio = "../TestSon/";
char* cheminBaseDescripteur="../BaseDescripteursAudios/";
char* cheminListeDescripteur="../ListeDescripteursAudios/ListeDescripteursAudios.txt";
  

// Vérifie que le fichier passé en paramètre est bien un fichier audio avant de faire l'indexation
void verificationFichierAudio(char *nomFichier){
    
	if (strlen(nomFichier) > 4) {

	   for (int j=0; nomFichier[j + 3]; j++) { 

		  if (!strcmp(&nomFichier[j], ".bin")){

			 histogrammeAudio(nomFichier);

			} 
       	}
    }
}


// Remplissage de l'histogramme dans le fichier descripteur
void remplirHistogramme(char* empDescripteur, int m, int* histogramme){	
	
	FILE *descripteur;
	
	// ouverture du fichier descripteur
	descripteur = fopen(empDescripteur, "a");

	// remplissage de l'histogramme avec les valeurs dans le fichier descripteur
	for(int i =0; i < m; i++){

        fprintf(descripteur,"%d ",histogramme[i]);

    }
    // saut de ligne pour traiter la prochaine fenêtre
	fprintf(descripteur,"\n");
	
	//fermeture du fichier descripteur
	fclose(descripteur);

	// mise à zéro du tableau
	for(int i =0; i < m; i++){

   		histogramme[i] = 0;

    }
}


// Création de l'histogramme du fichier audio passeé en paramètre
void histogrammeAudio(char* nomFichier){
	
    FILE *fichierBin=NULL;
    int k;
	long nbrValeurs;
    float intervalle;
    int fenetre=0;
    double recupVal;
	char nomDescripteur[100];
	char emplacement [100];

	strcpy(emplacement,cheminAudio);
	
    // ouverture du fichier
    fichierBin = fopen(strcat(emplacement,nomFichier),"rb");
  
    // vérification de l'existance et de l'ouverture du fichier
     if (fichierBin!=NULL){
         
		//détermination du nombre de valeurs dans le fichier.bin 
		//puis on divise le resultat obtenu par 8 car un double fait 8 octets
		fseek(fichierBin, 0, SEEK_END);	
		nbrValeurs=ftell(fichierBin)/8;
		fseek(fichierBin, 0,SEEK_SET);

		// lecture des paramètres dans le .config
		int m = config("indexationAudioM");
		int n = config("indexationAudioN");

		// vérification des valeurs de n et m
		if(n<1 || n>1000000 || m<1){ 
			
			fprintf(stderr, "\e[0;31m\n/!\\Attention /!\\\nLes valeurs n et/ou m de l'indexation audio sont mal configurées.\nMerci de modifier ces paramètres dans le .config.\n\n\e[0mMise à jour avec des valeurs par défaut : n = 1024 et m = 100.\n\n");
			m = 100;
			n = 1024;
			
		}

		// création d'un tableau de taille m pour traiter fenêtre par fenêtre
		int histogramme[m];

		// détermination du nombre d'intervalles k pour découper l'axe des abscisses 
		k=(nbrValeurs/n)+1;

		// création du descripteur du fichier audio 
		descripteurAudio(nomFichier, m, k, nomDescripteur);

		// mise à zéro du tableau
		for(int i =0; i < m; i++){

			histogramme[i] = 0;

		}
	
		// calcule l'intervalle de fréquence pour découper l'axe des ordonnées
		intervalle=(float)2/(float)m;

		// lecture des valeurs du fichier .bin
		while (fread(&recupVal, sizeof(double), 1, fichierBin)==1) {
        	
			int cpt = 0;
        	
			// remplissage du tableau avec les valeurs pour une fenêtre de taille n
			while(recupVal > (-1 + (intervalle)*cpt)){
        		
				cpt++;
   			}
			
   			histogramme[cpt-1]++;
			 
			 fenetre = (fenetre + 1)%n;

				if (fenetre==0){
					
					remplirHistogramme(nomDescripteur,m, histogramme);

				}
    	}
			
		// fermeture du fichier .bin
		fclose(fichierBin);
		
		// mise à jour de la liste des descripteurs
		majListeDescripteursAudio(nomFichier);
				
	}else{

		printf("ERREUR : nom du fichier errone \n");

	}

}


// Création du descripteur du fichier audio 
void descripteurAudio(char* nomFichier, int m, int k, char emplacement[100] ){
	
    FILE* descripteur=NULL;
	char suffixeDescripteur[]="_descripteur.txt";
	char *identifiant=(char *)malloc(strlen(nomFichier)+1);
	char *nomDescripteur=(char *)malloc(strlen(nomFichier)+strlen(suffixeDescripteur)+1);

	strcpy(emplacement,cheminBaseDescripteur);
	
	// création des chaines de caractères correspondants :
	// - à l'identifiant qui sera écrit au debut du descripteur
	strcpy(identifiant,nomFichier);

	// au nom du descripteur 
	// ex : nomdufichier_descripteur.txt
	strcpy(nomDescripteur,nomFichier);
	strncpy(nomDescripteur,nomFichier,strlen(nomFichier)-4);
	nomDescripteur[strlen(nomFichier)-4]='\0';
	
	strcat(nomDescripteur,suffixeDescripteur);

	// -à l'emplacement du descripteur
	strcat(emplacement,nomDescripteur);
	
	free(nomDescripteur);
	
	// création du descripteur 
	descripteur = fopen(emplacement,"w");
	
	if (descripteur != NULL){

		// écriture de l'identifiant
		fprintf(descripteur,"%s",identifiant);
		fprintf(descripteur,"\n");
		
		free(identifiant);
		
		// écriture des dimensions de la matrice 
		fprintf(descripteur,"%d ",m);
		fprintf(descripteur,"%d ",k);
		fprintf(descripteur,"\n");
		
		// fermeture du descripteur
		fclose(descripteur);
		
	}else{

		printf("ERREUR : impossible d'indexer le document\n");

	}

	 
}


// Ecriture du nom du fichier dans la liste des descripteurs
void majListeDescripteursAudio(char* nomFichier){
	
	FILE* listeDescripteurs;
	listeDescripteurs=fopen(cheminListeDescripteur,"a");
	fprintf(listeDescripteurs,"%s \n",nomFichier);
	fclose(listeDescripteurs);
	
}


// Permet la suppression des descripteurs
void rmDescripteurs(char *repertoireBaseDescripteur){
	
	char repertoire[strlen(repertoireBaseDescripteur)+1];
    struct dirent *fichier;
    char *emplacement;
    size_t repertoireSize;
    
    // ouverture du répertoire choisi en paramètre
    strcpy(repertoire,repertoireBaseDescripteur);
    DIR *dir = opendir(repertoire); 
    repertoireSize = strlen(repertoire);
    
    
    // vérification de l'ouverture du répertoire et parcourt de celui-ci
    if (dir) {
        while ((fichier = readdir(dir)) != NULL){
			
			// traitement des fichiers  hors "." et ".."
			if (!strcmp(fichier->d_name, ".") || !strcmp(fichier->d_name, ".."))
				
				continue;

			// suppression des autres fichiers
			emplacement = calloc(repertoireSize + strlen(fichier->d_name) + 1, sizeof(char));
			strcpy(emplacement, repertoire);
			strcat(emplacement, "/");
			strcat(emplacement, fichier->d_name);
			(unlink(emplacement));
			free(emplacement);

		}
		
		// fermeture du répertoire choisi en paramètre
		closedir(dir);

	}
}