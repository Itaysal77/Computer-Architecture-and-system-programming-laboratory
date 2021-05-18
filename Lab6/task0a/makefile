all: mypipe
	
mypipe: mypipe.c
	gcc -g -m32 -Wall -o mypipe mypipe.c

.PHONY: clean
clean:
	rm -rf ./*.o mypipe
