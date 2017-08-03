main: main.cc
	g++ -O2 -Wall -Wextra -o main main.cc

run: main
	./main

debug: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -fv main
