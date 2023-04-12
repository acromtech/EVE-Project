#include "recherche_Audio.h"

int main (){

	struct resultatAudio res = saisieRechercheAudio("jingle_fi.wav");
	printf("%s %d", res.path, res.score);
    
}

