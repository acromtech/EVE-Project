recherche : tst_rechercheTexte.c rechercheTexte.c indexationTexte.h cJSON.h cJSON.c
	gcc -c tst_rechercheTexte.c
	gcc -c rechercheTexte.c
	gcc -c cJSON.c
	gcc -o test1.out tst_rechercheTexte.o rechercheTexte.o cJSON.o -g
	rm -rf *.o
	./test1.out ../bin/data/

indexation : indexationTexte.c tst_indexationTexte.c indexationTexte.h cJSON.h cJSON.c
	gcc -c indexationTexte.c
	gcc -c tst_indexationTexte.c
	gcc -c cJSON.c
	gcc -o test.out indexationTexte.o tst_indexationTexte.o cJSON.o -g
	rm -rf *.o
	./test.out ../bin/data/

suppIndexation : indexationTexte.c tst_supIndexationTexte.c indexationTexte.h cJSON.h cJSON.c
	gcc -c indexationTexte.c
	gcc -c tst_supIndexationTexte.c
	gcc -c cJSON.c
	gcc -o test.out indexationTexte.o tst_supIndexationTexte.o cJSON.o -g
	rm -rf *.o
	./test.out ../bin/data/

clean :
	rm -rf *.o *.out
	rm -rf ../bin/data/*.clean ../bin/data/*.tok ../bin/data/*.json
	echo > ../bin/fichiersIndexation/base_descripteur.csv
	echo > ../bin/fichiersIndexation/liste_descripteur.csv
	echo > ../bin/fichiersIndexation/table_descripteur.csv
