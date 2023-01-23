#include "indexationImage.h"
#include <strings.h>

int main(int argc, char *argv[]){
    baseDescripteurImage bd = initBaseDescripteurImage();
    listeDescripteurImage liste = initListeDescripteurImage();
    
    recharger_base_indexation("base_descripteur_image.csv", &bd);
    printf("%d\n", bd->taillle);
    //indexationImage("TXT/01.txt", &bd, &liste, bd->taillle, NB_BITS);
    //indexerBaseImage(argv[1], &bd, &liste);

    return 0;   
}