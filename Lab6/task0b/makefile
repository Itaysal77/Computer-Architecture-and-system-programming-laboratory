all: task0b

task0b: task0b.o LineParser.o
	gcc -m32 -Wall  -o myshell task0b.o LineParser.o

LineParser.o : LineParser.c LineParser.h
	gcc -m32 -Wall  -c  LineParser.c -o LineParser.o	

task0b.o : task0b.c
	gcc -m32 -Wall -c task0b.c -o task0b.o

.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o myshell