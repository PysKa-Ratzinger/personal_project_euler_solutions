main: main.o asm.o
	gcc -Wall -o main main.o asm.o

main.o: main.c
	gcc -Wall -c main.c

asm.o: asm.s
	gcc -Wall -c asm.s

run: main
	./main

clean:
	rm -fv main main.o asm.o
