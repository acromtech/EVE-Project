#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "indexation_Audio.h"

int main (){
	// supprime les descripteurs fait lors de la précedente ouverture d'application
	rmDescripteurs("../BaseDescripteursAudios/");

	// supprime la liste descripteur faite lors de la précedente ouverture d'application
	remove("../ListeDescripteursAudios/ListeDescripteursAudios.txt");

	// lance l'indexation audio dans le répertoire contenant les fichiers audio
	struct dirent *dir;
	DIR *d = opendir("../TestSon/"); 
	if (d) {

        while ((dir = readdir(d)) != NULL){

			if(strlen(dir->d_name)>4){

			 verificationFichierAudio(dir->d_name);
			}
			
        }

        closedir(d);
	}
}
