
SOURCES := $(wildcard ./*.cc ./**/*.cc ../utils/*.cc ../utils/**/*.cc)

CXXFLAGS := -std=c++11 -Wall -Werror -Wextra -Wformat-security
LDLIBS := -lpthread -ldl -lrt -lcppunit -lm

main: $(SOURCES)
	g++ -g -O0 -o main -I. -I../utils/ $+ $(CXXFLAGS) $(LDLIBS)

run: main
	./main

clean:
	rm -rvf ./main

