main: main.cpp ../utils/bst.cpp
	g++ -o main main.cpp ../utils/bst.cpp

run: main
	./main

debug: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -fv main
