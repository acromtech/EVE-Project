recherche : tst_RGB.c indexationImage.c indexationImage.h cJSON.c cJSON.h
	gcc -c tst_RGB.c
	gcc -c indexationImage.c
	gcc -c comp_image.c
	gcc -c cJSON.c
	gcc -o test.out tst_RGB.o comp_image.o indexationImage.o cJSON.o -g
	./test.out TXT

indexation : indexationImage.c indexationImage.h test_indexationImage.c cJSON.c cJSON.h
	gcc -c test_indexationImage.c
	gcc -c indexationImage.c
	gcc -c cJSON.c
	gcc -o test.out test_indexationImage.o indexationImage.o cJSON.o -g
	./test.out TXT
clean :
	rm -f *.o* 
	echo > base_descripteur_image.csv
	echo > liste_descripteur_image.csv
	
