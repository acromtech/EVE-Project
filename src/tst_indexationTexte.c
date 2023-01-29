#include "indexationTexte.h"
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    // Vérifier si un fichier a été spécifié en tant que paramètre
    /*if (argc < 2)
    {
        printf("Veuillez spécifier un fichier en tant que paramètre.\n");
        return 1;
    }*/
    baseDescripteur bd = init_baseDescripteur();
    pathIdDesc listeDesc = init_listeDescripteur();
    tableDescript tb_liste = NULL;
    int count = 0;

    recharger_base_indexation("../bin/fichiersIndexation/base_descripteur.csv", &bd);
    //affiche_baseDescripteur(bd);

    recharger_liste_indexation("../bin/fichiersIndexation/liste_descripteur.csv", &listeDesc);
    //affiche_listedescripteur(listeDesc);
    
    recharger_table_indexation("../bin/fichiersIndexation/table_descripteur.csv", &tb_liste);
    
    //printf("Im also out of here %d\n", bd->taille);
    indexation_base(argv[1], &bd, &listeDesc, &tb_liste);
    //tableDescript tmp = tb_liste;
    //while(tmp != NULL)
    {
      //  count++;
        //tmp = tmp->next;
    }
    //printf("END : %d %d %d\n", bd->taille, listeDesc->taille, count);
    //affiche_baseDescripteur(bd);

    return 0;
}
/*
    cpy = fopen("cpy.txt", "r");
    if(cpy == NULL)
    {
        fprintf(stderr, "cpy.txt not found");
        exit(0);
    }

    while(fgets(outputPath, 1024, cpy) != NULL)
    {
        printf("%s\n",outputPath);
        mot = strtok(outputPath, " ");
        
        while(mot != NULL)
        {
            printf("%s\n",mot);
            
            mot = strtok(NULL, " ");
        }
    }
    fclose(cpy);
    
    descripteur *d = calloc(1, sizeof(descripteur));
    ELEMENT *e = calloc(1, sizeof(ELEMENT));
    e->mot = calloc(4, sizeof(char));
    e->nbOccurence = 3;
    strcpy(e->mot, "hehe");
    
    d->listeELMENT = emPILE(d->listeELMENT, e);
    d->listeELMENT = emPILE(d->listeELMENT, e);
    printf("%s\n", descripteur_toString(d));
    */
/*
    FILE *input = fopen(argv[1], "r"); // Ouvrir le fichier en lecture
    char *stopwords[] = {"n'", "s'", "m'","est", "une", "avec", "qui","à","ainsi","autre","aux", "au","avec", "d'","ce","ceci","cela","celle","celles","celui","ceux","chaque","ci","comme","comment","dans","de","des","du","elle","en","et","eu","eux","il","je","la","le","les","leur","lui","ma","mais","me","même","mes","moi","mon","ne","nos","notre","nous","on","ou","par","pas","pour","qu'","que","qui","sa","se","ses","son","sur","ta","te","tes","toi","ton","tu","un","une","vos","votre","vous","l'", "a", "an", "and", "are", "as", "at", "be", "by", "for", "from", "has", "he", "in", "is", "it", "its", "of", "on", "that", "the", "to", "was", "were", "will", "with"}; // Créer un tableau de stopwords
    int stopwordsBufferSize = buffer_size(stopwords);
    char token[TAILLE_TOKEN_MAX];
    char *mot = NULL; // Créer un tableau qui contiendra un liste de mots
    char *command = calloc(1024, sizeof(char)); // Créer un tableau qui contiendra une commande pour les appels system
    char *outputPath = calloc(strlen(argv[1]), sizeof(char));
    clean_path(outputPath, argv[1]);
    FILE *output_TOK, *baseDescriptr, *listeDescripteur, *cpy, *tb;
    int is_stopword = 0, nbMotFichierTok = 0, id = 1;

    baseDescripteur bd = init_baseDescripteur();
    pathIdDesc listeDesc = NULL;
    tableDescript tb_liste = NULL;
    
    printf("debut des deux traitements. \n");
    
    nettoyageToken(input, argv[1], outputPath);
    fclose(input);

    strcat(outputPath, ".clean");
    input = fopen(outputPath, "r");
    if(input == NULL)
    {
        fprintf(stderr,"shit \n");
        exit(0);
    }
    clean_path(outputPath, argv[1]);
    
    output_TOK = filtrageToken(input, outputPath);
    clean_path(outputPath, argv[1]);
    
    fclose(input);
    fclose(output_TOK);

    strcat(outputPath, ".tok");
    baseDescriptr = fopen("base_descripteur.csv", "w");

    listeDescripteur = fopen("liste_descripteur.csv", "w");

    tb = fopen("table_descripteur.csv", "w");
    if(baseDescriptr == NULL  || listeDescripteur == NULL || tb == NULL)
    {
        fprintf(stderr,"shit \n");
        exit(0);
    }
    saveDescripteur(outputPath, baseDescriptr, &bd, &id, tb, &tb_liste);
    
    clean_path(outputPath, argv[1]);
    strcat(outputPath, ".xml");
    lienDescripteur(listeDescripteur, id, outputPath, &listeDesc);
    printf("fin des deux traitements\n");
    
    //fclose(baseDescriptr);*/