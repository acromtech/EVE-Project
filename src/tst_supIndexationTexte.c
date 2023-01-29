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

    suprimerBaseMenu();
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