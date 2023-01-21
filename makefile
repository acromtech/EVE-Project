mae : menu_mae.c menu_mae.h main.c Configuration/configuration.c
	gcc -c menu_mae.c
	gcc -c main.c
	gcc -c Configuration/configuration.c
	gcc -o menu_mae.out menu_mae.o main.o configuration.o
	./menu_mae.out

clean :
	rm -f *.o*