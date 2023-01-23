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
    baseDescripteurImage bd = initBaseDescripteurImage();
    listeDescripteurImage liste = initListeDescripteurImage();
    //recharger_base_indexation("base_descripteur_image.csv", &bd);
    //indexationImage("TXT/01.txt", &bd, &liste, bd->taillle, NB_BITS);
    indexerBaseImage(&bd,&liste);
    //rechercheCouleur(bd,liste);
    rechercheHisto(bd,liste);
	
    return 0;
}