main:main.o functions.o translators.o stageOne.o stageTwo.o 
	gcc -g -ansi -Wall main.o functions.o translators.o stageOne.o stageTwo.o -o  main -lm
main.o: main.c main.h
	gcc -c -ansi -Wall -pedantic main.c -o main.o -lm
funcs.o: funcs.c
	gcc -c -ansi -Wall -pedantic functions.c -o functions.o -lm
translators.o:
	gcc -c -ansi -Wall -pedantic translators.c -o translators.o -lm
stageOne.o:
	gcc -c -ansi -Wall -pedantic stageOne.c -o stageOne.o -lm
stageTwo.o:
	gcc -c -ansi -Wall -pedantic stageTwo.c -o stageTwo.o -lm	