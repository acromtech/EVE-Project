#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "indexationImage.h"

const int tabVal[]={59,51,56,57,48,12,3,53,60,62,40,8,9,15,10,31,2,1,32,63,0,5};
const char* tabCouleur[]={"violet","fushia","orange","saumon","rouge","vert","bleu","corail","jaune","kaki","olive","vertForet","bleuMer","eau","cyan","turquoise","bleuMarine","bleuNuit","marron","blanc","noir","ardoise"};

void rechercheCouleur(const volatile baseDescripteurImage pileImage, listeDescripteurImage liste) {
    setlocale(LC_ALL,"");
    char* requete=calloc(1,sizeof(char));
    int nbScore=0;
    Src pileScore = NULL, tmp;
    descripteurEtScoreListe liste_resultat = NULL;
    char *jsonPath = calloc(TAILLE_MALLOC, sizeof(char));
    printf("\nCouleurs disponibles :\t");
    for(int i=0;i<sizeof(tabVal)/sizeof(int);i++) printf("%s ",tabCouleur[i]);
    do{
        printf("\n\n\e[1;37mFormulez une requete de couleur\e[0m\n");
        pileScore=calculeScoreCouleur(pileImage,requete,&nbScore);
        if(nbScore==0) printf("\n\e[1;35mAttention\e[0;35m : Aucune image ne correspond à la couleur spécifiée : Essayez d'autres couleurs\e[0m\n");
    }while(nbScore==0);
    if(afficheResultatsRecherche(pileScore,nbScore,liste)){
        for(int i = 0; i<nbScore; i++){
            jsonPath = trouverChemin(pileScore[i].id, liste);
            liste_resultat = empilerDescriipteurEtScore(liste_resultat, jsonPath,pileScore[i].id, (int)(pileScore[i].score));
        }
        if(liste_resultat != NULL){
            strcpy(jsonPath, "JSON/");
            strcat(jsonPath, getNomFichierImage(requete));
            strcat(jsonPath, ".json");
            createJson(liste_resultat, jsonPath);
        }
        if(ouvreFichierImage(choixFichier(pileScore,nbScore),liste)) printf("\n\e[1;32m-----------Recherche réalisée avec succès------------\e[0m\n\n");
        else printf("\e[1;31mErreur\e[0;31m : Impossible de lancer l'ouverture du résultat sélectionné\e[0m\n"); return;
    }else printf("\e[1;31mErreur\e[0;31m : Type d'image inconnu\e[0m\n"); return;
}

void rechercheHisto(const volatile baseDescripteurImage pileImage, listeDescripteurImage liste) {
    setlocale(LC_ALL,"");
    char* requete=calloc(1,sizeof(char));
    char* requeteTraite=calloc(1,sizeof(char));
    int nbScore=0;
    elementlitsetDescripteurImage tmp1;
    descripteurEtScoreListe liste_resultat = NULL;
    char *jsonPath = calloc(TAILLE_MALLOC, sizeof(char));
    int id=-1;
    do{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
        tmp1=liste->tete;
        printf("\n\e[1;37mVeuillez saisir le chemin ou le nom du fichier à comparer\e[0m\n");
        scanf("%s",requete);
        snprintf(requeteTraite,100,"TXT/%s.txt",getNomFichierImage(requete));
        while(tmp1 != NULL){
            if(strcmp(tmp1->path, requeteTraite) == 0){
                id = tmp1->id;
                break;
            }
            tmp1 = tmp1->next;
        }
        if(id==-1)printf("\e[1;35mAttention\e[0;35m : Aucune image ne correspond au chemin spécifiée\e[0m\n");
    }while(id==-1);
    descImage *tmp=pileImage->tete;
    while(tmp != NULL){
        if(tmp->id == id)
            break;
        tmp = tmp->next;
    }

    if(tmp!=NULL){
        Src pileScore=calculeScoreComparaison(pileImage,*tmp,&nbScore);
        if(nbScore>0){
            if(afficheResultatsRecherche(pileScore,nbScore,liste)){
                for(int i = 1; i<nbScore; i++){
                    jsonPath = trouverChemin(pileScore[i].id, liste);
                    liste_resultat = empilerDescriipteurEtScore(liste_resultat, jsonPath,pileScore[i].id, (int)(pileScore[i].score));
                }
                if(liste_resultat != NULL){
                    strcpy(jsonPath, "JSON/");
                    strcat(jsonPath, getNomFichierImage(requeteTraite));
                    strcat(jsonPath, ".json");
                    createJson(liste_resultat, jsonPath);
                }
                if(ouvreFichierImage(choixFichier(pileScore,nbScore),liste)) printf("\n\e[1;32m-----------Recherche réalisée avec succès------------\e[0m\n\n");
                else printf("\e[1;31mErreur\e[0;31m : Impossible de lancer l'ouverture du résultat sélectionné\e[0m\n"); return;
            }else printf("\e[1;31mErreur\e[0;31m : Type d'image inconnu\e[0m\n"); return;
        }else printf("\e[1;31mErreur\e[0;31m : Aucune image ne correspond à l'image spécifiée\nEssayez d'autres images\e[0m\n"); return;
    }
}

Score choixFichier(Src pileScore,int tailleTabScore) {
    int index;
    Score scoreImage;
    printf("\e[1;37mVeuillez rentrer le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir\e[0m\n");
    do{
        scanf("%d",&index);
        if(index>min(tailleTabScore,NBLISTE)||index<1) printf("\e[1;35mAttention\e[0;35m : Vous ne pouvez rentrer qu'un chiffre compris entre 1 et %d\e[0m\n",min(tailleTabScore,NBLISTE));
        else scoreImage=pileScore[index];
    }while(index>min(tailleTabScore,NBLISTE)||index<1);
    return scoreImage;
}

Src calculeScoreComparaison(const volatile baseDescripteurImage pileImage, descImage image, int* nbScore) {
    float score;
    int nbTotalVal,sommeMinimum;
    descripteurImage tmp=pileImage->tete;
    Src pileScore=(Src)calloc(100,sizeof(Score));
    for(int j=0;j<pileImage->taillle;j++,tmp=tmp->next){
        nbTotalVal=sommeMinimum=0;
        for(int i=0;i<64;i++){
            nbTotalVal+=image.histogramme[i];
            sommeMinimum+=min(tmp->histogramme[i],image.histogramme[i]);
        }
        score=sommeMinimum/(float)nbTotalVal*100;
        if((int)score>0){
            pileScore[*nbScore]=(Score){score,tmp->type,tmp->id};
            (*nbScore)++;
        }
    }
    qsort(pileScore,*nbScore,sizeof(Score),compareScore);
    return pileScore;
}

int compareScore(const void* a,const void* b){
    return((Score*)b)->score-((Score*)a)->score;
}

Src calculeScoreCouleur(const volatile baseDescripteurImage pileImage,char requete[20],int* nbScore) {
    int val=-1;
    for(int i=0;i<sizeof(tabVal)/sizeof(int);i++) if(strcoll(tabCouleur[i],requete)==0) val=tabVal[i];
    Src pileScore=(Src)calloc(100,sizeof(Score));
    if(val>-1){
        descripteurImage tmp=pileImage->tete;
        for(int i=0;i<pileImage->taillle;i++,tmp=tmp->next){
            if(tmp->histogramme[val]>0){
                pileScore[*nbScore]=(Score){tmp->histogramme[val],tmp->type,tmp->id};
                (*nbScore)++;
            }
        }
        qsort(pileScore,*nbScore,sizeof(Score),compareScore);
    }
    return pileScore;
}

int afficheResultatsRecherche(Src pileScore,int nbScore,listeDescripteurImage liste){
    int min = min(nbScore,NBLISTE);
    for(int i=1;i<min;i++){
        char *chemin=trouveChemin(pileScore[i].id,liste);
        char *nomFichier=getNomFichierImage(chemin);
        if(pileScore[i].type=='N') printf("(%d)\t%f%%\t%s.bmp\tImage noir et blanc\n",i,pileScore[i].score,nomFichier);
        else if(pileScore[i].type=='C') printf("(%d)\t%f%%\t%s.jpg\tImage couleur\n",i,pileScore[i].score,nomFichier);
        else return 0;
    }
    printf("\n\r");
    return 1;
}

int ouvreFichierImage(Score s,listeDescripteurImage liste){
    char* cmd=(char*)calloc(100,sizeof(char));
    if(s.type=='N') sprintf(cmd,"xdg-open ./BMP/%s.bmp",getNomFichierImage(trouveChemin(s.id,liste)));
    else sprintf(cmd,"xdg-open ./JPG/%s.jpg",getNomFichierImage(trouveChemin(s.id,liste)));
    if(system(cmd)!=0) return 0;
    return 1;
}

char* trouveChemin(int idDesc,listeDescripteurImage liste){
    elementlitsetDescripteurImage tmp;
    tmp=liste->tete;
    for(;tmp->next!=NULL;tmp=tmp->next) if(idDesc==tmp->id) return tmp->path;
    return NULL;
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



// Partie JAVA

void createJson(descripteurEtScoreListe liste, char *jsonName){
    char *string;
    char *idToString = calloc(10, sizeof(char));
    int id_ = 1;
    FILE *json = fopen(jsonName, "w");
    descripteurEtScoreListe tmp = NULL;
    cJSON *jsonFile = NULL;
    cJSON *descripteur = NULL;
    cJSON *id = NULL;
    cJSON *score = NULL;
    cJSON *path = NULL;    
    
    while(liste != NULL){
        tmp = empilerDescriipteurEtScore(tmp, liste->descripteur->path, liste->descripteur->id, liste->score);
        liste = liste->next;
    }


    jsonFile = cJSON_CreateObject();
    if(jsonFile == NULL){
        fprintf(stderr, "Error : createJson : impossible de creer le JSON");
        exit(0);
    }
    int i = 0;
    while(tmp != NULL){
        
        descripteur = cJSON_CreateObject();
        if(descripteur == NULL){
            fprintf(stderr, "Error : createJson : impossible de creer le JSON");
            exit(0);
        }
        sprintf(idToString, "%d", i);
        cJSON_AddItemToObject(jsonFile, idToString, descripteur);

        id = cJSON_CreateNumber(tmp->descripteur->id);
        if(id == NULL){
            fprintf(stderr, "Error : createJson : impossible de creer le JSON");
            exit(0);
        }
        cJSON_AddItemToObject(descripteur,"id" , id);

        score = cJSON_CreateNumber(tmp->score);
        if(id == NULL){
            fprintf(stderr, "Error : createJson : impossible de creer le JSON");
            exit(0);
        }
        cJSON_AddItemToObject(descripteur, "score", score);

        path = cJSON_CreateString(tmp->descripteur->path);
        if(path == NULL){
            fprintf(stderr, "Error : createJson : impossible de creer le JSON");
            exit(0);
        }
        cJSON_AddItemToObject(descripteur, "path", path);
        tmp = tmp->next;
        i++;
    }

    string = cJSON_Print(jsonFile);
    if(string == NULL){
        fprintf(stderr, "Error : createJson : impossible de creer le JSON");
        exit(0);
    }

    fprintf(json,"%s", string);
    
    cJSON_Delete(jsonFile);
    free(idToString);
    fclose(json);
}

descripteurEtScoreListe initListeDescripteurEtScore(){
    descripteurEtScoreListe d = calloc(1, sizeof(struct descripteurEtScore));
    if(d == NULL){
        fprintf(stderr, "Error : initListeDescripteurEtScore : impossible d'initialiser");
        exit(0);
    }
    return d;
}

descripteurEtScoreListe empilerDescriipteurEtScore(descripteurEtScoreListe d, char* path, int id, int score){
    descripteurEtScoreListe tmp = initListeDescripteurEtScore();

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


    return tmp;
}

char* trouverChemin(int id, listeDescripteurImage liste){
    char* chemin = NULL;
    struct elementlistedescripteurimage* tmp = liste->tete;

    while(tmp != NULL){
        if(id == tmp->id){
            chemin = tmp->path;
            break;
        }
        tmp = tmp->next;
    }
    return chemin;
}
    