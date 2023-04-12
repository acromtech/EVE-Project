#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
#include "../../Configuration/configuration.h"
#include "indexationImage.h"

const int tabVal[]={59,51,56,57,48,12,3,53,60,62,40,8,9,15,10,31,2,1,32,63,0,5};
const char* tabCouleur[]={"violet","fushia","orange","saumon","rouge","vert","bleu","corail","jaune","kaki","olive","vertForet","bleuMer","eau","cyan","turquoise","bleuMarine","bleuNuit","marron","blanc","noir","ardoise"};
void supprimerBaseImage()
{
    system("echo > ../FichierIndexation/Image/liste_descripteur_image.csv");
    system("echo > ../FichierIndexation/Image/base_descripteur_image.csv");
}

descripteurEtScoreListeImage rechercheCouleur(const volatile baseDescripteurImage pileImage, listeDescripteurImage liste, char *couleur) {
    setlocale(LC_ALL,"");
    char* requete=calloc(1,sizeof(char));
    int nbScore=0;
    baseDescripteurImage tmp = pileImage;
    Src pileScore = NULL;
    descripteurEtScoreListeImage liste_resultat = NULL;
    char *jsonPath = calloc(TAILLE_MALLOC, sizeof(char));
    
    pileScore=calculeScoreCouleur(pileImage,couleur,&nbScore);

    for(int i = 0; i<nbScore; i++){
        jsonPath = trouverCheminImage(pileScore[i].id, liste);
        liste_resultat = empilerDescripteurEtScoreImage(liste_resultat, jsonPath,pileScore[i].id, (int)(pileScore[i].score));
    }
    return liste_resultat;
}

descripteurEtScoreListeImage rechercheHisto(const volatile baseDescripteurImage pileImage, listeDescripteurImage liste, char *requete) {
    char* requeteTraite=calloc(100 ,sizeof(char));
    int nbScore=0;
    elementlitsetDescripteurImage tmp1 = liste->tete;
    descImage *tmp = pileImage->tete;
    descripteurEtScoreListeImage liste_resultat = NULL;
    char *jsonPath = calloc(TAILLE_MALLOC, sizeof(char));
    int id=-1;                                                                                                                                                                                                                                                                                                                                         
    
    snprintf(requeteTraite,100,"../../BaseFichier/Image/TXT/%s.txt",getNomFichierImage(requete));
    

    while(tmp1 != NULL){
        if(strcmp(tmp1->path, requeteTraite) == 0){
            id = tmp1->id;
            break;
        }
        tmp1 = tmp1->next;
    }
     
    if(id != -1){ 
        while(tmp != NULL){
            if(tmp->id == id)
                break;
            tmp = tmp->next;
        }
    
        Src pileScore=calculeScoreComparaison(pileImage,*tmp,&nbScore);
        //printf("%s %d %d %d\n",requeteTraite, id, tmp->id, nbScore);   

        for(int i = 1; i<nbScore; i++){
            jsonPath = trouverCheminImage(pileScore[i].id, liste);
            //printf("%s %f\n", jsonPath, pileScore[i].score);
            liste_resultat = empilerDescripteurEtScoreImage(liste_resultat, jsonPath,pileScore[i].id, (int)(pileScore[i].score));
        }
    }
    
    return liste_resultat;
}


ScoreImage choixFichierImage(Src pileScore,int tailleTabScore) {
    int index;
    int nbListe = config("nbListe");
    ScoreImage scoreImage;
    printf("\e[1;37mVeuillez rentrer le nombre entre parenthèses associé au fichier que vous souhaitez ouvrir\e[0m\n");
    do{
        scanf("%d",&index);
        if(index>min(tailleTabScore,nbListe)||index<1) printf("\e[1;35mAttention\e[0;35m : Vous ne pouvez rentrer qu'un chiffre compris entre 1 et %d\e[0m\n",min(tailleTabScore,nbListe));
        else scoreImage=pileScore[index-1];
    }while(index>min(tailleTabScore,nbListe)||index<1);
    return scoreImage;
}
void insertionSortImage(Src tab, int size) 
{
    int i, j;
    ScoreImage tmp;

    for (i=0 ; i < size-1; i++)
    {
        for (j=0 ; j < size-i-1; j++)
        {
            if (tab[j].score < tab[j+1].score) 
            {
                tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }
        }
    }
}

Src calculeScoreComparaison(const volatile baseDescripteurImage pileImage, descImage image, int* nbScore) {
    float score;
    int nbTotalVal,sommeMinimum;
    descripteurImage tmp=pileImage->tete;
    Src pileScore=(Src)calloc(100,sizeof(ScoreImage));
    for(int j=0;j<pileImage->taillle;j++,tmp=tmp->next){
        nbTotalVal=sommeMinimum=0;
        for(int i=0;i<64;i++){
            nbTotalVal+=image.histogramme[i];
            sommeMinimum+=min(tmp->histogramme[i],image.histogramme[i]);
        }
        score=sommeMinimum/(float)nbTotalVal*100;
        if(score>0){
            pileScore[*nbScore]=(ScoreImage){score,tmp->type,tmp->id};
            (*nbScore)++;
        }
    }
    insertionSortImage(pileScore, *nbScore);

    return pileScore;
}

int compareScore(const void* a,const void* b){
    return((ScoreImage*)b)->score-((ScoreImage*)a)->score;
}

Src calculeScoreCouleur(const volatile baseDescripteurImage pileImage,char requete[20],int* nbScore) {
    int val=-1;
    for(int i=0;i<sizeof(tabVal)/sizeof(int);i++) if(strcoll(tabCouleur[i],requete)==0) val=tabVal[i];
    Src pileScore=(Src)calloc(100,sizeof(ScoreImage));
    if(val>-1){
        descripteurImage tmp=pileImage->tete;
        for(int i=0;i<pileImage->taillle;i++,tmp=tmp->next){
            if(tmp->histogramme[val]>0){
                pileScore[*nbScore]=(ScoreImage){tmp->histogramme[val],tmp->type,tmp->id};
                (*nbScore)++;
            }
        }
        
    }
    insertionSortImage(pileScore, *nbScore);
    return pileScore;
}
/*
int afficheResultatsRecherche(Src pileScore,int nbScore,listeDescripteurImage liste){
    int nbListe = config("nbListe");
    for(int i=0;i<min(nbScore,nbListe);i++){
        char *chemin=trouveCheminImage(pileScore[i].id,liste);
        printf("hehe = %s\n",chemin);
        char *nomFichier=getNomFichierImage(chemin);
        if(pileScore[i].type=='N') printf("(%d)\t%f%%\t%s.bmp\tImage noir et blanc\n",i+1,pileScore[i].score,nomFichier);
        else if(pileScore[i].type=='C') printf("(%d)\t%f%%\t%s.jpg\tImage couleur\n",i+1,pileScore[i].score,nomFichier);
        else return 0;
    }
    printf("\n\r");
    return 1;
}

int ouvreFichierImage(ScoreImage s,listeDescripteurImage liste){
    char* cmd=(char*)calloc(100,sizeof(char));
    if(s.type=='N') sprintf(cmd,"eog ../IndexationImage/BMP/%s.bmp",getNomFichierImage(trouveCheminImage(s.id,liste)));
    else sprintf(cmd,"eog ../IndexationImage/JPG/%s.jpg",getNomFichierImage(trouveCheminImage(s.id,liste)));
    if(system(cmd)!=0) return 0;
    return 1;
}
*/
char* trouverCheminImage(int id, listeDescripteurImage liste){
    char* chemin = calloc(100, sizeof(char));
    struct elementlistedescripteurimage* tmp = liste->tete;

    while(tmp != NULL){
        if(id == tmp->id){
            if(id > 49){
                sprintf(chemin, "../../BaseFichier/Image/BMP/%s",getNomFichierImage(tmp->path));
                strcat(chemin, ".bmp");
            }
            else{
                sprintf(chemin, "../../BaseFichier/Image/JPG/%s",getNomFichierImage(tmp->path));
                strcat(chemin, ".jpg");
            }
            break;
        }
        tmp = tmp->next;
    }
    return chemin;
}


char* getNomFichierImage(char* filename){
    int indice = -1;

    if(atoi(filename)>0 && atoi(filename)<64)
        return filename;

    for(int i = strlen(filename)-1; i>=0;i--){
        if(filename[i] == '/'){
            indice = i;
            break;
        }
    }
            
    char *new_filename = filename+indice+1;
    new_filename = strtok(new_filename, ".");
    return new_filename;
}

descripteurEtScoreListeImage empilerDescripteurEtScoreImage(descripteurEtScoreListeImage d, char* path, int id, int score){
    descripteurEtScoreListeImage tmp = calloc(1, sizeof(struct descripteurEtScoreImage));

    if(tmp == NULL){
        fprintf(stderr, "Error : initListeDescripteurEtScore : impossible d'empiler : tmp null");
        exit(0);
    }

    tmp->descripteur = calloc(1, sizeof(listeDescripteurImage));
    if(tmp->descripteur == NULL){
        fprintf(stderr, "Error : initListeDescripteurEtScore : impossible d'empiler : descripteur null");
        exit(0);
    }

    tmp->descripteur->path = calloc(TAILLE_MALLOC, sizeof(char));
    if(tmp->descripteur->path == NULL){
        fprintf(stderr, "Error : initListeDescripteurEtScore : impossible d'empiler : path null");
        exit(0);
    }

    tmp->score = score;
    strcpy(tmp->descripteur->path, path);
    tmp->descripteur->id = id;

    tmp->next = d;
    //printf("%d %s\n", tmp->descripteur->id, tmp->descripteur->path);


    return tmp;
}