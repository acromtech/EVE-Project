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
    baseDescripteur bd = initBaseDescripteur();
    pathIdDesc listeDesc = initListeDescripteur();
    tableDescript tb_liste = NULL;
    int count = 0;

    rechargerBaseDescripteur("../bin/fichiersIndexation/base_descripteur.csv", &bd);
    //affiche_baseDescripteur(bd);

    rechargerListeDescripteur("../bin/fichiersIndexation/liste_descripteur.csv", &listeDesc);
    //affiche_listedescripteur(listeDesc);
    
    rechargerTableDescripteur("../bin/fichiersIndexation/table_descripteur.csv", &tb_liste);
    
    //printf("Im also out of here %d\n", bd->taille);
    indexationBase(argv[1], &bd, &listeDesc, &tb_liste);
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