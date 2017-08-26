main: main.c
	gcc -O3 -Wall -Wextra -o main main.c

run: main
	./main

debug: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -fv main
