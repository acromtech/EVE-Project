
histogramme: indexation_Audio.c indexation_Audio.h tst_indexation_Audio.c ../Configuration/configuration.c
	gcc -c indexation_Audio.c
	gcc -c ../Configuration/configuration.c
	gcc -c tst_indexation_Audio.c
	gcc -o histog.out indexation_Audio.o tst_indexation_Audio.o configuration.o
	./histog.out


clean : 
	rm -f prog *.o 
	rm -f prog *.out
