

					/*-------------------------------------------/
					/ AUTEUR : VESIN Emilien LALANNE Bastien     /
                    /-------------------------------------------*/  

/* Rôle : Indexation des fichiers audios */


#ifndef INDEXATION_Audio           
#define INDEXATION_Audio


// Vérifie que le fichier passé en paramètre est bien un fichier audio avant de faire l'indexation
void  verificationFichierAudio(char *nomFichier);
// Remplissage de l'histogramme dans le fichier descripteur
void remplirHistogramme(char* nomDescripteur, int m, int* histogramme);
// Creation de l'histogramme du fichier audio passeé en paramètre
void histogrammeAudio(char* nom_Fichier);
// Création du descripteur du fichier audio
void descripteurAudio(char* nom_Fichier, int m, int k, char emplacement[100] );
// Ecriture du nom du fichier dans la liste des descripteurs
void majListeDescripteursAudio(char* nomFichier);
// Permet la suppression des descripteurs fait lors de la précedente ouverture d'application		
void rmDescripteurs(char *repertoireBaseDescripteur);
// Lance l'indexation audio automatique dans le répertoire contenant les fichiers audio
void autoIndexationAudio(void);

#endif