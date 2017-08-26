main: main.cc number.cc
	g++ -Wall -Wextra -o main main.cc number.cc

run: main
	./main

debug: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

profile: main
	valgrind --tool=callgrind ./main

clean:
	rm -fv main
