recherche : tst_rechercheTexte.c rechercheTexte.c indexationTexte.h
	gcc -c tst_rechercheTexte.c
	gcc -c rechercheTexte.c
	gcc -o test1.out tst_rechercheTexte.o rechercheTexte.o -g
	rm -rf *.o
	./test1.out ../bin/data/

indexation : indexationTexte.c tst_indexationTexte.c indexationTexte.h
	gcc -c indexationTexte.c
	gcc -c tst_indexationTexte.c
	gcc -o test.out indexationTexte.o tst_indexationTexte.o -g
	rm -rf *.o
	./test.out ../bin/data/

suppIndexation : indexationTexte.c tst_supIndexationTexte.c indexationTexte.h
	gcc -c indexationTexte.c
	gcc -c tst_supIndexationTexte.c
	gcc -o test.out indexationTexte.o tst_supIndexationTexte.o -g
	rm -rf *.o
	./test.out ../bin/data/

clean :
	echo > ../bin/fichiersIndexation/base_descripteur.csv
	echo > ../bin/fichiersIndexation/liste_descripteur.csv
	echo > ../bin/fichiersIndexation/table_descripteur.csv
