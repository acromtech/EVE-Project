#include "indexationTexte.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

//Role :
//Auteur :

int taille_base_descripteur = 0;
int taille_liste_descripteur = 0;
int id_ = 0;


/***********************************************************/
/*****************ELEMENT MOT DESCRIPTEUR*******************/
/***********************************************************/

void affiche_ELEMENT(ELEMENT e){
    printf("Mot = %s occurence = %d ", e.mot, e.nbOccurence);
}

void saisir_ELEMENT(ELEMENT * ptr_e){
    int i;
    ptr_e->mot = calloc(TAILLE_TOKEN_MAX, sizeof(char));
    printf("Saisir le mot : ");
    scanf("%s", ptr_e->mot);
    if(ptr_e->mot[strlen(ptr_e->mot)-1] == '\n')
        ptr_e->mot[strlen(ptr_e->mot)-1] = '\0';
    printf("Saisir son nombre d'occurence : ");
    scanf("%d", &(ptr_e->nbOccurence));
}

void affect_ELEMENT(ELEMENT *e, ELEMENT e_){
    e->mot = calloc(TAILLE_TOKEN_MAX, sizeof(char));
    for(int i = 0; i < strlen(e_.mot); i++)
        e->mot[i] = e_.mot[i];
    e->nbOccurence = (e_.nbOccurence);
}

ELEMENT* create_EMENT(char *mot, int nbOccurence){
    ELEMENT *e = calloc(1, sizeof(ELEMENT));
    if(e == NULL){
        fprintf(stderr,"createELEMENT : Error: Failed to allocate : Out of memory\n");
        exit(0);
    }
    e->mot = calloc(TAILLE_TOKEN_MAX, sizeof(char));
    if(e == NULL){
        fprintf(stderr,"createELEMENT : Error: Failed to allocate : Out of memory\n");
        exit(0);
    }
    strcpy(e->mot, mot);
    e->nbOccurence = nbOccurence;
    return e;
}

int compare_ELEMENT(ELEMENT a, ELEMENT b){ // renvoie 0 en cas d'égalité, 1 en cas de a>b et -1 si a est plus petit que b
    return (strcmp(a.mot, b.mot) == 0 && (a.nbOccurence == b.nbOccurence) == 1);
}

char* element_toString(ELEMENT e){
    char* result = malloc(sizeof(char) * 1000);
    sprintf(result, "%s %d", e.mot, e.nbOccurence);
    return result;
}

/***********************************************************/
/*******************ELEMENT  DESCRIPTION********************/
/***********************************************************/

void affiche_DESCRIPTEUR(descripteur* d){
    printf("[ "); affiche_PILE(d->listeELMENT);
    printf(" %d, ", d->tailleListe);
    printf(" %d", d->nbToken);
    printf(" ]\n");
}

float compareDESCRIPTEUR(descripteur d1, descripteur d2)
{
    float egale = 0;
    int count = 0;
    PILE tmp = d1.listeELMENT;
    if(d1.tailleListe == 0 || d2.tailleListe == 0)
        return egale;
    
    if(d1.tailleListe == d2.tailleListe)
    {
        while(d2.listeELMENT != NULL)
        {
            
            while(tmp != NULL)
            {
                if(strcmp(((ELEMENT*)tmp->element)->mot, ((ELEMENT*)d2.listeELMENT->element)->mot) == 0)
                {
                    egale = ((ELEMENT*)d2.listeELMENT->element)->nbOccurence - ((ELEMENT*)tmp->element)->nbOccurence;
                    if(egale == 0) 
                        count++;
                }
                tmp = tmp->next;
            }
            tmp = d1.listeELMENT;
            d2.listeELMENT = d2.listeELMENT->next;
        }
        printf("%d %d\n",count, d1.tailleListe);
        egale = (float)count/d1.tailleListe;
        printf("%d %f\n", d1.idDesc, egale);
    }
    return egale;
}
void affect_DESCRIPTEUR(descripteur *desc_dest, descripteur desc){
    PILE tmp = desc.listeELMENT;
    while(tmp != NULL){
        desc_dest->listeELMENT = emPILE(desc_dest->listeELMENT, tmp->element);
        tmp = tmp->next;
    }
    desc_dest->nbToken = desc.nbToken;
    desc_dest->tailleListe = desc.tailleListe;
    desc_dest->idDesc = desc.idDesc;
}

char* descripteur_toString(descripteur d){
    char* result = calloc(TAILLE_MALLOC, sizeof(char));
    if(result == NULL){
        fprintf(stderr, "Error : descripteur_toString : malloc failed\n");
        exit(0);
    }
    sprintf(result, "%d %d %d %s",
            d.idDesc, d.tailleListe, d.nbToken, pile_toString(d.listeELMENT));
    return result;
}

/***********************************************************/
/********************LISTE  DESCRIPTION*********************/
/***********************************************************/
pathIdDesc init_listeDescripteur(){
    pathIdDesc p = calloc(1, sizeof(struct pathid));
    if(p != NULL) return p;
    else{
        fprintf(stderr, "Error : init listeDescripteur failed\n");
        exit(0);
    }
}

liste_descripteur* create_path_id_desc(char *path, int id){
    liste_descripteur* p = calloc(1, sizeof(struct pathid));
    if(p == NULL){
        fprintf(stderr, "Error : impossible to create path id descriptor.\n");
        exit(0);
    }
    p->path = calloc(strlen(path)+1, sizeof(char));
    if(p->path == NULL){
        fprintf(stderr, "Error : impossible to create path part of path id descriptor.\n");
        exit(0);
    }
    strcpy(p->path, path);
    p->id = id;
    return p;
}

pathIdDesc empiler_listedescripteur(pathIdDesc p, liste_descripteur* element){
    liste_descripteur *tmp = calloc(1, sizeof(liste_descripteur));
    tmp->path = calloc(TAILLE_MALLOC, sizeof(char));
    if(element == NULL || tmp == NULL || tmp->path == NULL){
        fprintf(stderr, "Error : impossible to stack the path id descriptor.\n");
        exit(0);
    }
    else{
        //printf("%s %d\n", element->path, element->id);
        tmp->id = element->id;
        strcpy(tmp->path, element->path);
        tmp->next = p->tete;
        p->tete = tmp;
        p->taille++;
        return p;
    }
}

pathIdDesc depile_listedescripteur(pathIdDesc p, liste_descripteur* element){
    liste_descripteur* tmp = NULL;    
    if(p != NULL){
        tmp = p->tete;
        strcpy(element->path,tmp->path);
        (*element).id = (*tmp).id;
        p->taille--;
        p->tete = p->tete->next;
        free(tmp);
    }
    return p;
}

char* liste_toString(liste_descripteur* p){
    char* result = calloc(TAILLE_MALLOC, sizeof(char));
    if(result == NULL){
        fprintf(stderr, "Error : liste_toString : failed to allocate memory\n");
        exit(0);
    }
    sprintf(result, "%s %d", p->path, p->id);
    return result;
}

void affiche_listedescripteur(pathIdDesc lb){
    while(lb != NULL && lb->tete != NULL){
        printf("%s %d\n", lb->tete->path, lb->tete->id);
        lb->tete = lb->tete->next;
    }
}
/***********************************************************/
/***********************PILE RELATED************************/
/***********************************************************/
PILE init_PILE(){
    return NULL;
}

int PILE_estVide(PILE p){ // Si la pile est vide alors p est a -1 alors on renvoit le resultat de l'expression booléen p == -1
    return (p == NULL);
}

void affiche_PILE(PILE p){
    PILE tmp = p ;
    // Verifier si la pile est vide
    if(PILE_estVide(p)) printf("[ ]\n");
    // Verifier si la pile n'est pas vide la parcourrir et afficher les elements du tableau en partant de la tete à l'indice 0
    else{
        printf("[ ");
        while(tmp !=NULL){
            affiche_ELEMENT(*(ELEMENT*)tmp->element);
            tmp = tmp->next;
        }
        printf("]\n");
    }
}

char* pile_toString(PILE p){
    char* result = calloc(1024, sizeof(char));
    char* temp = calloc(1024, sizeof(char));
    if(result == NULL || temp == NULL){
        fprintf(stderr, "Error : pile_toString : failed to allocate memory\n");
        exit(0);
    }
    while(p != NULL){
        sprintf(temp, "%s %d", ((ELEMENT*)p->element)->mot, ((ELEMENT*)p->element)->nbOccurence);
        strcat(result, temp); 
        p = p->next;
        if(p != NULL) strcat(result, " ");
    }
    return result;
}

int PILE_contient(PILE p, ELEMENT element){
    int contient = 0;
    while(p != NULL){
        contient = compare_ELEMENT(*(ELEMENT*)p->element, element);
        if(contient == 1) break;
        p = p->next;
    }
    return contient;
}

PILE emPILE(PILE p, void *x){
    Cellule *e = (Cellule*)calloc(1,sizeof(Cellule));
    if(!e){
        fprintf(stderr,"emPILE : Error: Failed to allocate : Out of memory\n");
        exit(0);
    }
    e->element = (ELEMENT*)calloc(1,sizeof(ELEMENT));
    if(!(e->element)){
        fprintf(stderr,"emPILE : Error: Failed to allocate : Out of memory\n");
        exit(0);
    }
    affect_ELEMENT((ELEMENT*)e->element, *(ELEMENT*)x);
    if(PILE_contient(p, *(ELEMENT*)x) == 1){
        free(e);
        return p;
    }
    else{
        e->next = p;
        return e;
    }
}

PILE dePILE(PILE p, void *x){
    Cellule *d;
    if(PILE_estVide(p)) fprintf(stderr, "La pile est vide. Il est impossible d'en depiler un element.\n");
    else{
        affect_ELEMENT(x, *(ELEMENT*)p->element);
        d = p;
        p = p->next;
        free(d);
    }
    return p;
}

PILE saisir_PILE(){
    PILE p = init_PILE();
    int num, i;
    ELEMENT  number;
    affiche_PILE(p);
    printf("Combien d'élément voulez vous entrer ? \n");
    scanf("%d", &num);
    if(num< 0){
        while(num< 0){
            printf("Le nombre %d n'est pas valide. Veuillez entrer un nombre compris entre 0 et 10 s'il vous plait !", num);
            scanf("%d", &num);
        }
    }
    if(num == 0) printf("Aucun nombre ne sera ajouter à la pile.\n");
    else{
        printf("Veillez saisir sucessivement les %d nombres à ajouter à la pile :\n ", num);
        for(i=0; i<num; i++){
            printf("L'élément numero %d : \n", i+1);
            saisir_ELEMENT(&number);
            p = emPILE(p, &number);
        }
    }
    return p;
}

void finir_PILE(PILE p){
    ELEMENT x;
    if(!PILE_estVide(p)) while(p != NULL) p = dePILE(p, &x);
    
}

int descripteur_NULL(descripteur d){
    return (d.listeELMENT == NULL);
}

int PILE_taille_liste(PILE p){
    int cont = 0;
    while(p != NULL){
        cont++;
        p = p->next;
    }
    return cont;
}

/***********************************************************/
/******************BASE DESCRIPTEUR RELATED*****************/
/***********************************************************/

baseDescripteur init_baseDescripteur(){
    baseDescripteur desc = calloc(1, sizeof(struct bDesc));
    if(desc != NULL){
        desc->tete = calloc(1, sizeof(descripteur));
        if(desc->tete != NULL) return desc;
    }
    fprintf(stderr, "Error : init_base_Descripteur : out of memory\n");
    exit(0);
}

void affiche_baseDescripteur(baseDescripteur baseDesc){
    descripteur* tmp = baseDesc->tete;
    if(baseDescripteur_estVide(baseDesc)) printf("{ }");
    else{
        printf("{ ");
        while(tmp !=NULL){
            affiche_DESCRIPTEUR(tmp);
            tmp = tmp->next;
        }
        printf("}\n");
    }
}
int baseDescripteur_estVide(baseDescripteur baseDesc){
    return (baseDesc->tete == NULL);
}

int contient_descripteur(baseDescripteur baseDesc, descripteur desc){
    int contient = 0;
    descripteur *d = baseDesc->tete;
    while(d != NULL){
        if(d->idDesc == desc.idDesc) contient = 1;
        d = d->next;
    }
    return contient;
}

baseDescripteur empiler_baseDescripteur(baseDescripteur baseDesc, descripteur d){
    descripteur *desc = (descripteur*)calloc(1, sizeof(descripteur));
    if(desc == NULL){
        fprintf(stderr, "Error : empiler descripteur failed\n");
        exit(0);
    }
    //printf("%s\n", descripteur_toString(d));
    desc->idDesc = d.idDesc;
    desc->nbToken = d.nbToken;
    desc->tailleListe = d.tailleListe;
    desc->listeELMENT = d.listeELMENT;
    //printf("%s\n\n", descripteur_toString(*desc));
    desc->next = baseDesc->tete;
    baseDesc->tete = desc; 
    baseDesc->taille++;
    return baseDesc;
}

baseDescripteur depilerbaseDescripteur(baseDescripteur baseDesc, descripteur* d){
    descripteur *desc_tmp;
    if(baseDescripteur_estVide(baseDesc)) fprintf(stderr, "Error : impossible de retirer un descripteur : base vide.n");
    else{
        affect_DESCRIPTEUR(desc_tmp, *(baseDesc->tete));
        affect_DESCRIPTEUR(d, *desc_tmp);
        baseDesc->tete = baseDesc->tete->next;
        detruire_descripteur(d);
        baseDesc->taille--;
    }
    return baseDesc;
}

void detruire_descripteur(descripteur* d){
    finir_PILE(d->listeELMENT);
    free(d);
}

void finir_baseDescripteur(baseDescripteur baseDesc){
    descripteur *d;
    while(baseDesc != NULL){
        affect_DESCRIPTEUR(d, *(baseDesc->tete));
        baseDesc->tete = baseDesc->tete->next;
        free(d);
    }
    free(baseDesc);
}

char *baseDescripteur_toString(baseDescripteur bd){
    char * s = calloc(2048, sizeof(char));
    while(bd->tete != NULL){
        strcat(s, descripteur_toString(*(bd->tete)));
        strcat(s, "\n");
        bd->tete = bd->tete->next;
    }
    return s;
}

/***********************************************************/
/*****************TABLE DESCRIPTEUR RELATED*****************/
/***********************************************************/

int is_in(idDescOccu p, int id){
    int contient = 0;
    while(p!=NULL){
        if(p->idDesc == id){   
            contient =  1;
            break;
        } 
        p = p->next;
    }
    return contient;
}

char *idDescOccu_toString(idDescOccu p){
    char *result = calloc(1000, sizeof(char));
    char *tmp = calloc(1000, sizeof(char));
    while(p!=NULL){
        sprintf(tmp, "%d %d", p->idDesc, p->occ);
        strcat(result, tmp);
        p = p->next;
        if(p != NULL) strcat(result,",");
    }
    free(tmp);
    return result;
}

idDescOccu empile_idDesc(idDescOccu p,int id, int occ){
    idDescOccu tmp = create_idDesc(id, occ);
    idDescOccu tmp_p = p;
    if(is_in(p, id) == 1) return p;
    else{
        tmp->next = p;
        return tmp;
    }
}
idDescOccu depile_idDesc(idDescOccu p, idDescOccu e){
    idDescOccu tmp = p;
    if(p != NULL){
        e = create_idDesc(p->idDesc, p->occ);
        p = p->next;
        free(tmp);
    }
    return p;
}

idDescOccu create_idDesc(int id, int oc){
    idDescOccu tmp = calloc(1, sizeof(struct idDescOcc));
    if(tmp == NULL){
        fprintf(stderr, "Error : can't create *idDescOcc element.\n ");
        exit(0);
    }
    tmp->idDesc = id;
    tmp->occ = oc;
    return tmp;
}

void affect_tableDescElement(tableDescript p, struct tableDescripteur e){
    p->mot = calloc(strlen(e.mot), sizeof(char));
    if(p->mot == NULL){
        fprintf(stderr, "Error : can't create mot de tableIndex.\n ");
        exit(0);
    }
    strncpy(p->mot, e.mot, strlen(e.mot));
    p->idDescripteur = (create_idDesc(e.idDescripteur->idDesc, e.idDescripteur->occ));
}

tableDescript empile_tableDescElement(tableDescript p, char* mot, int id, int occ){
    tableDescript tmp = calloc(1, sizeof(struct tableDescripteur));
    tableDescript tmp_p = p;
    int found = 0;
    if(!tmp){
        fprintf(stderr, "Error : can't create element in empiler_tableDescript.\n ");
        exit(0);
    }
    tmp->mot = calloc(strlen(mot)+1, sizeof(char));
    if(tmp->mot == NULL){
        fprintf(stderr, "Error : can't create mot de tableIndex in empiler.\n ");
        exit(0);
    }
    strcpy(tmp->mot, mot);
    tmp->idDescripteur = (create_idDesc(id, occ));
    tmp->next = p;
    return tmp;
}

tableDescript creer_tableDescElement(tableDescript tb, char *token, idDescOccu id_ds){
    tableDescript tmp = calloc(1, sizeof(struct tableDescripteur));
    if(!tmp){
        fprintf(stderr, "Error : can't create element in empiler_tableDescript.\n ");
        exit(0);
    }
    tmp->mot = calloc(strlen(token)+1, sizeof(char));
    if(tmp->mot == NULL){
        fprintf(stderr, "Error : can't create mot de tableIndex in empiler.\n ");
        exit(0);
    }
    strcpy(tmp->mot, token);
    tmp->idDescripteur = (create_idDesc(id_ds->idDesc, id_ds->occ));
    return tmp;
}

tableDescript depiler_tableDescElement(tableDescript p, tableDescript d){
    tableDescript tmp = p;
    if(p != NULL){
        affect_tableDescElement(d, *p);
        p = p->next;
        free(tmp);
    }
    return p;
}

char *tableDescripteur_toString(tableDescript tb){
    char *result = calloc(TAILLE_MALLOC, sizeof(char));
    if(result == NULL){
        fprintf(stderr, "Error : pile_toString : failed to allocate memory\n");
        exit(0);
    }
    sprintf(result, "%s %d %d\n", tb->mot, tb->idDescripteur->idDesc, tb->idDescripteur->occ);
    return result;
}

void affiche_table_descripteur(tableDescript p){
    while(p != NULL){
        printf("%s %d %d\n",p->mot, p->idDescripteur->idDesc, p->idDescripteur->occ);
        p = p->next;
    }
}

/***********************************************************/
/*****************INDEX DESCRIPTEUR RELATED*****************/
/***********************************************************/

void clean_path(char *new_path, char *path){
    int i, len = strlen(path);
    strncpy(new_path, path, len);
    for(i = len-1; i >= 0; i--)
        if(new_path[i] == '.'){
            new_path[i] = '\0';
            break;
        }
}

void nettoyageToken(FILE *input,char *inputPath, char *outputPath){
    char *command = calloc(1024, sizeof(char)); // Créer un tableau qui contiendra une commande pour les appels system
    // Génération de la commande pour l'appel du script de génération du fichier .clean
    sprintf(command, "cat %s > %s.clean", inputPath, outputPath); // "cat nom_du_fichier.xml > nom_du_fichier_entrer_sans_son_extenxion.clean"
        // printf("la commande pour copier le contenu du fichier xml dans le fichier .clean  : %s\n", command);
    system(command); // appel system pour lancer la commande cat 
    sprintf(command, "chmod u+x ../IndexationRechercheTexte/script_clean.sh");
    system(command); // appel system pour autoriser l'exécution du script
    sprintf(command, "../IndexationRechercheTexte/script_clean.sh %s.clean", outputPath); // "./script_clean.sh nom_du_fichier_entrer_sans_son_extenxion.clean"
        // printf("la commande pour lancer le script de génération du fichier .clean nettoyé : %s\n", command);
    system(command); // appel system pour lancer la commande pour le script shell
    free(command);
}

FILE *filtrageToken(FILE *input, char *outputPath){
    char token[TAILLE_TOKEN_MAX];
    char *stopwords[] = {"t'","lorsqu'", "ces", "ils","t", "sont" ,"n'", "s'", "m'","est", "une", "avec", "qui","à","ainsi","autre","aux", "au","avec", "d'","ce","ceci","cela","celle","celles","celui","ceux","chaque","ci","comme","comment","dans","de","des","du","elle","en","et","eu","eux","il","je","la","le","les","leur","lui","ma","mais","me","même","mes","moi","mon","ne","nos","notre","nous","on","ou","par","pas","pour","qu'","que","qui","sa","se","ses","son","sur","ta","te","tes","toi","ton","tu","un","une","vos","votre","vous","l'", "a", "an", "and", "are", "as", "at", "be", "by", "for", "from", "has", "he", "in", "is", "it", "its", "of", "on", "that", "the", "to", "was", "were", "will", "with"}; // Créer un tableau de stopwords
    int is_stopword = 0, i, buffer_smal = 0;
    FILE *cpy = fopen("cpy.txt", "w");
    int stopwordsBufferSize = buffer_size(stopwords);
    char *mot, *tmp;
    FILE *output_TOK = fopen(outputPath, "w");
    if (output_TOK == NULL || cpy == NULL){
        fprintf(stderr, "Impossible d'ouvrir le fichier %s ", outputPath);
        exit(0);
    }
    while(fscanf(input,"%s[^n]", token) != EOF){
        for(int i=0; i<stopwordsBufferSize; i++){
            if(strcmp(token, stopwords[i]) == 0 || strlen(token) <= 5){
                is_stopword = 1;
                break;
            }
        }
        if(is_stopword == 0){
            fprintf(cpy, "%s ", token);
            fprintf(output_TOK, "%s ", token);
        }
        is_stopword = 0;
    }
    fclose(cpy);
    return output_TOK;
}

int countOccurence(FILE *input, char *word){
    int count = 0, i;
    char token[TAILLE_TOKEN_MAX];
    // Lire le fichier ligne par ligne
    while(fscanf(input,"%s[^n]", token) != EOF){
        if(strcmp(token,word) == 0) count++;
    }
    return count;
}

int saveDescripteur(char* inputPath, FILE* baseDesct, baseDescripteur* bd, int idDesc, FILE* tableDescripteur, tableDescript *tb){
    char token[TAILLE_TOKEN_MAX];
    int count = 0, found = 0;
    descripteur* d = calloc(1, sizeof(descripteur));
    ELEMENT *e = calloc(1, sizeof(ELEMENT));
    PILE tmp;
    FILE *input, *cpy;
    cpy = fopen("cpy.txt", "r");
    int seuil_mot_significatif = config("seuilMotSignificatif");
    
       
    if(cpy == NULL){
        fprintf(stderr, "cpy : impossible d'ouvrir cpy.\n");
        exit(0);
    }
    if(d == NULL || e == NULL){
        fprintf(stderr,"saveDescripteur : Error: Failed to allocate : Out of memory\n");
        exit(0);
    }
    d->listeELMENT = init_PILE();
    d->next = NULL;
        while(fscanf(cpy,"%s[^n]", token) != EOF){
            input = fopen(inputPath, "r");
            if(input == NULL){
                fprintf(stderr,"saveDescripteur : imposible d'ouvrir %s\n", inputPath);
                exit(0);
            }
            count = countOccurence(input, token);
            fclose(input);
            if(count >=  seuil_mot_significatif){
                tmp = d->listeELMENT;
                while(tmp != NULL){
                    if(strcmp(((ELEMENT*)tmp->element)->mot, token) == 0){
                        found = 1;
                        break;
                    }
                    tmp = tmp->next;
                }
                if(found == 0){
                    e->mot = calloc(strlen(token), sizeof(char));
                    strcpy(e->mot, token);
                    e->nbOccurence = count;
                    d->listeELMENT = emPILE(d->listeELMENT, e);
                    *tb = empile_tableDescElement(*tb, token, idDesc, count);
                    fprintf(tableDescripteur, "%s", tableDescripteur_toString(*tb));
                }
                found = 0;
            }
            d->nbToken++;
        }
    d->tailleListe = PILE_taille_liste(d->listeELMENT);
    d->idDesc = idDesc;
    if(d->nbToken != 0){
        *bd = empiler_baseDescripteur(*bd, *d);
        fprintf(baseDesct, "%s\n", descripteur_toString(*d));
    }    
    free(d);
    free(e);
    fclose(cpy);
    return 1;
}

int lienDescripteur(FILE* listDesc, int idDesc, char* inputPath, pathIdDesc *listeDesc){
    liste_descripteur* tmp = calloc(1, sizeof(struct listeDesc));
    if(tmp == NULL){
        fprintf(stderr, "Error : listeDesc : malloc failed\n");
        exit(0);
    }
    tmp =  create_path_id_desc(inputPath, idDesc);
    *listeDesc = empiler_listedescripteur(*listeDesc,tmp); 
    fprintf(listDesc, "%s\n", liste_toString(tmp));
    return 1;
}

int buffer_size(char *buffer[]){
    int i;
    for(i = 1; buffer[i] != NULL; i++);
    return --i;
}

int indexation_texte(char *inputpath, int id_, baseDescripteur *bd, pathIdDesc *listeDesc, tableDescript *tb_liste){
    FILE *input = fopen(inputpath, "r"); // Ouvrir le fichier en lecture
    char *stopwords[] = {"n'", "s'", "m'","est", "une", "avec", "qui","à","ainsi","autre","aux", "au","avec", "d'","ce","ceci","cela","celle","celles","celui","ceux","chaque","ci","comme","comment","dans","de","des","du","elle","en","et","eu","eux","il","je","la","le","les","leur","lui","ma","mais","me","même","mes","moi","mon","ne","nos","notre","nous","on","ou","par","pas","pour","qu'","que","qui","sa","se","ses","son","sur","ta","te","tes","toi","ton","tu","un","une","vos","votre","vous","l'", "a", "an", "and", "are", "as", "at", "be", "by", "for", "from", "has", "he", "in", "is", "it", "its", "of", "on", "that", "the", "to", "was", "were", "will", "with"}; // Créer un tableau de stopwords
    int stopwordsBufferSize = buffer_size(stopwords);
    char *outputPath = calloc(TAILLE_MALLOC, sizeof(char));
    clean_path(outputPath, inputpath);
    char output[TAILLE_MALLOC];
    strcpy(output, outputPath); 
    FILE *output_TOK, *baseDescriptr, *listeDescripteur, *cpy, *tb;
    int is_stopword = 0, nbMotFichierTok = 0, id = id_;
    //printf("debut indexation ficher : %s. \n", inputpath);
    nettoyageToken(input, inputpath, output);
    fclose(input);
    sprintf(outputPath, "%s.clean", output);
    input = fopen(outputPath, "r");
    if(input == NULL){
        fprintf(stderr,"Error : indexationTexte could not open files for writing.\n");
        exit(0);
    }
    sprintf(outputPath, "%s.tok", output);
    output_TOK = filtrageToken(input, outputPath);
    clean_path(outputPath, inputpath);
    fclose(input);
    fclose(output_TOK);
    sprintf(outputPath, "%s.tok", output);
    baseDescriptr = fopen("../BaseFichiersTexte/FichiersDeDescription/base_descripteur.csv", "a");
    listeDescripteur = fopen("../BaseFichiersTexte/FichiersDeDescription/liste_descripteur.csv", "a");
    tb = fopen("../BaseFichiersTexte/FichiersDeDescription/table_descripteur.csv", "a");
    if(baseDescriptr == NULL  || listeDescripteur == NULL || tb == NULL){
        fprintf(stderr,"Error : could not open files for writing.\n");
        exit(0);
    }
    saveDescripteur(outputPath, baseDescriptr, bd, (*bd)->taille, tb, tb_liste);
    lienDescripteur(listeDescripteur, id, inputpath, listeDesc);
    //printf("fin indexation : %s\n", inputpath);
    sprintf(outputPath, "rm cpy.txt");
    fclose(baseDescriptr);
    fclose(listeDescripteur);
    fclose(tb);
    free(outputPath);
    return (*bd)->tete->idDesc;
}

int isIndexer(char *path)
{
    
    char *command = calloc(TAILLE_MALLOC, sizeof(char));
    FILE *fp = fopen("../BaseFichiersTexte/FichiersDeDescription/liste_descripteur.csv", "r");

    if(fp == NULL || command == NULL)
    {
        fprintf(stderr, "Error : out of memory\n");
        exit(0);
    }

    int is_indexed = 0;
    while(fscanf(fp, "%s[^\n]", command) != EOF)
    {
        if(strcmp(command, path) == 0)
        {
            is_indexed = 1;
            break;
        }
    }
    return is_indexed;
}
void suprimerBaseMenu()
{
    system("echo > ../BaseFichiersTexte/FichiersDeDescription/base_descripteur.csv");
    system("echo > ../BaseFichiersTexte/FichiersDeDescription/liste_descripteur.csv");
    system("echo > ../BaseFichiersTexte/FichiersDeDescription/table_descripteur.csv");
    system("rm ../BaseFichiersTexte/*.clean ../BaseFichiersTexte/*.tok ../BaseFichiersTexte/files.txt");
}
void indexationBaseMenu()
{
    baseDescripteur bd = init_baseDescripteur();
    pathIdDesc liste = init_listeDescripteur();
    tableDescript tb_desc = NULL;

    recharger_base_indexation("../BaseFichiersTexte/FichiersDeDescription/base_descripteur.csv",&bd);
    recharger_liste_indexation("../BaseFichiersTexte/FichiersDeDescription/liste_descripteur.csv", &liste);
    recharger_table_indexation("../BaseFichiersTexte/FichiersDeDescription/table_descripteur.csv", &tb_desc);

    indexation_base("../BaseFichiersTexte/", &bd, &liste, &tb_desc);
    sleep(10);
}

int indexation_base(char *base_fichiers, baseDescripteur *bd, pathIdDesc *listeDesc, tableDescript *tb_liste){
    char *command = calloc(1024, sizeof(char)), *path = calloc(1024, sizeof(char)), *mot; // Créer un tableau qui contiendra une commande pour les appels system
    FILE *deja_indexer, *files;
    int is_indexed = 0;
    sprintf(command, "ls %s*.xml > %sfiles.txt", base_fichiers, base_fichiers);
    system(command);

    sprintf(command, "%sfiles.txt", base_fichiers);
    files = fopen(command, "r");
    if(files == NULL || path == NULL || command == NULL){
        fprintf(stderr, "indexation_base_texte : ouveture impossible des fichiers.\n");
        exit(0);
    }
    while(fscanf(files,"%s[^n]", command) != EOF)
    {        
        is_indexed = isIndexer(command);
        if(is_indexed == 0){
            //printf("%s\n", command);
            indexation_texte(command, (*bd)->taille, bd, listeDesc, tb_liste);
        }
    }
    return 1;
}

/***********************************************************/
/****************RECHARCHER BASE LISTE TABLE****************/
/***********************************************************/
int count_number_of_file_line(char *path){
    int count = 0;
    char *command = calloc(TAILLE_MALLOC, sizeof(char));
    if(command == NULL){
        fprintf(stderr, "Couldn't allocate memory for command\n");
        exit(0);
    }
    sprintf(command, "wc -l %s > nb_line.txt", path);
    system(command);
    FILE *p = fopen("nb_line.txt", "r");
    if(p == NULL){
        fprintf(stderr, "Couldn't open %s for reading\n", path);
        exit(0);
    }
    fscanf(p, "%d", &count);
    pclose(p);
    sprintf(command, "rm -f nb_line.txt");
    system(command);
    free(command);
    return count;
}

void recharger_base_indexation(char *path, baseDescripteur* bd){
    FILE *fp = fopen(path, "r");
    descripteur *d = calloc(1, sizeof(descripteur));
    ELEMENT *e = calloc(1, sizeof(ELEMENT));
    e->mot = calloc(TAILLE_TOKEN_MAX, sizeof(char));
    
    if( d == NULL || fp == NULL || e == NULL || e->mot == NULL){
        fprintf(stderr, "Error : recharcher base indexation : failed memory allocation \n");
        exit(0);
    }

    if(e->mot == NULL){
        fprintf(stderr, "Error : recharcher base indexation : failed memory allocation \n");
        exit(0);
    }
    int count = count_number_of_file_line(path);
    
    for(int j = 1; j < count; j++)
    {
        fscanf(fp, "%d",&(d->idDesc));
        fscanf(fp, "%d",&(d->tailleListe));
        fscanf(fp, "%d",&(d->nbToken));
        for(int i=0; i<d->tailleListe; i++)
        {
            fscanf(fp, "%s",e->mot);
            fscanf(fp, "%d[^\n]", &(e->nbOccurence));
            d->listeELMENT = emPILE(d->listeELMENT, e);
        }
        printf("%s\n", descripteur_toString(*d));
        if(d->nbToken != 0) *(bd) = empiler_baseDescripteur(*bd, *d);
        d->listeELMENT = NULL;
    }
    
   free(d);
   fclose(fp);
}

void recharger_liste_indexation(char *path, pathIdDesc* tb_liste){
    FILE *fp = fopen(path, "r");
    liste_descripteur* p = calloc(1, sizeof(struct listeDesc));
    int count = count_number_of_file_line(path);
    if(fp == NULL || p == NULL){
        fprintf(stderr, "Error : recharcher liste indexation : failed memory allocation \n");
        exit(0);
    }
    p->path = calloc(TAILLE_MALLOC, sizeof(char));
    if(p->path == NULL){
        fprintf(stderr, "Error : recharcher liste indexation : failed memory allocation \n");
        exit(0);
    }
    //fgets(token, sizeof(token), fp);
    for(int i = 1; i < count; i++){
        fscanf(fp, "%s[^\n]", p->path);
        fscanf(fp, "%d[^\n]", &(p->id));
        //printf("%s, %d\n", p->path, p->id);
        *tb_liste = empiler_listedescripteur(*tb_liste, p);
    }
    //printf("%d\n", (*tb_liste)->taille); 
    //affiche_listedescripteur(*tb_liste);
    free(p);
    fclose(fp);
}

void recharger_table_indexation(char *path, tableDescript* tb_desc){
    FILE *fp = fopen(path, "r");
    int count = count_number_of_file_line(path);
    tableDescript p = calloc(1, sizeof(struct tableDescripteur));
    if(fp == NULL || p == NULL){
        fprintf(stderr, "Error : recharcher table indexation : failed memory allocation \n");
        exit(0);
    }
    p->idDescripteur = calloc(1, sizeof(struct idDescOcc));
    if(p->idDescripteur == NULL){
        fprintf(stderr, "Error : recharcher table indexation : failed memory allocation \n");
        exit(0);
    }
    p->mot = calloc(TAILLE_MALLOC, sizeof(char));
    if(p->mot == NULL){
        fprintf(stderr, "Error : recharcher table indexation : failed memory allocation \n");
        exit(0);
    }
    int j = 0;
    for(int i = 0; i<count; i++){
        fscanf(fp, "%s[^\n]",p->mot);
        fscanf(fp, "%d[^\n]",&(p->idDescripteur->idDesc));
        fscanf(fp, "%d[^\n]",&(p->idDescripteur->occ));
        *tb_desc = empile_tableDescElement(*tb_desc, p->mot, p->idDescripteur->idDesc, p->idDescripteur->occ);
        j++;
    }
    //printf("%d\n", j);
    fclose(fp);
    free(p);
}

/// Mettre des commentaires
