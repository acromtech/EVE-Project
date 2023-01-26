#include "indexationImage.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../IndexationRechercheTexte/indexationTexte.h"

baseDescripteurImage initBaseDescripteurImage()
{
    baseDescripteurImage bd = calloc(1, sizeof(struct basedescripteur));
    if(bd == NULL)
    {
        fprintf(stderr, "Error : initBaseDescripteurImage : out of memory\n");
        exit(0);
    }
    return bd;
}
void empilerBaseDescripteurImage(baseDescripteurImage* bd, struct descripteur_image d)
{   
    struct descripteur_image *tmp = calloc(1, sizeof(struct descripteur_image));
    tmp->histogramme = calloc(d.taille, sizeof(int));

    if(tmp == NULL || tmp->histogramme == NULL)
    {
        fprintf(stderr, "Error : empilerBaseDescripteurImage : out of memory\n");
        exit(0);
    }
    tmp->taille = d.taille;
    for(int i = 0; i <d.taille; i++)
        tmp->histogramme[i] = d.histogramme[i];
    
    tmp->id = d.id;
    tmp->type = d.type;
    tmp->next = (*bd)->tete;
    (*bd)->tete = tmp;
    (*bd)->taillle++;
}

void depilerBaseDescripteurImage(baseDescripteurImage* bd , struct descripteur_image* d)
{
    struct descripteur_image *tmp = (*bd)->tete;
    (*bd)->tete = (*bd)->tete->next;
    (*bd)->taillle--;
    d = tmp;
}

char* descripteurImageToString(struct descripteur_image d)
{
    char *buffer = calloc(1024, sizeof(char));
    int tmp;
    char tmpBuff[20];
    if(buffer == NULL)
    {
        fprintf(stderr, "Error : descripteurImageToString : out of memory\n");
        exit(0);
    }
    sprintf(buffer,"%d %c", d.id, d.type);
    for(int i=0; i<d.taille; i++)
    {
        tmp = d.histogramme[i];
        sprintf(tmpBuff," %d", tmp);
        strcat(buffer, tmpBuff);
    }
    return buffer;  
}

listeDescripteurImage initListeDescripteurImage()
{
    listeDescripteurImage list = calloc(1, sizeof(struct listedescripteurimage));
    
    if(list == NULL)
    {
        fprintf(stderr, "Error : initListeDescripteurImage : out of memory\n");
        exit(0);
    }

    return list;
}

void empilerListeDescripteurImage(listeDescripteurImage* liste, struct elementlistedescripteurimage el)
{
    struct elementlistedescripteurimage *tmp = calloc(1, sizeof(struct elementlistedescripteurimage));
    tmp->path = calloc(1024, sizeof(char));
    if(tmp == NULL || tmp->path == NULL)
    {
        fprintf(stderr, "Error : empilerListeDescripterImage : out of memory\n");
        exit(0);
    }
    tmp->id = el.id;
    strcpy(tmp->path, el.path);
    tmp->next = (*liste)->tete;
    (*liste)->tete = tmp;
    (*liste)->taille++;
}

int** allocationMatrice(int hauteur, int longueur)
{
    int** tab = calloc(hauteur, sizeof(int*));
    if(tab != NULL)
        for(int i = 0; i < hauteur; i++)
        {
            tab[i] = calloc(longueur, sizeof(int));
            if(tab[i] == NULL)
            {
                fprintf(stderr, "Error : allocationMatrice : out of memory\n");
                exit(0);
            }
        }
    if(tab == NULL)
    {
        fprintf(stderr, "Error : allocationMatrice : out of memory\n");
        exit(0);
    }
    return tab;
}

int* quantification(char *path, int nbBits, int *nbComposante)
{
    FILE *image = fopen(path, "r");
    if(image == NULL)
    {
        fprintf(stderr, "Error : quantification : impossible d'ouvrir le fichier %s.\n", path);
        exit(0);
    }
    int pix;
    int li,co;
    
	char couleur;
    int *histogramme = calloc(64, sizeof(int));
    int nombre_lu;
    
    fscanf(image,"%d",&li);
    fscanf(image,"%d",&co);
    fscanf(image,"%d",nbComposante);
	
	unsigned int R[li][co],G[li][co],B[li][co],binary_pix[li][co];
	for(int c=0;c<(*nbComposante);c++){
		for(int i=0;i<li;i++){
			for(int j=0;j<co;j++){
				fscanf(image,"%d",&pix);
				if(c==0)		R[i][j]=((pix&0xC0)>>2);
				else if(c==1)	G[i][j]=((pix&0xC0)>>4);
				else if(c==2)	B[i][j]=((pix&0xC0)>>6);
			}
		}
	}
	for(int i=0;i<li;i++) for(int j=0;j<co;j++) binary_pix[i][j]=R[i][j]|G[i][j]|B[i][j];
	for(int i=0;i<li;i++){
		for(int j=0;j<co;j++){
			nombre_lu=binary_pix[i][j];
			histogramme[nombre_lu]+=1;
		}
	}

    float somme=0;
	for(int i=0;i<64;i++)somme+=histogramme[i];
	for(int i=0;i<64;i++)histogramme[i]=(histogramme[i]/somme)*100;

    return histogramme;
}

void saveDescripteurImage(baseDescripteurImage* bd,FILE* baseDescripteur, struct descripteur_image d)
{
    empilerBaseDescripteurImage(bd, d);
    fprintf(baseDescripteur, "%s\n", descripteurImageToString(d));
}
void savelisteDescripteurImage(listeDescripteurImage* liste, FILE* listeDescripteur, char* path, int id)
{
    struct elementlistedescripteurimage* tmp = calloc(1, sizeof(struct elementlistedescripteurimage));
    tmp->path = calloc(1024, sizeof(char));
    if(tmp == NULL || tmp->path == NULL)
    {
        fprintf(stderr, "Error: savelisteDescripteurImage : out of memory\n");
        exit(0);
    }
    tmp->id = id;
    strcpy(tmp->path, path);
    empilerListeDescripteurImage(liste, *tmp);

    fprintf(listeDescripteur, "%s %d\n", path, id);
    free(tmp);
}

int isIndexerI(char* path)
{
    FILE *f = fopen("liste_descripteur_image.csv", "r");
    char *command = calloc(1024, sizeof(char));
    int indexer = 0;

    if(f == NULL || command == NULL)
    {
        fprintf(stderr, "isIndexer : out of memory\n");
        exit(0);
    }
    while(fscanf(f, "%s[^\n]", command) != EOF)
    {
        if(strcmp(path, command) == 0)
        {
            indexer = 1;
            break;
        }
    }
    fclose(f);
    return indexer;
}

void indexationImage(char* path, baseDescripteurImage* bd, listeDescripteurImage* liste, int id, int nbBits)
{
    FILE *baseDescripteur = fopen("base_descripteur_image.csv", "a");
    FILE *listeDescripteur = fopen("liste_descripteur_image.csv", "a");
    int nbComposantes;
    int histogramSize =1; 
    struct descripteur_image d;

        d.histogramme  = quantification(path, NB_BITS,&nbComposantes);
    
        if(nbComposantes != 1)
            d.type = 'C';
        else
            d.type = 'N';
        d.taille = 64;
        d.id = id;
        for(int i=0; i<d.taille; i++)
            printf("%d ", d.histogramme[i]);
        saveDescripteurImage(bd, baseDescripteur, d);
    savelisteDescripteurImage(liste, listeDescripteur, path, id);

    fclose(baseDescripteur);
    fclose(listeDescripteur);
}

void indexerBaseImage(baseDescripteurImage *bd, listeDescripteurImage *listeDescripteur)
{
    FILE *f;
    char *command = calloc(1024, sizeof(char)), *tmp = calloc(1024, sizeof(char));
    int isIndexer_;
    if(command == NULL || tmp == NULL)
    {
        fprintf(stderr, "Error : indexerBaseImage : out of memory\n");
        exit(0);
    }
    sprintf(command, "ls ../IndexationImage/TXT > files.txt");
    system(command);

    f = fopen("files.txt", "r");

    while(fscanf(f, "%s[^\n]", command) != EOF)
    {
        //printf("%s\n", command);
        sprintf(tmp, "../IndexationImage/TXT/%s", command);
        //printf("%s\n", tmp);
        indexationImage(tmp, bd, listeDescripteur, (*bd)->taillle, NB_BITS);     
    }
}

void recharger_base_indexationImage(char *path, baseDescripteurImage* bd)
{
    FILE *fp = fopen(path, "r");
    struct descripteur_image d;
    d.taille = 64;
    int nok = 0;

    if(fp == NULL )
    {
        fprintf(stderr, "Error : recharcher base indexation : impossible d'ouvir %s \n", path);
        exit(0);
    }
    int count = count_number_of_file_line(path);
    
    for(int j = 1; j < count; j++)
    {
        fscanf(fp, "%d",&(d.id));
        fscanf(fp, "%c",&(d.type));
        fscanf(fp, "%d",&(d.histogramme[0]));
        for(int i = 0; i < d.taille; i++)
            fscanf(fp, "%d", &(d.histogramme[i]));
        for(int i = 0; i < d.taille; i++)
            if(d.histogramme[i]> 63 || d.histogramme[i]<0)
            {
                nok = 1;
                break;
            }
        if(nok == 0)
        {
            empilerBaseDescripteurImage(bd, d);
            printf("%s\n", descripteurImageToString(d));
        }
        nok = 0;
    }
   
   fclose(fp);
}

void recharger_liste_indexationImage(char *path, listeDescripteurImage* tb_liste){
    FILE *fp = fopen(path, "r");
    struct elementlistedescripteurimage *p = calloc(1, sizeof(struct elementlistedescripteurimage));
    p->path = calloc(1024, sizeof(char));
    
    if(fp == NULL || p == NULL || p->path == NULL)
    {
        fprintf(stderr, "Error : recharcher liste indexation : failed memory allocation \n");
        exit(0);
    }

    int count = count_number_of_file_line(path);
    for(int i = 1; i < count; i++)
    {
        fscanf(fp, "%s", p->path);
        fscanf(fp, "%d", &(p->id));
        printf("%s, %d\n", p->path, p->id);
        empilerListeDescripteurImage(tb_liste, *p);
    }
    printf("%d\n", (*tb_liste)->taille); 
    //affiche_listedescripteur(*tb_liste);
    free(p);
    fclose(fp);
}

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
        afficheNbScoreImage(pileScore,NBLISTE,nbScore);
        ouvreFichierImage(choixFichierImage(pileScore,nbScore),liste);
    }
    else printf("Aucune image ne correspond a la couleur spécifiée : Essayez d'autres couleurs\n");
}

void supprimerBaseImage()
{
    system("echo > ../IndexationImage/liste_descripteur_image.csv");
    system("echo > ../IndexationImage/base_descripteur_image.csv");

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
    int id=trouveIDDescripteurImage(requete,liste);
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
            afficheNbScoreImage(pileScore,NBLISTE,nbScore);
            ouvreFichierImage(choixFichierImage(pileScore,nbScore),liste);
        }
        else printf("Aucun document ne correspond au descripteur spécifié : Essayez d'autres descripteurs\n");
    }
}

ScoreImage choixFichierImage(Src pileScore,int tailleTabScore){
    int index;
    ScoreImage scoreImage;
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
    Src pileScore=(Src)calloc(100,sizeof(ScoreImage));
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
    Src pileScore=(Src)calloc(100,sizeof(ScoreImage));
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

void afficheNbScoreImage(Src pileScore,int nbMaxResultat,int tailleTabScore){
    for(int i=0;i<nbMaxResultat&&i<tailleTabScore;i++)printf("(%d)\t%d\t%f%%\n",i+1,pileScore[i].id,pileScore[i].score);
    printf("\n\r");
}

void ouvreFichierImage(ScoreImage s,listeDescripteurImage liste){
    char* cmd=(char*)calloc(100,sizeof(char));
    char* cheminTXT=trouveCheminImage(s.id,liste);
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

char* trouveCheminImage(int idDesc,listeDescripteurImage liste){
    elementlitsetDescripteurImage tmp;
    tmp=liste->tete;
    while(tmp->next!=NULL){
        if(idDesc==tmp->id)
            return tmp->path;
    }
    return NULL;
}

int trouveIDDescripteurImage(char* chemin,listeDescripteurImage liste){
    elementlitsetDescripteurImage tmp;
    tmp=liste->tete;
    for(int i=0;i<liste->taille;i++,tmp=tmp->next)
        if(strcoll(chemin,tmp->path)==0) return tmp->id;
    return -1;
}
