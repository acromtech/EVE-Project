test : menu_mae.c menu_mae.h main.c ../Configuration/configuration.c ../Configuration/configuration.h ../RechercheAudio/recherche_Audio.c ../RechercheAudio/recherche_Audio.h ../IndexationAudio/indexation_Audio.c ../IndexationAudio/indexation_Audio.h ../IndexationRechercheTexte/indexationTexte.c ../IndexationRechercheTexte/indexationTexte.h ../IndexationRechercheTexte/rechercheTexte.c ../IndexationImage/IndexationRechercheImage/indexationImage.h ../IndexationImage/IndexationRechercheImage/indexationImage.c javaBridge.c
	gcc -c javaBridge.c
	gcc -c ../Configuration/configuration.c
	gcc -c ../RechercheAudio/recherche_Audio.c
	gcc -c ../IndexationAudio/indexation_Audio.c
	gcc -c ../IndexationRechercheTexte/indexationTexte.c
	gcc -c ../IndexationRechercheTexte/rechercheTexte.c
	gcc -c ../IndexationImage/IndexationRechercheImage/indexationImage.c
	gcc -c ../IndexationImage/IndexationRechercheImage/compImage.c
	gcc -o test.out configuration.o recherche_Audio.o indexation_Audio.o indexationTexte.o rechercheTexte.o indexationImage.o compImage.o javaBridge.o -g
	./test.out


clean :
	rm -f *.o*
	echo > ../BaseFichiersTexte/FichiersDeDescription/base_descripteur.csv
	echo > ../BaseFichiersTexte/FichiersDeDescription/liste_descripteur.csv
	echo > ../BaseFichiersTexte/FichiersDeDescription/table_descripteur.csv
