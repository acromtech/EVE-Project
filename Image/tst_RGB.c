#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "indexationImage.h"

void afficheBase(baseDescripteurImage pileImage){
    descripteurImage tmp;
    tmp=pileImage->tete;
    for(int i=0;i<pileImage->taillle;i++,tmp=tmp->next){
        printf("%d %c",tmp->id,tmp->type);
        for(int j=0;j<64;j++) printf(" %d",tmp->histogramme[j]);
        printf("\n");
    }
}

int main(){
    system("echo > base_descripteur_image.csv");
    system("echo > liste_descripteur_image.csv");
    baseDescripteurImage bd = initBaseDescripteurImage();
    listeDescripteurImage liste = initListeDescripteurImage();
    indexerBaseImage(&bd,&liste);
    rechercheCouleur(bd,liste);
    //rechercheHisto(bd,liste);
    return 0;
}