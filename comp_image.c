#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "indexationImage.h"

const int tabVal[]={59,51,56,57,48,12,3,53,60,62,40,8,9,15,10,31,2,1,32,63,0,5};
const char* tabCouleur[]={"violet","fushia","orange","saumon","rouge","vert","bleu","corail","jaune","kaki","olive","vertForet","bleuMer","eau","cyan","turquoise","bleuMarine","bleuNuit","marron","blanc","noir","ardoise"};

void rechercheCouleur(const volatile baseDescripteurImage pileImage,listeDescripteurImage liste){
    setlocale(LC_ALL,"");
    char requete[20];
    Src pileScore=NULL;
    int nbScore=0;
    clock_t debut;
    clock_t fin;
    double temps=0.0;
    system("clear");
    printf("\nCouleurs disponibles :\t");
    for(int i=0;i<sizeof(tabVal)/sizeof(int);i++)printf("%s ",tabCouleur[i]);
    printf("\n\nFormulez une requete de couleur\n");
    scanf("%s",requete);
    debut=clock();
    pileScore=calculeScoreCouleur(pileImage,requete,&nbScore);
    if(nbScore>0){
        fin=clock();
        temps+=(double)(fin-debut)/CLOCKS_PER_SEC;
        system("clear");
        printf("\nRésultat(s) en %f secondes\n\n",temps);
        afficheNbScore(pileScore,NBLISTE,nbScore);
        ouvreFichier(choixFichier(pileScore,nbScore),liste);
    }
    else printf("Aucune image ne correspond a la couleur spécifiée : Essayez d'autres couleurs\n");
}

void rechercheHisto(const volatile baseDescripteurImage pileImage,listeDescripteurImage liste){
    setlocale(LC_ALL,"");
    descImage image;
    Src pileScore=NULL;
    clock_t debut;
    clock_t fin;
    double temps=0.0;
    char requete[20];
    int nbScore=0;
    system("clear");
    printf("\nVeuillez saisir le chemin du fichier à comparer\n");
    scanf("%s",requete);
    int id=trouveIDDescripteur(requete,liste);
    if(id==-1){
        printf("Veuillez rentrer un chemin de descripteur valide\n");
        return;
    }
    else{
        debut=clock();
        descripteurImage tmp;
        tmp=pileImage->tete;
        for(int i=0;i<pileImage->taillle;i++,tmp=tmp->next){
            if(tmp->id==id){
                image.id=tmp->id;
                image.type=tmp->type;
                image.taille=tmp->taille;
                image.histogramme=tmp->histogramme;
                break;
            }
        }
        pileScore=calculeScoreComparaison(pileImage,image,&nbScore);
        if(nbScore>0){
            fin=clock();
            temps+=(double)(fin-debut)/CLOCKS_PER_SEC;
            system("clear");
            printf("\nRésultat(s) en %f secondes\n\n",temps);
            afficheNbScore(pileScore,NBLISTE,nbScore);
            ouvreFichier(choixFichier(pileScore,nbScore),liste);
        }
        else printf("Aucun document ne correspond au descripteur spécifié : Essayez d'autres descripteurs\n");
    }
}

Score choixFichier(Src pileScore,int tailleTabScore){
    int index;
    Score scoreImage;
    printf("Rentrez le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir\n");
    while(1){
        scanf("%d",&index);
        if(index>NBLISTE||index<0) printf("Rentrez un chiffre compris entre 1 et %d\n",NBLISTE);
        else break;
    }
    for(int i=0;i<index&&i<tailleTabScore;i++,pileScore[i]=pileScore[i+1]){
        if(i<index&&i==tailleTabScore) printf("Cette valeur ne peut pas être lue\n");
        else{
            scoreImage.score=pileScore[i].score;
            scoreImage.id=pileScore[i].id;
        }
    }
    return scoreImage;
}

Src calculeScoreComparaison(const volatile baseDescripteurImage pileImage,descImage image,int* nbScore){
    float score=0;
    int nbTotalVal=0;
    int sommeMinimum=0;
    descripteurImage tmp;
    tmp=pileImage->tete;
    Src pileScore=(Src)calloc(100,sizeof(Score));
    for(int j=0;j<pileImage->taillle;j++,tmp=tmp->next){
        nbTotalVal=0;
        sommeMinimum=0;
        for(int i=0;i<64;i++){
            nbTotalVal+=image.histogramme[i];
            if(tmp->histogramme[i]<image.histogramme[i]) sommeMinimum+=tmp->histogramme[i];
            else sommeMinimum+=image.histogramme[i];
        }
        score=((float)sommeMinimum/(float)nbTotalVal)*100;
        if(score>0){
            pileScore[*nbScore].score=score;
            pileScore[*nbScore].id=tmp->id;
            (*nbScore)++;
        }
    }
    insertionSort(pileScore,*nbScore);
    return pileScore;
}

Src calculeScoreCouleur(const volatile baseDescripteurImage pileImage,char requete[20],int* nbScore){
    descripteurImage tmp=(descripteurImage)calloc(1,sizeof(descImage));
    tmp=pileImage->tete;
    Src pileScore=(Src)calloc(100,sizeof(Score));
    int val=-1;
    for(int i=0;i<sizeof(tabVal)/sizeof(int);i++){
        if(strcoll(tabCouleur[i],requete)==0){
            val=tabVal[i];
            break;
        }
    }
    if(val>-1){
        for(int i=0;i<pileImage->taillle;i++,tmp=tmp->next){
            if(tmp->histogramme[val]>0){
                pileScore[*nbScore].score=tmp->histogramme[val];
                pileScore[*nbScore].id=tmp->id;
                (*nbScore)++;
            }
        }
        insertionSort(pileScore,*nbScore);
    }
    return pileScore;
}

void afficheNbScore(Src pileScore,int nbMaxResultat,int tailleTabScore){
    for(int i=0;i<nbMaxResultat&&i<tailleTabScore;i++)printf("(%d)\t%d\t%f%%\n",i+1,pileScore[i].id,pileScore[i].score);
    printf("\n\r");
}

void ouvreFichier(Score s,listeDescripteurImage liste){
    char* cmd=(char*)calloc(100,sizeof(char));
    char* cheminTXT=trouveChemin(s.id,liste);
    if(cheminTXT==NULL){
        printf("Erreur : le fichier n'a pas de correspondance dans la liste\n");
        return;
    }
    /*
    char* cheminJPG=findJpegFile(cheminTXT);
    if(cheminJPG==NULL){
        printf("Erreur : le fichier JPG n'as pas été trouvé\n");
        return;
    }*/
    printf("%s\n",cheminTXT);
    sprintf(cmd,"xdg-open ./%s",cheminTXT);
    if(system(cmd)!=0) printf("Impossible de lancer la commande, %s\n",cmd);
    free(cmd);
}

char* trouveChemin(int idDesc,listeDescripteurImage liste){
    elementlitsetDescripteurImage tmp;
    tmp=liste->tete;
    while(tmp->next!=NULL){
        if(idDesc==tmp->id)
            return tmp->path;
    }
    return NULL;
}

int trouveIDDescripteur(char* chemin,listeDescripteurImage liste){
    elementlitsetDescripteurImage tmp;
    tmp=liste->tete;
    for(int i=0;i<liste->taille;i++,tmp=tmp->next)
        if(strcoll(chemin,tmp->path)==0) return tmp->id;
    return -1;
}

void insertionSort(Src tab, int size){
    int i, j;
    Score tmp;
    for (i=0;i<size-1;i++){
        for (j=0;j<size-i-1;j++){
            if (tab[j].score<tab[j+1].score){
                tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }
        }
    }
}