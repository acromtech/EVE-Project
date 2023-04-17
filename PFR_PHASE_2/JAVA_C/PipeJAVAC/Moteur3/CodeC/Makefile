main: javaBridge.c wrapperPFR.h ../Menu/menu_mae.h ../Menu/menu_mae.c ../Configuration/configuration.c ../Configuration/configuration.h ../RechercheAudio/recherche_Audio.c ../RechercheAudio/recherche_Audio.h ../IndexationAudio/indexation_Audio.c ../IndexationAudio/indexation_Audio.h ../IndexationRechercheTexte/indexationTexte.c ../IndexationRechercheTexte/indexationTexte.h ../IndexationRechercheTexte/rechercheTexte.c ../IndexationImage/IndexationRechercheImage/indexationImage.h ../IndexationImage/IndexationRechercheImage/indexationImage.c javaBridge.c
	gcc -c javaBridge.c
	gcc -c wrapperPFR.c
	gcc -c ../Menu/menu_mae.c
	gcc -c ../Configuration/configuration.c
	gcc -c ../RechercheAudio/recherche_Audio.c
	gcc -c ../IndexationAudio/indexation_Audio.c
	gcc -c ../IndexationRechercheTexte/indexationTexte.c
	gcc -c ../IndexationRechercheTexte/rechercheTexte.c
	gcc -c ../IndexationImage/IndexationRechercheImage/indexationImage.c
	gcc -c ../IndexationImage/IndexationRechercheImage/compImage.c
	gcc -o main.out configuration.o recherche_Audio.o indexation_Audio.o indexationTexte.o rechercheTexte.o indexationImage.o compImage.o menu_mae.o wrapperPFR.o javaBridge.o libivy.a libpcre.a
	./main.out 0 3

clean:
	rm -f main
