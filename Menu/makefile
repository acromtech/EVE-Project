mae : menu_mae.c menu_mae.h main.c ../Configuration/configuration.c ../Configuration/configuration.h ../RechercheAudio/recherche_Audio.c ../RechercheAudio/recherche_Audio.h ../IndexationAudio/indexation_Audio.c ../IndexationAudio/indexation_Audio.h
	gcc -c menu_mae.c
	gcc -c main.c
	gcc -c ../Configuration/configuration.c
	gcc -c ../RechercheAudio/recherche_Audio.c
	gcc -c ../IndexationAudio/indexation_Audio.c
	gcc -o menu_mae.out menu_mae.o main.o configuration.o recherche_Audio.o indexation_Audio.o
	./menu_mae.out

clean :
	rm -f *.o*