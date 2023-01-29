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
        baseDescripteur bd = initBaseDescripteur();
        pathIdDesc listeDesc = initListeDescripteur();
        tableDescript tb_liste = NULL;
        int count = 0;
        if(SEUIL_MOT_SIGNIFICATIF <= 2)
            suprimerBaseMenu();
        
        rechargerBaseDescripteur("../bin/fichiersIndexation/base_descripteur.csv", &bd);
        //affiche_baseDescripteur(bd);
        rechargerListeDescripteur("../bin/fichiersIndexation/liste_descripteur.csv", &listeDesc);
        //affiche_listedescripteur(listeDesc);
        rechargerTableDescripteur("../bin/fichiersIndexation/table_descripteur.csv", &tb_liste);
        indexationBase(argv[1], &bd, &listeDesc, &tb_liste);
        tableDescript tmp = tb_liste;
        while(tmp != NULL){
            count++;
            tmp = tmp->next;
        }
        printf("END : %d %d %d\n", bd->taille, listeDesc->taille, count);

        
        //RECHERCHE PAR COMPARAISON DE DESCRIPTEUR
        printf("| RECHERCHE PAR COMPARAISON |\n");
        rechercheTexteCompare(bd,listeDesc);
        //RECHERCHE PAR MOT CLE (PAS ENCORE TOTALEMENT AU POINT)
        printf("| RECHERCHE PAR MOT CLE |\n");
        rechercheTexteMotCle(listeDesc,tb_liste);
    return 0;
}
