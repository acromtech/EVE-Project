#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "indexationTexte.h"

void saisie(char *mot)
{
    getchar();
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
void viderBuffer(){for(int c=0;c!='\n'&&c!=EOF;c=getchar());}

PILE traitementSaisie(char saisie[100]){
    PILE p=NULL;
    char* pc=strtok(saisie," \n\t");
    while(pc!=NULL){
        p=emPILE(p,create_EMENT(pc,-1));
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
            if (tab[j].occ > tab[j+1].occ) 
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
                idOcc = empile_idDesc(idOcc, tb_desc->idDescripteur->idDesc, tb_desc->idDescripteur->occ);
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
                    printf("\t%s : %d\n",tmp->path, resultat[i].occ);
                    break;
                }   
                tmp = tmp->next;
            }
            tmp = liste_desc->tete;
        }
    }
    else
        printf("Aucun fichier ne contient \"%s\" comme mot significatif.\n", mot);
}

void rechercheTexteCompare(const volatile baseDescripteur b, pathIdDesc liste){     //PROGRAMME PRINCIPAL DE RECHERCHE PAR COMPARAISON DE DESCRIPTEUR
    setlocale(LC_ALL,"");
    descripteur *d = calloc(1,sizeof(descripteur));
    char *chemin = calloc(TAILLE_MALLOC, sizeof(char));
    if(chemin == NULL || d == NULL)
    {
        fprintf(stderr,"Error : rechercheTexteCompare : out of memory\n");
        exit(0);
    }
    double temps=0.0;
    clock_t debut;
    clock_t fin;
    Score s=NULL;
    
    //system("clear");
    printf("Veuillez saisir le chemin du fichier à comparer\n");
    int ok = saisiePath(chemin);
    int nbListe = config("nbListe");

    if(ok == 1)
    {
        int id=trouveIDDescripteur(chemin,liste->tete);
        if(id==-1){   perror("Descripteur inconnu");      exit(0);}
        if(descripteurExiste(id,b->tete,d) == 1){
            debut=clock();
            s=calculeScoreBaseDescripteur(b->tete,*d,s);
            if(s==NULL) printf("Aucun document ne correspond au fichier spécifié a part lui meme : Essayez avec d'autres fichiers.\n");
            else{
                fin=clock();
                temps+=(double)(fin-debut)/CLOCKS_PER_SEC;
                //system("clear");
                printf("Résultat(s) en %f secondes\n\n",temps);
                afficheNbScore(s, nbListe,liste);
                ouvreFichier(choixFichier(s),liste);
            }
        }
        else printf("\tIl semblerait que ce descripteur n'existe pas\n\tVeuillez vérifier le chemin saisie\n");
    }
    else
        printf("Le fichier \"%s\" n'existe pas\n", chemin);
    libereScore(s);
    liberePILE(d->listeELMENT);
    free(d);
}

Score calculeScoreBaseDescripteur(const volatile descripteur* descBase,descripteur descRequete,Score s){
    float score=0;
    while(descBase != NULL)
    {
        if(descRequete.listeELMENT != NULL && descBase->listeELMENT != NULL)
            score=((calculeScoreDescripteur(descBase->listeELMENT,descRequete.listeELMENT))/descRequete.tailleListe);
        if(score>0)
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
    ELEMENT elmDesc;    affect_ELEMENT(&elmDesc, elementDescRequete);
    while(descBase != NULL)
    {
        ELEMENT elmBase;    affect_ELEMENT(&elmBase,*(ELEMENT*)descBase->element);
    
        if(strcoll(elmBase.mot,elmDesc.mot)==0)
        {
            if(elmDesc.nbOccurence==(-1)) score+=elmBase.nbOccurence;
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
    if(ms!=0) for(int i=0;i<nb&&s!=NULL;printf("(%d)\t%f%%\t%s\n",i+1,s->score/ms*100,trouveChemin(s->id,liste->tete)),i++,s=s->next);
    printf("\n\r");
}

Score empilerScore(Score s,float score,int idDesc){
    Score tmp=(Score)calloc(1,sizeof(DescripteurScore));
	tmp->id=idDesc;
    tmp->score=score;
	tmp->next=s;
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
        if(index>NBLISTE||index<0) 
            printf("Le chiffre entrer est invalide. Veuillez rentrez un chiffre compris entre 1 et %d\n",NBLISTE);
    }while(index>NBLISTE||index<0);

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

int descripteurExiste(int idDesc,const volatile descripteur* b,descripteur* d){
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
    sprintf(cmd,"xdg-open %s",trouveChemin(s.id,liste->tete));
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
    pathIdDesc liste = init_listeDescripteur();

    recharger_table_indexation("../BaseFichiersTexte/FichiersDeDescription/table_descripteur.csv",&tbDesc);
    recharger_liste_indexation("../BaseFichiersTexte/FichiersDeDescription/liste_descripteur.csv", &liste);

    rechercheTexteMotCle(liste, tbDesc);
}

void comparaisonTexteMenu()
{
    baseDescripteur bd = init_baseDescripteur();
    pathIdDesc liste = init_listeDescripteur();

    recharger_base_indexation("../BaseFichiersTexte/FichiersDeDescription/base_descripteur.csv",&bd);
    recharger_liste_indexation("../BaseFichiersTexte/FichiersDeDescription/liste_descripteur.csv", &liste);

    printf("END : %d %d", bd->taille, liste->taille);
    rechercheTexteCompare(bd, liste);
}