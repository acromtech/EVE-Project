#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

#include "indexationTexte.h"
/**
 * @brief fonction permettant de receuillir les différentes entrée de chaine de caractères
 * 
 * @param mot paramètre d'entrée sortie permettant de stocker la chaine de caractère entrée par l'utilisateur 
 */
void saisie(char *mot)
{
    getchar();
    fgets(mot, TAILLE_MALLOC, stdin);
    if(mot[strlen(mot)-1] == '\n')
        mot[strlen(mot)-1] = '\0';
}       
/**
 * @brief fonction permettant de vérifier l'existance d'un fichier dont le chemin est fourni par l'utilisateur.
 * 
 * @param mot paramètre d'entrée sortie permettant de stocker la chaine de caractère entrée par l'utilisateur 
 * @return int valeur de retour 1 ou 0
 */
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
/**
 * @brief fonction permettant de "supprimer" le contenu d'un tableau de caractères
 * 
 */
void viderBuffer(){for(int c=0;c!='\n'&&c!=EOF;c=getchar());}

/**
 * @brief fonction permettant le traitement d'une chaine de caractère entrée par l'utilisateur
 * 
 * @param saisie paramètre d'entrée contenant la chaine de caractère à traiter.
 * @return PILE pile d'élément de type ELEMENT contenant les différents mots recceuillis après traitement avec des un nombre d'occurence à -1 
 */
PILE traitementSaisie(char saisie[100]){
    PILE p=NULL;
    char* pc=strtok(saisie," \n\t");
    while(pc!=NULL){
        p=emPILE(p,createELEMENT(pc,-1));
        pc=strtok(NULL," \n\t");
    }
    return p;
}
/**
 * @brief fonction permettant de trier un tableau d'éléments de type idDescOccu suivant un ordre décroissant basé sur l'attribut "occ" rendant compte sur le nombre d'occurence
 * 
 * @param tab adresse du tableau d'éléments de type idDescOccu à trier
 * @param size taille du tableau
 */
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

/**
 * @brief donction permettant de recceuillir un tableau d'élement de type idDescOccu correspondant à l'ensemble des id et nombre d'occurence du "mot" enntré par l'utilisateur dans le cadre de la recherche par mot clé
 * 
 * @param tb_desc structure contenant une pile d'élélement de type liste_descripteur* renseillant pour chaque mot significatif l'id du fichier dans lequel il est présent et et son nombre d'occurence dans ce fichier
 * @param mot variable permettant de stocker une suite de caractères représentant le "mot clé" de la recherche
 * @param count paramètre d'entrée sortie donnant le nombre de corespondance obtenu
 * @return idDescOccu tableau d'élément de type idDescOccu
 */
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

/**
 * @brief fonction générale de recherche par mot clé
 * 
 * @param liste_desc structure contenant le chemin vers de chaque fichier indexer suivi de son id
 * @param tb_desc structure contenant les mot significatif, l'id des fichiers dont ils proviennent et leurs nombre d'occurence dans ces différents fichiers
 */
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
        sleep(15);
    }
    else
    {
        printf("Aucun fichier ne contient \"%s\" comme mot significatif.\n", mot);
        sleep(4);
    }
        
}

/**
 * @brief fonction permettant la comparaison de fichiers
 * 
 * @param b structure contenant la base de descripteurs
 * @param liste structure contenant la structure contenant le chemin vers de chaque fichier indexer suivi de son id
 */
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
    Score s = NULL;

    //system("clear");
    printf("Veuillez saisir le chemin du fichier à comparer\n");
    int ok = saisiePath(chemin);
    int nbListe = config("nbListe");

    if(ok == 1)
    {
        int id=trouveIDDescripteur(chemin,liste->tete);
        if(id==-1){   perror("Descripteur inconnu");      exit(0);}
        if(descripteurExiste(id,b->tete,d) == 1){
            if(d->tailleListe == 0)
            {
                printf("\e[1;35mResultat\e[0;35m : A l'issu traitement du fichier %s aucun mot n'apparaît plus de %d fois. \nCe fichier ne contient donc aucun mot significatif il est donc impossible de le comparer à la base de fichier.\n Veuillez changer le sueil de mot significatif et rééssayer. Merci.\n\e[0m\n", chemin, config("seuilMotSignificatif"));
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
                    afficheNbScore(s, nbListe,liste);
                        if(s->next->score == 0)
                        {
                            sleep(5);
                            return;
                        }
                    ouvreFichier(choixFichier(s),liste);
                }
                    sleep(12);    
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
/**
 * @brief fonction de calcul du score de correspondance chaque descripteur de la base par rapport au descripteur du fichier servant de base de comparaison 
 * 
 * @param descBase descripteur de la base
 * @param descRequete descripteur du fichier servant de base de comparaison
 * @param s liste des de type Score ayant pour champs id et score
 * @return Score liste trié des scores après parcours de toute la base
 */
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

/**
 * @brief fonction de calcul du taux de ressemblance entre les éléments des deux liste de mots des deux différents descriptuers
 * 
 * @param descBase liste de mots du descripteur de la base
 * @param descRequete liste de mots du descripteur servant de base de comparaison
 * @return float resultat de calcul représentant le taux de similitude
 */
float calculeScoreDescripteur(const volatile PILE descBase,PILE descRequete){
    float score=0;
    while(descRequete != NULL)
    {
        score+=calculeScoreUnitaire(descBase,*(ELEMENT*)descRequete->element);
        descRequete = descRequete->next;
    }
    
    return score;
}
/**
 * @brief fonction permettant d'obtenir le taux de ressemblance pour chaque mot du descripteur servant de base de comparaison
 * 
 * @param descBase 
 * @param elementDescRequete 
 * @return float resultat correspondant au taux de ressemblance pour chaque mot du descripteur servant de base de comparaison
 */
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

/**
 * @brief fonction d'affichage du ressultat à l'issu de la comparaison
 * 
 * @param s liste de resultat
 * @param nb nombre de resultat à afficher au minimum
 * @param liste structure pathIdDesc
 */
void afficheNbScore(Score s,int nb,pathIdDesc liste){
    float ms=s->score;
    int i = 0;
    s = s->next;
    if(s == NULL || s->score == 0) 
    {
        printf("\e[1;35mResultat\e[0;35m : Aucun fichier ne correspond à ce fichiers\n Le taux de ressemblace le plus élévé est de 0.000%%.\n\e[0m\n");
        return;
    }
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
        printf("Rentrez le nombre entre parenthèses associé au fichier que vous souhaitez ouvrir\n");
        scanf("%c",&c);
        index = c - '0' +1;
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
    baseDescripteur bd = initBaseDescripteur();
    if(config("seuilmotsignificatif") <= 2)
    {
        suprimerBaseMenu();
        indexationBase("../BaseFichiersTexte/", &bd, &liste, &tbDesc);
    }
    else
    {
        rechargerTableDescripteur("../BaseFichiersTexte/FichiersDeDescription/table_descripteur.csv",&tbDesc);
        rechargerListeDescripteur("../BaseFichiersTexte/FichiersDeDescription/liste_descripteur.csv", &liste);
        indexationBase("../BaseFichiersTexte/", &bd, &liste, &tbDesc);
    }
    
    rechercheTexteMotCle(liste, tbDesc);
}

void comparaisonTexteMenu()
{
    tableDescript tbDesc = NULL;
    pathIdDesc liste = initListeDescripteur();
    baseDescripteur bd = initBaseDescripteur();
    
    if(config("seuilmotsignificatif") <= 2)
    {
        suprimerBaseMenu();
        indexationBase("../BaseFichiersTexte/", &bd, &liste, &tbDesc);
    }
    else 
    {
        rechargerBaseDescripteur("../BaseFichiersTexte/FichiersDeDescription/base_descripteur.csv",&bd);
        rechargerListeDescripteur("../BaseFichiersTexte/FichiersDeDescription/liste_descripteur.csv", &liste);
        indexationBase("../BaseFichiersTexte/", &bd, &liste, &tbDesc);
    }
    
    rechercheTexteCompare(bd, liste);
}
