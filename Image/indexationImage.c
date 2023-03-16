#include "indexationImage.h"
#include <stdio.h>
#include <stdlib.h>

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

int isIndexer(char* path)
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

    if(isIndexer(path) == 0)
    {
        printf("Indexation de %s :\n",path);
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
        printf("\nFin de l'indexation de %s.\n",path);
    }
    else
        printf("Fichier déjà indexer.\n");
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
    sprintf(command, "ls TXT > files.txt");
    system(command);

    f = fopen("files.txt", "r");

    while(fscanf(f, "%s[^\n]", command) != EOF)
    {
        //printf("%s\n", command);
        sprintf(tmp, "TXT/%s", command);
        //printf("%s\n", tmp);
        indexationImage(tmp, bd, listeDescripteur, (*bd)->taillle, NB_BITS);     
    }
}

int count_number_of_file_line(char *path){
    int count = 0;
    char *command = calloc(1024, sizeof(char));
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


void recharger_base_indexation(char *path, baseDescripteurImage* bd)
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

void recharger_liste_indexation(char *path, listeDescripteurImage* tb_liste){
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

void cleanPath(char *new_path, char *path){
    int i, len = strlen(path);
    strncpy(new_path, path, len);
    for(i = len-1; i >= 0; i--)
        if(new_path[i] == '.'){
            new_path[i] = '\0';
            break;
        }
}