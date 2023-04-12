#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "configuration.h"

int main(){
 
    editConfig(3,1024);
    int parametre = config("indexationAudioN");

    editConfig(4,100);
    int parametre1 = config("indexationAudioM");

    printf("la valeur est: %d\n", parametre);
    printf("la valeur est: %d\n", parametre1);

    saisieConfig();
}
