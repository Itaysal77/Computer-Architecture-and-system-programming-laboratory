all: task3a

task3a: task3a.o LineParser.o
	gcc -m32 -Wall  -o myshell task3a.o LineParser.o

LineParser.o : LineParser.c LineParser.h
	gcc -m32 -Wall  -c  LineParser.c -o LineParser.o	

task3a.o : task3a.c
	gcc -m32 -Wall -c task3a.c -o task3a.o

.PHONY: clean


clean: 
	rm -f *.o myshell