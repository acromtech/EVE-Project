#ifndef INDEXATION_TEXTE_IN
#define INDEXATION_TEXTE_IN


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../Configuration/configuration.h"

#define TAILLE_TOKEN_MAX 120
#define SEUIL_MOT_SIGNIFICATIF 5
#define TAILLE_MALLOC 1024
#define NBLISTE 10  //PARAMETRE A METTRE DANS LE POINT CONFIG POUR FAIRE VARIER LE NOMBRE DE RESULATS


/***********************************************************/
/*****************ELEMENT MOT DESCRIPTEUR*******************/
/***********************************************************/

typedef struct _ELEMENT_{
    char *mot;
    int nbOccurence;
}ELEMENT;

void afficheELEMENT(ELEMENT);
void saisirELEMENT(ELEMENT *);
void affectELEMENT(ELEMENT*, ELEMENT);
int compareELEMENT(ELEMENT, ELEMENT);
ELEMENT *createELEMENT(char *, int);
char* elementToString(ELEMENT);


/***********************************************************/
/***********************PILE RELATED************************/
/***********************************************************/

typedef struct cellule{
    void* element;
    struct cellule *next;
}Cellule;

typedef Cellule* PILE;

PILE initPILE();
void affichePILE(PILE);
int PILEEstVide(PILE);
int PILEEstPleine(PILE);
PILE emPILE(PILE, void*);
PILE dePILE(PILE, void*);
PILE saisirPILE();
void finirPILE(PILE);
char* pileToString(PILE);
int PILEContient(PILE, ELEMENT);
int PILETailleListe(PILE);

/***********************************************************/
/********************LISTE  DESCRIPTION*********************/
/***********************************************************/

typedef struct listeDesc{
    char *path;
    int id;
    struct listeDesc *next;
}liste_descripteur;

typedef struct pathid{
    liste_descripteur *tete;
    int taille;
}*pathIdDesc;


void afficheListeDescripteur(pathIdDesc);
int listedescripteurEstVide(pathIdDesc);
pathIdDesc empilerListeDescripteur(pathIdDesc, liste_descripteur*);
pathIdDesc depileListeDescripteur(pathIdDesc, liste_descripteur*);
liste_descripteur* createPathIdDesc(char *, int);
char* pathIdDescToString(pathIdDesc);
char* listeToString(liste_descripteur* p);
pathIdDesc initListeDescripteur();

/***********************************************************/
/*******************ELEMENT  DESCRIPTION********************/
/***********************************************************/

typedef struct descrpteur{
    PILE listeELMENT;
    int tailleListe;
    int nbToken;
    int idDesc;
    struct descrpteur* next;
}descripteur;

typedef struct bDesc{
    descripteur *tete;
    int taille;
}*baseDescripteur;

int descripteurNULL(descripteur);
void afficheDESCRIPTEUR(descripteur*);
float compareDESCRIPTEUR(descripteur, descripteur);
void affectDESCRIPTEUR(descripteur*, descripteur);
void detruireDescripteur(descripteur*);
char* descripteurToString(descripteur);

/***********************************************************/
/******************BASE DESCRIPTEUR RELATED*****************/
/***********************************************************/

baseDescripteur initBaseDescripteur();
void affiche_baseDescripteur(baseDescripteur);
int baseDescripteurEstVide(baseDescripteur);
baseDescripteur empilerBaseDescripteur(baseDescripteur, descripteur);
baseDescripteur depilerBaseDescripteur(baseDescripteur, descripteur*);
baseDescripteur saisirBaseDescripteur();
char *baseDescripteurToString(baseDescripteur);
void finirBaseDescripteur(baseDescripteur);



/***********************************************************/
/*****************TABLE DESCRIPTEUR RELATED*****************/
/***********************************************************/
char *strtok_(char* str, char delim);
typedef struct idDescOcc{
    int idDesc;
    int occ;
    struct idDescOcc *next;
}*idDescOccu;

typedef struct tableDescripteur{
    char *mot;
    struct idDescOcc *idDescripteur;
    struct tableDescripteur *next;
}*tableDescript;

idDescOccu empileIdDesc(idDescOccu, int, int);
idDescOccu depileIdDesc(idDescOccu, idDescOccu);
idDescOccu createIdDesc(int, int);
tableDescript initTableDescripteur();

void affectTableDescElement(tableDescript, struct tableDescripteur);
tableDescript empileTableDescElement(tableDescript, char*, int, int);
tableDescript depilerTableDescElement(tableDescript, tableDescript);
void afficheTableDescripteur(tableDescript);


/***********************************************************/
/*****************INDEX DESCRIPTEUR RELATED*****************/
/***********************************************************/

extern baseDescripteur bd;
extern pathIdDesc listeDesc;
extern tableDescript tb_liste;
int initIdCount(baseDescripteur);
void cleanPath(char* new_path, char *path);
int bufferSize(char *buffer[]);
int countOccurence(FILE *file, char *word);
void nettoyageToken(FILE *input,char *inputPath, char *outputPath);    
FILE *filtrageToken(FILE *input, char *outputPath);
int saveDescripteur(char *, FILE*, baseDescripteur*, int, FILE*, tableDescript*);
int lienDescripteur(FILE*, int, char*, pathIdDesc*);
void tableIndex(FILE*, baseDescripteur, tableDescript*);
int indexationTexte(char *inputpath, int id_, baseDescripteur *, pathIdDesc *, tableDescript *);
int indexationBase(char *base_fichiers, baseDescripteur *, pathIdDesc *, tableDescript *);
void indexationBaseMenu();


/***********************************************************/
/****************RECHARCHER BASE LISTE TABLE****************/
/***********************************************************/
int countNumberOfLine(char *);
int isIndexer(char *);
void rechargerBaseDescripteur(char *path, baseDescripteur*);
void rechargerListeDescripteur(char *path, pathIdDesc*);
void rechargerTableDescripteur(char *path, tableDescript*);
void suprimerBaseMenu();

/***********************************************************/
/****************RECHERCHE BASE DE DONNEES******************/
/***********************************************************/

typedef struct descripteurScore{
    int id;
    float score;
    struct descripteurScore* next;
}DescripteurScore;

typedef DescripteurScore* Score;

void saisie(char[100]);
int trouveIDDescripteur(char[500],liste_descripteur*);
char* trouveChemin(int,liste_descripteur*);
PILE traitementSaisie(char[100]);
void viderBuffer();

idDescOccu rechercheTexteMot(tableDescript, char *, int *);
void rechercheTexteMotCle(pathIdDesc, tableDescript);
void rechercheTexteCompare(const volatile baseDescripteur,pathIdDesc);

int descripteurExiste(int, descripteur*,descripteur*);

Score calculeScoreBaseDescripteur(const volatile descripteur*,descripteur*,Score);
float calculeScoreDescripteur(const volatile PILE,PILE);
float calculeScoreUnitaire(const volatile PILE, ELEMENT);
Score empilerScore(Score,float,int);
Score triScore(Score);
void afficheNbScore(Score,int,pathIdDesc);

DescripteurScore choixFichier(Score);
DescripteurScore recupScore(Score,int,int);
void ouvreFichier(DescripteurScore,pathIdDesc);

void liberePILE(PILE);
void libereScore(Score);


int cheminExiste(char *);



void rechercheMotCleMenu();
void comparaisonTexteMenu();
#endif // !INDEXATION_TEXTE_IN
