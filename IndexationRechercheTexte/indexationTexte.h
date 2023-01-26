#ifndef INDEXATION_TEXTE_IN
#define INDEXATION_TEXTE_IN


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../Configuration/configuration.h"

#define TAILLE_TOKEN_MAX 90
#define SEUIL_MOT_SIGNIFICATIF 5
#define TAILLE_MALLOC 1024
#define NBLISTE 10  //PARAMETRE A METTRE DANS LE POINT CONFIG POUR FAIRE VARIER LE NOMBRE DE RESULATS


struct conf{
    int taille_max_token;
    int seuil_mot_significatif;
};
extern int id_;

/***********************************************************/
/*****************ELEMENT MOT DESCRIPTEUR*******************/
/***********************************************************/

typedef struct _ELEMENT_{
    char *mot;
    int nbOccurence;
}ELEMENT;

void affiche_ELEMENT(ELEMENT);
void saisir_ELEMENT(ELEMENT *);
void affect_ELEMENT(ELEMENT*, ELEMENT);
int compare_ELEMENT(ELEMENT, ELEMENT);
ELEMENT *create_EMENT(char *, int);
char* element_toString(ELEMENT);


/***********************************************************/
/***********************PILE RELATED************************/
/***********************************************************/

typedef struct cellule{
    void* element;
    struct cellule *next;
}Cellule;

typedef Cellule* PILE;

PILE init_PILE();
void affiche_PILE(PILE);
int PILE_estVide(PILE);
int PILE_estPleine(PILE);
PILE emPILE(PILE, void*);
PILE dePILE(PILE, void*);
PILE saisir_PILE();
void finir_PILE(PILE);
char* pile_toString(PILE);
int PILE_contient(PILE, ELEMENT);
int PILE_taille_liste(PILE);

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


void affiche_listedescripteur(pathIdDesc);
int listedescripteur_estVide(pathIdDesc);
pathIdDesc empiler_listedescripteur(pathIdDesc, liste_descripteur*);
pathIdDesc depile_listedescripteur(pathIdDesc, liste_descripteur*);
liste_descripteur* create_path_id_desc(char *, int);
char* pathIdDesc_toString(pathIdDesc);
char* liste_toString(liste_descripteur* p);
pathIdDesc init_listeDescripteur();

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

int descripteur_NULL(descripteur);
void affiche_DESCRIPTEUR(descripteur*);
void compare_DESCRIPTEUR(descripteur, descripteur);
void affect_DESCRIPTEUR(descripteur*, descripteur);
void detruire_descripteur(descripteur*);
char* descripteur_toString(descripteur*);

/***********************************************************/
/******************BASE DESCRIPTEUR RELATED*****************/
/***********************************************************/

baseDescripteur init_baseDescripteur();
void affiche_baseDescripteur(baseDescripteur);
int baseDescripteur_estVide(baseDescripteur);
baseDescripteur empiler_baseDescripteur(baseDescripteur, descripteur*);
baseDescripteur depilerbaseDescripteur(baseDescripteur, descripteur*);
baseDescripteur saisir_baseDescripteur();
char *baseDescripteur_toString(baseDescripteur);
void finir_baseDescripteur(baseDescripteur);



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

idDescOccu empile_idDesc(idDescOccu, int, int);
idDescOccu depile_idDesc(idDescOccu, idDescOccu);
idDescOccu create_idDesc(int, int);
tableDescript init_tableDescripteur();

void affect_tableDescElement(tableDescript, struct tableDescripteur);
tableDescript empile_tableDescElement(tableDescript, char*, int, int);
tableDescript depiler_tableDescElement(tableDescript, tableDescript);
void affiche_table_descripteur(tableDescript);


/***********************************************************/
/*****************INDEX DESCRIPTEUR RELATED*****************/
/***********************************************************/

extern baseDescripteur bd;
extern pathIdDesc listeDesc;
extern tableDescript tb_liste;
int init_id_count(baseDescripteur);
void clean_path(char* new_path, char *path);
int buffer_size(char *buffer[]);
int countOccurence(FILE *file, char *word);
void nettoyageToken(FILE *input,char *inputPath, char *outputPath);    
FILE *filtrageToken(FILE *input, char *outputPath);
int saveDescripteur(char *, FILE*, baseDescripteur*, int, FILE*, tableDescript*);
int lienDescripteur(FILE*, int, char*, pathIdDesc*);
void tableIndex(FILE*, baseDescripteur, tableDescript*);
int indexation_texte(char *inputpath, int id_, baseDescripteur *, pathIdDesc *, tableDescript *);
int indexation_base(char *base_fichiers, baseDescripteur *, pathIdDesc *, tableDescript *);
void indexationBaseMenu();


/***********************************************************/
/****************RECHARCHER BASE LISTE TABLE****************/
/***********************************************************/
int count_number_of_file_line(char *);
int isIndexer(char *);
void recharger_base_indexation(char *path, baseDescripteur*);
void recharger_liste_indexation(char *path, pathIdDesc*);
void recharger_table_indexation(char *path, tableDescript*);
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

int descripteurExiste(int,const volatile descripteur*,descripteur*);

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
