#ifndef INDEXATION_IMAGE_IN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NB_BITS 2
#define NBLISTE 10

typedef enum {N ='N',C ='C'}type;

typedef struct descripteur_image{
    int id;
    int *histogramme;
    int taille;
    char type;
    struct descripteur_image *next;
}descImage;

typedef descImage* descripteurImage;

typedef struct basedescripteur{
    int taillle;
    descripteurImage tete;
}*baseDescripteurImage;

baseDescripteurImage initBaseDescripteurImage();
void empilerBaseDescripteurImage(baseDescripteurImage*, struct descripteur_image);
void depilerBaseDescripteurImage(baseDescripteurImage*, struct descripteur_image*);
char* descripteurImageToString(struct descripteur_image);

typedef struct elementlistedescripteurimage{
    int id;
    char *path;
    struct elementlistedescripteurimage *next;
}*elementlitsetDescripteurImage;

typedef struct listedescripteurimage{
    int taille;
    struct elementlistedescripteurimage * tete;
}*listeDescripteurImage;
listeDescripteurImage initListeDescripteurImage();

int* quantification(char *, int, int*);
void saveDescripteurImage(baseDescripteurImage*,FILE*, struct descripteur_image);
void savelisteDescripteurImage(listeDescripteurImage*, FILE*, char*, int id);
void indexationImage(char*, baseDescripteurImage*, listeDescripteurImage*, int, int);
void indexerBaseImage(baseDescripteurImage *bd, listeDescripteurImage *listeDescripteur);
void recharger_base_indexation(char *path, baseDescripteurImage*);

typedef struct score{
    float score;
    int id;
    struct score* next;
}Score;

typedef Score* Src;

typedef struct base_score{
    int taille;
    Src tete;
}*baseScore;

void rechercheCouleur(const volatile baseDescripteurImage,listeDescripteurImage);
Src calculeScoreCouleur(const volatile baseDescripteurImage,char[20],int*);

void rechercheHisto(const volatile baseDescripteurImage,listeDescripteurImage);
Src calculeScoreComparaison(const volatile baseDescripteurImage,descImage,int*);

char* trouveChemin(int,listeDescripteurImage);
int trouveIDDescripteur(char*,listeDescripteurImage);

void afficheNbScore(Src,int,int,listeDescripteurImage);
Score choixFichier(Src,int);
void ouvreFichier(Score,listeDescripteurImage);

void insertionSort(Src,int);
char* findJpegFile(char*);

#endif // !INDEXATION_IMAGE_IN