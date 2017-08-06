main: main.cc dictionary.cc utils.c
	g++ -g -O2 -Wall -Wextra -o main main.cc dictionary.cc utils.c

run: main
	./main

debug: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -fv main
