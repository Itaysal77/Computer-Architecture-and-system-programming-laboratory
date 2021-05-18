all: exec

libs: asm-lib

asm-lib: asmAssignment0.s
	nasm -g -f elf -o asmAssignment0.o asmAssignment0.s

exec: mainAssignment0.c libs
	gcc -g -m32 -c -o mainAssignment0.o mainAssignment0.c
	gcc -g -m32  mainAssignment0.o asmAssignment0.o -o main
	rm mainAssignment0.o asmAssignment0.o 

.PHONY: clean
clean:
	rm -rf ./*.o main