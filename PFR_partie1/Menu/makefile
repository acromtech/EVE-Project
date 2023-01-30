mae : menu_mae.c menu_mae.h main.c ../Configuration/configuration.c ../Configuration/configuration.h ../RechercheAudio/recherche_Audio.c ../RechercheAudio/recherche_Audio.h ../IndexationAudio/indexation_Audio.c ../IndexationAudio/indexation_Audio.h ../IndexationRechercheTexte/indexationTexte.c ../IndexationRechercheTexte/indexationTexte.h ../IndexationRechercheTexte/rechercheTexte.c ../IndexationImage/IndexationRechercheImage/indexationImage.h ../IndexationImage/IndexationRechercheImage/indexationImage.c
	gcc -c menu_mae.c
	gcc -c main.c
	gcc -c ../Configuration/configuration.c
	gcc -c ../RechercheAudio/recherche_Audio.c
	gcc -c ../IndexationAudio/indexation_Audio.c
	gcc -c ../IndexationRechercheTexte/indexationTexte.c
	gcc -c ../IndexationRechercheTexte/rechercheTexte.c
	gcc -c ../IndexationImage/IndexationRechercheImage/indexationImage.c
	gcc -c ../IndexationImage/IndexationRechercheImage/compImage.c
	gcc -o menu_mae.out menu_mae.o main.o configuration.o recherche_Audio.o indexation_Audio.o indexationTexte.o rechercheTexte.o indexationImage.o compImage.o -g
	./menu_mae.out

clean :
	rm -f *.o*
