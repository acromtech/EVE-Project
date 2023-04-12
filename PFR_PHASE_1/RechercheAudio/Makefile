
recherche: recherche_Audio.c recherche_Audio.h tst_recherche_Audio.c ../Configuration/configuration.c
	gcc -c recherche_Audio.c
	gcc -c tst_recherche_Audio.c
	gcc -c ../Configuration/configuration.c
	gcc -o recherche.out recherche_Audio.o tst_recherche_Audio.o configuration.o
	./recherche.out


clean : 
	rm -f prog *.o 
	rm -f prog *.out
