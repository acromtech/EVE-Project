#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

#include "indexationImage.h"

const int tabVal[]={59,51,56,57,48,12,3,53,60,62,40,8,9,15,10,31,2,1,32,63,0,5};
const char* tabCouleur[]={"violet","fushia","orange","saumon","rouge","vert","bleu","corail","jaune","kaki","olive","vertForet","bleuMer","eau","cyan","turquoise","bleuMarine","bleuNuit","marron","blanc","noir","ardoise"};
void supprimerBaseImage()
{
    system("echo > ../IndexationImage/IndexationRechercheImage/FichierIndexation/liste_descripteur_image.csv");
    system("echo > ../IndexationImage/IndexationRechercheImage/FichierIndexation/base_descripteur_image.csv");

}

void rechercheImageHisto()
{
    baseDescripteurImage bd = initBaseDescripteurImage();
    listeDescripteurImage liste = initListeDescripteurImage();
    supprimerBaseImage();
    indexerBaseImage(&bd,&liste);
    rechercheHisto(bd,liste);
}

void rechercheImageCouleur()
{
    baseDescripteurImage bd = initBaseDescripteurImage();
    listeDescripteurImage liste = initListeDescripteurImage();
    supprimerBaseImage();
    indexerBaseImage(&bd,&liste);
    rechercheCouleur(bd,liste);
}

void rechercheCouleur(const volatile baseDescripteurImage pileImage, listeDescripteurImage liste) {
    setlocale(LC_ALL,"");
    char* requete=calloc(1,sizeof(char));
    int nbScore=0;
    Src pileScore;
    printf("\nCouleurs disponibles :\t");
    for(int i=0;i<sizeof(tabVal)/sizeof(int);i++) printf("%s ",tabCouleur[i]);
    printf("\n\n\e[1;37mFormulez une requete de couleur\e[0m\n");
    scanf("%s",requete);
    pileScore=calculeScoreCouleur(pileImage,requete,&nbScore);
    if(nbScore==0) 
    {
        printf("\n\e[1;35mAttention\e[0;35m : Aucune image ne correspond à la couleur spécifiée : Essayez d'autres couleurs\e[0m\n");
        return;
    }
    free(requete);
    if(afficheResultatsRecherche(pileScore,nbScore,liste)){
        if(ouvreFichierImage(choixFichierImage(pileScore,nbScore),liste)) printf("\n\e[1;32m-----------Recherche réalisée avec succès------------\e[0m\n\n");
        else printf("\e[1;31mErreur\e[0;31m : Impossible de lancer l'ouverture du résultat sélectionné\e[0m\n"); return;
    }else printf("\e[1;31mErreur\e[0;31m : Type d'image inconnu\e[0m\n"); return;
}

void rechercheHisto(const volatile baseDescripteurImage pileImage, listeDescripteurImage liste) {
    setlocale(LC_ALL,"");
    char* requete=calloc(1024,sizeof(char));
    char* requeteTraite=calloc(1024,sizeof(char));
    int nbScore=0;
    elementlitsetDescripteurImage tmp1;
    int id=-1;
                                                                                                                                                                                                                                                                                                                                                                                           
    tmp1=liste->tete;
    printf("\n\e[1;37mVeuillez saisir le chemin ou le nom du fichier à comparer\e[0m\n");
    scanf("%s",requete);
    sprintf(requeteTraite,"../IndexationImage/TXT/%s.txt",getNomFichierImage(requete));
    printf("%s\n",requeteTraite);
    while(tmp1 != NULL)
    {
        if(strcmp(tmp1->path, requeteTraite) == 0)
        {
            id = tmp1->id;
            break;
        }
        tmp1 = tmp1->next;
    }

    if(id==-1)printf("\e[1;35mAttention\e[0;35m : Aucune image ne correspond au chemin spécifiée\e[0m\n");
    free(requete);
    descImage *tmp=pileImage->tete;
    while(tmp!=NULL&&tmp->id!=id) tmp=tmp->next;
    if(tmp!=NULL){
        Src pileScore=calculeScoreComparaison(pileImage,*tmp,&nbScore);
        if(nbScore>0){
            if(afficheResultatsRecherche(pileScore,nbScore,liste)){
                if(ouvreFichierImage(choixFichierImage(pileScore,nbScore),liste)) printf("\n\e[1;32m-----------Recherche réalisée avec succès------------\e[0m\n\n");
                else printf("\e[1;31mErreur\e[0;31m : Impossible de lancer l'ouverture du résultat sélectionné\e[0m\n"); return;
            }else printf("\e[1;31mErreur\e[0;31m : Type d'image inconnu\e[0m\n"); return;
        }else printf("\e[1;31mErreur\e[0;31m : Aucune image ne correspond à l'image spécifiée\nEssayez d'autres images\e[0m\n"); return;
    }

    sleep(15);
}

ScoreImage choixFichierImage(Src pileScore,int tailleTabScore) {
    int index;
    ScoreImage scoreImage;
    printf("\e[1;37mVeuillez rentrer le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir\e[0m\n");
    do{
        scanf("%d",&index);
        if(index>min(tailleTabScore,NBLISTE)||index<1) printf("\e[1;35mAttention\e[0;35m : Vous ne pouvez rentrer qu'un chiffre compris entre 1 et %d\e[0m\n",min(tailleTabScore,NBLISTE));
        else scoreImage=pileScore[index-1];
    }while(index>min(tailleTabScore,NBLISTE)||index<1);
    return scoreImage;
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
    qsort(pileScore,*nbScore,sizeof(ScoreImage),compareScore);
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
        qsort(pileScore,*nbScore,sizeof(ScoreImage),compareScore);
    }
    return pileScore;
}

int afficheResultatsRecherche(Src pileScore,int nbScore,listeDescripteurImage liste){
    for(int i=0;i<min(nbScore,NBLISTE);i++){
        char *chemin=trouveCheminImage(pileScore[i].id,liste);
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

char* trouveCheminImage(int idDesc,listeDescripteurImage liste){
    elementlitsetDescripteurImage tmp;
    tmp=liste->tete;
    for(;tmp->next!=NULL;tmp=tmp->next) if(idDesc==tmp->id) return tmp->path;
    return NULL;
}   

char* getNomFichierImage(char* filename){
    char* new_filename;
    char* token=strrchr(filename,'/');
    if(token!=NULL)new_filename=token+1;
    else new_filename=filename;
    token=strrchr(new_filename,'.');
    if(token!=NULL)*token='\0';
    return new_filename;
}