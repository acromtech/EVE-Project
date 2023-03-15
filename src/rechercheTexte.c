
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

#include "cJSON.h"
#include "indexationTexte.h"

void saisie(char *mot)
{
    fgets(mot, TAILLE_MALLOC, stdin);
    if(mot[strlen(mot)-1] == '\n')
        mot[strlen(mot)-1] = '\0';
}       
int saisiePath(char *mot)
{
    FILE *fp;
    saisie(mot);
    fp = fopen(mot, "r");
    if (fp == NULL)
        return 0;
    
    fclose(fp);
    return 1;
}
void viderBuffer(){
    for(int c=0;c!='\n'&&c!=EOF;c=getchar());
}

PILE traitementSaisie(char saisie[100]){
    PILE p=NULL;
    char* pc=strtok(saisie," \n\t");
    while(pc!=NULL){
        p=emPILE(p,createELEMENT(pc,-1));
        pc=strtok(NULL," \n\t");
    }
    return p;
}
void insertionSort(idDescOccu tab, int size) 
{
    int i, j;
    struct idDescOcc tmp;

    for (i=0 ; i < size-1; i++)
    {
        for (j=0 ; j < size-i-1; j++)
        {
            if (tab[j].occ < tab[j+1].occ) 
            {
                tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }
        }
    }
}

idDescOccu rechercheTexteMot(tableDescript tb_desc, char *mot, int *count)
{      //PROGRAMME PRINCIPAL DE RECHERCHE PAR MOT CLE
    idDescOccu idOcc = NULL;
    idDescOccu tab;
    

    while(tb_desc != NULL)
    {
        if(strcmp(tb_desc->mot, mot) == 0)
            if(tb_desc->idDescripteur != NULL)
            {
                idOcc = empileIdDesc(idOcc, tb_desc->idDescripteur->idDesc, tb_desc->idDescripteur->occ);
                *count = *(count) + 1;
            }
                
        tb_desc = tb_desc->next;
    }
    if(*count != 0)
    {
        tab = calloc(*count, sizeof(struct idDescOcc));
        if(tab == NULL)
        {
            fprintf(stderr, "Error : rechercheMotCle : out of memory\n");
            exit(0);
        }
        for(int i = 0; idOcc != NULL; i++, idOcc = idOcc->next)
        {
            tab[i].idDesc = idOcc->idDesc;
            tab[i].occ = idOcc->occ;
        }
        insertionSort(tab, *count);

        free(idOcc);
        return tab;
    }
    free(idOcc);
    return NULL;
}

void rechercheTexteMotCle(pathIdDesc liste_desc, tableDescript tb_desc)
{
    setlocale(LC_ALL,"");
    idDescOccu resultat = NULL;
    int count = 0;
    liste_descripteur *tmp = liste_desc->tete;
    double temps=0.0;
    clock_t debut;
    clock_t fin;
    descripteurEtScoreListe liste_resultat = NULL;

    char *mot = calloc(TAILLE_MALLOC, sizeof(char));
    if(mot == NULL) 
    {
        fprintf(stderr, "Error : rechercheMotCleResultat : out of memory\n");
        exit(0);
    }
    printf("Veuillez saisir le mot qui servira à la comparaison : \n");
    saisie(mot);
    debut = clock();
    resultat = rechercheTexteMot(tb_desc, mot, &count);
    fin = clock();
    

    if(count != 0)
    {
        temps+=(double)(fin-debut)/CLOCKS_PER_SEC;
        printf("Résultat(s) en %f secondes\n\n",temps);
        printf("Le(s) fichier(s) dans lequel(lesquels) le mot \"%s\" est significatif est(sont): (Nom_du_fichier : nombre_d'occurence de mot)\n", mot);
        for(int i = 0; i < count; i++)
        {
            while(tmp != NULL)
            {
                if(tmp->id == resultat[i].idDesc)
                {
                    liste_resultat = empilerDescriipteurEtScore(liste_resultat, tmp->path,tmp->id, resultat[i].occ);
                    break;
                }   
                tmp = tmp->next;
            }
            tmp = liste_desc->tete;
        }
        //sleep(15);
    }
    else
    {
        printf("Aucun fichier ne contient \"%s\" comme mot significatif.\n", mot);
        sleep(4);
    }
    if(liste_resultat != NULL){
        strcat(mot, ".json");
        createJson(liste_resultat, mot);
    }
}

void rechercheTexteCompare(const volatile baseDescripteur b, pathIdDesc liste){     //PROGRAMME PRINCIPAL DE RECHERCHE PAR COMPARAISON DE DESCRIPTEUR
    setlocale(LC_ALL,"");
    descripteur *d = calloc(1,sizeof(descripteur));
    liste_descripteur *ld = calloc(1, sizeof(liste_descripteur));
    ld->path = calloc(TAILLE_MALLOC, sizeof(char));
    descripteurEtScoreListe liste_resultat = NULL;
    char *chemin = calloc(TAILLE_MALLOC, sizeof(char));
    char *jsonPath = calloc(TAILLE_MALLOC, sizeof(char));

    if(chemin == NULL || d == NULL || jsonPath == NULL || ld == NULL || ld->path == NULL )
    {
        fprintf(stderr,"Error : rechercheTexteCompare : out of memory\n");
        exit(0);
    }
    double temps=0.0;
    clock_t debut;
    clock_t fin;
    Score s = NULL, tmp = NULL;

    //system("clear");
    printf("Veuillez saisir le chemin du fichier à comparer\n");
    int ok = saisiePath(chemin);
    

    if(ok == 1)
    {
        int id=trouveIDDescripteur(chemin,liste->tete);
        if(id==-1){   perror("Descripteur inconnu");      exit(0);}
        if(descripteurExiste(id,b->tete,d) == 1){
            if(d->tailleListe == 0)
            {
                printf("\e[1;35mResultat\e[0;35m : A l'issu traitement du fichier %s aucun mot n'apparaît plus de %d fois. \nCe fichier ne contient donc aucun mot significatif il est donc impossible de le comparer à la base de fichier.\n Veuillez changer le sueil de mot significatif et rééssayer. Merci.\n\e[0m\n", chemin, SEUIL_MOT_SIGNIFICATIF);
                sleep(5);
                return;
            }
            else
            {
                debut=clock();
                s = calculeScoreBaseDescripteur(b->tete, d, s);
                if(s==NULL) printf("Aucun document ne correspond au fichier spécifié a part lui meme : Essayez avec d'autres fichiers.\n");
                else{
                    fin=clock();
                    temps+=(double)(fin-debut)/CLOCKS_PER_SEC;
                    //system("clear");
                    printf("Résultat(s) en %f secondes\n\n",temps);
                    s = s->next;
                    tmp = s;
                    while(tmp != NULL){
                        if((tmp->score) != 0){
                            jsonPath = trouverChemin(tmp->id, liste);
                            printf("%d %s\n", tmp->id, jsonPath);
                            liste_resultat = empilerDescriipteurEtScore(liste_resultat, jsonPath,tmp->id, (int)((tmp->score*100.0)/s->score));
                        }
                        tmp = tmp->next;
                    }
                    
                    if(liste_resultat != NULL){
                        cleanPath(jsonPath, chemin);
                        strcat(jsonPath, ".json");
                        printf("%s\n", jsonPath);
                        createJson(liste_resultat, jsonPath);
                    }
                    afficheNbScore(s, NB_LISTE,liste);
                    ouvreFichier(choixFichier(s),liste);
                }
                    //sleep(12);    
            }
            
        }
        else 
        {
            printf("\tIl semblerait que ce fichier n'a pas été indexer\n\tVeuillez vérifier le chemin saisie\n");
            sleep(4);
        }
        
    }
    else
    {
        printf("Le fichier \"%s\" n'existe pas\n", chemin);
        sleep(4);
    }
        
    libereScore(s);
    liberePILE(d->listeELMENT);
    free(d);
}

Score calculeScoreBaseDescripteur(const volatile descripteur* descBase,descripteur* descRequete,Score s){
    float score=0;

    while(descBase != NULL)
    {
        if(descBase->tailleListe == 0)
            score = 0;
        else
            score = ((calculeScoreDescripteur(descBase->listeELMENT,descRequete->listeELMENT))/descRequete->nbToken);
    
        if(score>=0)
        {
            s=empilerScore(s,score,descBase->idDesc);
            s=triScore(s);
        }    
        descBase = descBase->next;
    }
    
    
    return s;
}

float calculeScoreDescripteur(const volatile PILE descBase,PILE descRequete){
    float score=0;
    while(descRequete != NULL)
    {
        score+=calculeScoreUnitaire(descBase,*(ELEMENT*)descRequete->element);
        descRequete = descRequete->next;
    }
    
    return score;
}

float calculeScoreUnitaire(PILE descBase,ELEMENT elementDescRequete){
    float score=0;
    ELEMENT elmDesc;    
    affectELEMENT(&elmDesc, elementDescRequete);
    while(descBase != NULL)
    {
        ELEMENT elmBase;    affectELEMENT(&elmBase,*(ELEMENT*)descBase->element);
    
        if(strcoll(elmBase.mot,elmDesc.mot)==0)
        {
            if(elmDesc.nbOccurence==-1) score+=elmBase.nbOccurence;
            else if(elmBase.nbOccurence<elmDesc.nbOccurence) score+=(((float)elmBase.nbOccurence)/((float)elmDesc.nbOccurence))*100;
            else score+=(((float)elmDesc.nbOccurence)/((float)elmBase.nbOccurence))*100;
            return score;        
        }
        descBase = descBase->next;
    }
    
    return score;
}

void afficheNbScore(Score s,int nb,pathIdDesc liste){
    float ms=s->score;
    int i = 0;

    if(ms != 0)
    {
        while(s != NULL)
        {
            printf("(%d)\t%f%%\t%s\n",i+1,s->score/ms*100,trouveChemin(s->id,liste->tete));
            printf("\n\r");
                if(nb == (i+1))
                    break;
            i++;
            s = s->next;
        }
    }
    else 
    {
        while(s != NULL)
        {
            printf("(%d)%f\t%s\n",i+1,s->score,trouveChemin(s->id,liste->tete));
            printf("\n\r");
                if(nb == (i+1))
                    break;
            i++;
            s = s->next;
        }
    }
    
}

Score empilerScore(Score s,float score,int idDesc){
    Score tmp = calloc(1,sizeof(DescripteurScore));
    if(tmp == NULL)
    {   
        fprintf(stderr,"Error \n");
        exit(0);
    }
    tmp->id = idDesc;
    tmp->score = score;
    tmp->next = s;
    return tmp;
}

Score triScore(Score s){
    if(s->next!=NULL){
        if(s->score<s->next->score){
            int tmpR=s->next->id;
            float tmpS=s->next->score;
            s->next->id=s->id;
            s->next->score=s->score;
            s->id=tmpR;
            s->score=tmpS;
            s->next=triScore(s->next);
        }
    }
    return s;
}

void libereScore(Score p){
    if(p!=NULL){
        libereScore(p->next);
        free(p);
    }
}

void liberePILE(PILE p){
    if(p!=NULL){
        liberePILE(p->next);
        free(p);
    }
}

DescripteurScore choixFichier(Score s){
    char c;
    int index;

    do 
    {
        printf("Rentrez le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir\n");
        scanf("%c",&c);
        index = c - '0';
        if(index>NB_LISTE||index<0) 
            printf("Le chiffre entrer est invalide. Veuillez rentrez un chiffre compris entre 1 et %d\n",NB_LISTE);
    }while(index>NB_LISTE||index<0);

    viderBuffer();
    return recupScore(s,index,1);
}

DescripteurScore recupScore(Score s,int index,int i){
    DescripteurScore ds;
    if(i<index&&s->next!=NULL) ds=recupScore(s->next,index,i+1);
    else if(i<index&&s->next==NULL) printf("Cette valeur ne peut pas être lue\n");
    else{
        ds.score=s->score;
        ds.id=s->id;
    }
    return ds;
}

int descripteurExiste(int idDesc, descripteur* b,descripteur* d){
    int existe=0;
    while(b != NULL)
    {
        if(b->idDesc==idDesc)
        {
            d->listeELMENT = b->listeELMENT;
            d->tailleListe = b->tailleListe;
            d->idDesc = b->idDesc;
            d->nbToken = b->nbToken;
            existe = 1;
            break;
        }
        b = b->next;
    }
    return existe;
}

void ouvreFichier(DescripteurScore s,pathIdDesc liste){
    char* cmd=(char*)calloc(100,sizeof(char));
    sprintf(cmd,"gedit %s",trouveChemin(s.id,liste->tete));
    if(system(cmd)!=0) printf("Impossible de lancer la commande, %s\n",cmd);
    free(cmd);
}

char* trouveChemin(int idDesc,liste_descripteur* liste){
    char* chemin=NULL;
    if(idDesc==liste->id) return liste->path;
    if(liste->next!=NULL) chemin=trouveChemin(idDesc,liste->next);
    return chemin;
}

int trouveIDDescripteur(char* chemin,liste_descripteur* liste){
    int test=-1;
    if(strcmp(chemin,liste->path)==0) return liste->id;
    if(liste->next!=NULL) test=trouveIDDescripteur(chemin,liste->next);
    return test;
}

void rechercheMotCleMenu()
{
    tableDescript tbDesc = NULL;
    pathIdDesc liste = initListeDescripteur();

    rechargerTableDescripteur("../bin/fichiersIndexation/table_descripteur.csv",&tbDesc);
    rechargerListeDescripteur("../bin/fichiersIndexation/liste_descripteur.csv", &liste);

    rechercheTexteMotCle(liste, tbDesc);
}

void comparaisonTexteMenu()
{
    baseDescripteur bd = initBaseDescripteur();
    pathIdDesc liste = initListeDescripteur();

    rechargerBaseDescripteur("../bin/fichiersIndexation/base_descripteur.csv",&bd);
    rechargerListeDescripteur("../bin/fichiersIndexation/liste_descripteur.csv", &liste);
    
    rechercheTexteCompare(bd, liste);
}
// Partie JAVA

void createJson(descripteurEtScoreListe liste, char *jsonName){
    char *string;
    char *idToString = calloc(10, sizeof(char));
    int id_ = 1;
    FILE *json = fopen(jsonName, "w");

    cJSON *jsonFile = NULL;
    cJSON *descripteur = NULL;
    cJSON *id = NULL;
    cJSON *path = NULL;    
    
    jsonFile = cJSON_CreateObject();
    if(jsonFile == NULL){
        fprintf(stderr, "Error : createJson : impossible de creer le JSON");
        exit(0);
    }

    while(liste != NULL){
        
        descripteur = cJSON_CreateObject();
        if(descripteur == NULL){
            fprintf(stderr, "Error : createJson : impossible de creer le JSON");
            exit(0);
        }
        sprintf(idToString, "%d", liste->score);
        cJSON_AddItemToObject(jsonFile, idToString, descripteur);

        id = cJSON_CreateNumber(liste->descripteur->id);
        if(id == NULL){
            fprintf(stderr, "Error : createJson : impossible de creer le JSON");
            exit(0);
        }
        cJSON_AddItemToObject(descripteur, "id", id);

        path = cJSON_CreateString(liste->descripteur->path);
        if(path == NULL){
            fprintf(stderr, "Error : createJson : impossible de creer le JSON");
            exit(0);
        }
        cJSON_AddItemToObject(descripteur, "path", path);
        liste = liste->next;
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

    tmp->descripteur = calloc(1, sizeof(liste_descripteur));
    if(tmp->descripteur == NULL){
        fprintf(stderr, "Error : initListeDescripteurEtScore : impossible d'empiler : descripteur null");
        exit(0);
    }

    tmp->descripteur->path = calloc(TAILLE_TOKEN_MAX, sizeof(char));
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

char* trouverChemin(int id, pathIdDesc liste){
    char* chemin = NULL;
    liste_descripteur* tmp = liste->tete;

    while(tmp != NULL){
        if(id == tmp->id){
            chemin = tmp->path;
            break;
        }
        tmp = tmp->next;
    }
    printf("%s %s %d\n", chemin, tmp->path, tmp->id);
    return chemin;
}
    