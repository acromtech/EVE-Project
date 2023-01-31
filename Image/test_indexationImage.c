#include "indexationImage.h"


int main(int argc, char *argv[])
{
    system("echo > base_descripteur_image.csv");
    system("echo > liste_descripteur_image.csv");

    baseDescripteurImage bd = initBaseDescripteurImage();
    listeDescripteurImage liste = initListeDescripteurImage();

    indexerBaseImage(&bd, &liste);
    printf("L'indexation a été réalisée avec succès :\n\t- nombre de descripteur : %d\n\t- nombre fichiers indexer : %d\n", bd->taillle, liste->taille);
    
    return 0;
}