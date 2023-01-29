#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "indexationTexte.h"
#include "indexationTexte.c"

int main(int argc, char *argv[]){
    //  while(1){
        /*
        puts("--------------------------");
        puts("Test unitaire de la saisie");
        puts("--------------------------");
        char* mots=saisie();
        printf("%s",mots);
        puts("");

        puts("----------------------------------");
        puts("Test unitaire de traitementSaisie");
        puts("----------------------------------");
        descripteur d1;
        d1.listeELMENT=NULL;
        d1.listeELMENT=traitementSaisie(mots);
        if(d1.listeELMENT!=NULL)puts("\tOK\n");
        else puts("\tNOK\n");
        liberePILE(d1.listeELMENT);

        descripteur d2;
        d2.listeELMENT=NULL;
        d2.listeELMENT=traitementSaisie("bla");
        if(d2.listeELMENT!=NULL)puts("\tOK\n");
        else puts("\tNOK\n");
        liberePILE(d2.listeELMENT);

        descripteur d3;
        d3.listeELMENT=NULL;
        d3.listeELMENT=traitementSaisie("un éléphAnt d'AfriQue qui mange de l'HerBe");
        if(d3.listeELMENT!=NULL)puts("\tOK\n");
        else puts("\tNOK\n");
        liberePILE(d3.listeELMENT);
        
        if(traitementSaisie("2994 jhz BUBHD 7222")!=NULL)puts("\tOK\n");
        else puts("\tNOK\n");

        puts("----------------------------------");
        puts("Test unitaire de trouve_descripteur");
        puts("----------------------------------");
        if(trouve_descripteur(b->listeELMENT,d.listeELMENT!=NULL))puts("\tOK\n");
        else puts("\tNOK\n");

        puts("----------------------------------");
        puts("Test unitaire de trouve_baseDescripteur");
        puts("----------------------------------");
        Score s=NULL;
        trouve_baseDescripteur(b,d,s);

        puts("----------------------------------");
        puts("Test unitaire des fonctions de libération de mémoire");
        puts("----------------------------------");
        free(mots);
        liberePILE(d.listeELMENT);
        libereScore(s);
        */
        
        //INDEXATION AUTOMATIQUE
        baseDescripteur bd = init_baseDescripteur();
        pathIdDesc listeDesc = init_listeDescripteur();
        tableDescript tb_liste = NULL;
        int count = 0;
        recharger_base_indexation("../bin/fichiersIndexation/base_descripteur.csv", &bd);
        recharger_liste_indexation("../bin/fichiersIndexation/liste_descripteur.csv", &listeDesc);
        recharger_table_indexation("../bin/fichiersIndexation/table_descripteur.csv", &tb_liste);
        indexation_base(argv[1], &bd, &listeDesc, &tb_liste);
        tableDescript tmp = tb_liste;
        while(tmp != NULL){
            count++;
            tmp = tmp->next;
        }
        printf("END : %d %d %d\n", bd->taille, listeDesc->taille, count);

        //RECHERCHE PAR COMPARAISON DE DESCRIPTEUR
        rechercheTexteCompare(bd,listeDesc);
        //RECHERCHE PAR MOT CLE (PAS ENCORE TOTALEMENT AU POINT)
        rechercheTexteMotCle(listeDesc,tb_liste);
    //}
    return 0;
}
