
	/*-------------------------------------------/
	/ AUTEUR : VESIN Emilien et LALANNE Bastien  /
    /-------------------------------------------*/
                    
//Création des fonctions nécessaires à la recherche des fichiers audios par similitudes

#include "recherche_Audio.h"
#include "../Configuration/configuration.h"

//Compare le fichier 1 avec le fichier 2
float comparaisonDeuxFichiers(char* Nomfichier1 , char* Nomfichier2){
	//variables
	FILE* fichier1;
	FILE* fichier2;
	char identifiant1,identifiant2;
	int valeur1=0,valeur2=0;
	float resultTime=0;
	int numeroLigne=0;

	//Verifie l'ouverture des descripteurs
	fichier1=fopen(Nomfichier1,"r");
	fichier2=fopen(Nomfichier2,"r");
	if((fichier1!=NULL)&&(fichier2!=NULL)){
		
		//Récupère les identidiants 
		fscanf(fichier1,"%s",&identifiant1);
		fscanf(fichier2,"%s",&identifiant2);
		
		//Reucupère les dimensions de l'histogramme
		int m;
		int k1;
		int k2;
		fscanf(fichier1,"%d %d\n",&m,&k1);
		fscanf(fichier2,"%d %d\n",&m,&k2);
		
		//Ferme les fichiers
		fclose(fichier1);
		fclose(fichier2);

		//Compare la taille du fichier 1 par rapport au fichier 2
		if (k2>=k1){

			comparaisonDeuxHistogrammes(k1,k2,m,Nomfichier1,Nomfichier2,&numeroLigne,&resultTime);
		} else {
			comparaisonDeuxHistogrammes(k2,k1,m,Nomfichier2,Nomfichier1,&numeroLigne,&resultTime);
		}
			
	
	//Renvoie le temps trouvé		
	return resultTime;
	}
	 
}


//Compare deux histogrammes
void comparaisonDeuxHistogrammes(int k1, int k2, int m, char* Nomfichier1 , char* Nomfichier2, int* numeroLigne, float* resultTime){
	
		//Variables
		FILE *fichier1=fopen(Nomfichier1,"r");
		FILE *fichier2=fopen(Nomfichier2,"r");
		int valeur1=0, valeur2=0;
		char recupereString;
		int  recupereInt=0, recupereInt2=0;
		int i=0;
		fpos_t pos1,pos2;
		int difference=0,differenceTot=0;
		float seuil=config("seuil");
		float dureeAudioCorpus=config("dureeAudioCorpus");
		float cptSeuil=0;
		float time=0;
		float timeTot=0;
		float pourcentage=0;
		float pourcentageTot=0;

		//Prend les premiere valeur des descripteur, valeur qui ne nous interesse pas puisqu'on les as deja
		fscanf(fichier1,"%s %d %d ",&recupereString, &recupereInt2, &recupereInt2);
		fscanf(fichier2,"%s %d %d ",&recupereString, &recupereInt2, &recupereInt2);
		fgetpos(fichier1,&pos1);
		for (int i=0; i<(k2);i++){
			//Traite uniquement la premiere ligne pour placer correctement le fgetpos
			for(int z=0;z<m;z++){
				//Recupère les valeurs 
				fscanf(fichier1,"%d ", &valeur1);
				fscanf(fichier2,"%d ", &valeur2);
				
				//Calcule la difference des deux valeurs en ABSOLUE
				difference = abs((int)valeur1-(int)valeur2);
				
				//Ajoute a la difference totale 
				differenceTot+=difference;
			}
			fgetpos(fichier2,&pos2);
			//Traite les autres lignes
			for(int a=0;a<(k1-1);a++){

				for(int j=0;j<m;j++){
					//Recupère les valeurs 
					fscanf(fichier1,"%d ", &valeur1);
					fscanf(fichier2,"%d ", &valeur2);

					//Calcule la difference des deux valeurs 
					difference = abs((int)valeur1-(int)valeur2);
					
					//Ajoute a la difference totale 
					differenceTot+=difference;
				}
			}
			fsetpos(fichier1,&pos1);
			fsetpos(fichier2,&pos2);

			//Mise en poucentage de la différence calculer sur les 40 lignes
			pourcentage = ((float)differenceTot*100/(float)(k2*m));
			pourcentage = 100 - pourcentage;//Calcule pour que le poucentage corresponde à la ressemblance avec le jingle
			
			//Si le seuil est dépassé on a une bonne valeur donc on fait une moyenne avec les autres dépassements
			if(pourcentage>seuil)
			{
				//printf IMPORTANT pour debug rapidement si on a un soucis
				//printf("\r\nLigne : %d \r\n",i);
				pourcentageTot=pourcentageTot+pourcentage;
				//printf("\r\nPourcentageTot : %f \r\n",pourcentageTot);
				//printf("\r\nPourcentage : %f \r\n",pourcentage);
				time = (dureeAudioCorpus*i)/k2;
				timeTot=timeTot+time;
				//printf("\r\n Time : %.2f",time);
				cptSeuil++;
			}
			differenceTot=0;
		}
	//Calcul de la moyenne
	*resultTime=timeTot/cptSeuil;
	pourcentageTot=pourcentageTot/cptSeuil;

	//Aucune correspondance trouvée
	if(cptSeuil<1)
	{
		pourcentageTot=0;
		*resultTime=-2;
	}

	printf("\n");
	printf("| Correspondance trouvé à %.2f%% ... | \n",pourcentageTot);
	printf("\n");

	//Ferme les fichiers
	fclose(fichier1);
	fclose(fichier2);
			
}
	
//Compare un fichier audio avec tous les autres situés dans le repertoire
float comparaisonRepertoire(char * fichierReference){
	float resultTime;
	//Lance la recherche audio dans le repertoire contenant les descripteurs audios
    struct dirent *dir;
 
    DIR *d = opendir("../BaseDescripteursAudios/"); 
  
    if (d) {
		//Traite chacun des fichiers du repertoire
        while ((dir = readdir(d)) != NULL){
		
			if(strlen(dir->d_name)>3) {
				
				//Construit le chemin menant aux descripteurs audio
				char chemin[strlen("../BaseDescripteursAudios/")+strlen(dir->d_name)+1];
				char nomFichier[strlen(dir->d_name)+1];
				strcpy(chemin,"../BaseDescripteursAudios/");
				strcpy(nomFichier, dir->d_name);
				strcat(chemin,nomFichier);
				//printf("%s",strcat(chemin,nomFichier));
					
				if (strcmp(chemin,fichierReference)!=0){
					//Compare le fichier de reference avec le fichier courant 
					resultTime=comparaisonDeuxFichiers(fichierReference,chemin);
				}
			}	
        }
        closedir(d);
    }
	return resultTime;
}

//Demande le nom d'un fichier et renvoie le resultat de la recherche 
float resultatRechercheAudio(char* souhait){
	//Parcours le repertoire a la recherche du fichier
	struct dirent *dir;
	int existe=0;
 
    DIR *d = opendir("../TestSon/");
    if (d) {
        while ((dir = readdir(d)) != NULL){
			if(!strcmp(dir->d_name,souhait)){
				souhait[strlen(souhait)-4]='\0';
				strcat(souhait,"_descripteur.txt");
				
				char chemin[strlen("../BaseDescripteursAudios/")+1+ strlen(souhait)];
				strcpy(chemin,"../BaseDescripteursAudios/");
				strcat(chemin,souhait);
				existe=1;
				//Compare aux autres fichiers du repertoire s'il existe
				float resultTime = comparaisonRepertoire(chemin);
				
				return resultTime;
			} 
		}
	}
	return -1;
}



void saisieRechercheAudio(){
	//Demande le nom du fichier
	char souhait[100];
	printf("| Entrez le nom de votre fichier : ");
	scanf("%s",souhait);
	printf("\n");
	
	printf("\n");
	printf("| Veuillez patienter | \n");
	printf("\n");
	
	float resultat;
	resultat = resultatRechercheAudio(souhait);
	
	if (resultat==-1){
		printf("| document inconnu, arrêt du programme |\n");
		printf("\n");
		exit(0);
	} else {
		if(resultat==-2){
			printf("\n");
			perror("| Pas de correspondance trouvé, arrêt du programme ");
			exit(0);
		}
		else{
			printf("\n");
			printf("| Voici le résultat | \n");
			printf("\n");
			printf("Le jingle demarre à environ %d sec du corpus\n", (int)resultat);
		}
	}

	printf("\r\nAppuyez sur entrée pour lancer l'audio... (3 sec avant) ");

	getchar();
	// retour de chariot
	while(getchar() != '\n');
	char *fichierAudio = "../TestSon/corpus_fi.wav";

	//Lance le fichier correspondant
	lanceFichierAudio(&(*fichierAudio),resultat);
}



//Lance un fichier audio à partir de son nom avec vlc au temps correspondant -3 sec
void lanceFichierAudio(char *fichierAudio, int time) {

	char *lecteurAudio="vlc --play-and-exit --start-time ";//--start-time 12 POUR commencer à 12sec par exemple
	char *commande;
	char ctime[4];

	//Regarde si on peut soustraire 3 sec à la corespondance trouvée
	if(time>4)
	{
		time-=3;
	}
	else{
		time=0;
	}
    //Allocation espace fichierAudio + lecteurAudion + temps
	commande=(char *)malloc(strlen(fichierAudio)+strlen(lecteurAudio)+strlen(ctime)+1+1+1);
	//Verifie le malloc
	if (commande !=NULL){
		//Lance l'ouverture du fichier .wav correspondant
		sprintf(ctime,"%d",time);
		strcpy(commande,lecteurAudio);
		strcat(commande,ctime);
		strcat(commande," ");
		strcat(commande,fichierAudio);
		printf("%s \r\n\n",commande);
		int ret=system(commande);

		if (ret != 0) {
        fprintf(stderr, "Erreur lors de l'appel de VLC\n");
    	}

		//Libère l'espace memoire
		free(commande);
	}
	

}



	
