#include <stdio.h>

#include <map>
#include <chrono>

#include "partitions.hpp"

int main (int argc, char* argv[]) {
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

	unsigned long res;
	res = Partitions(100);

	std::chrono::high_resolution_clock::time_point t2 =
		std::chrono::high_resolution_clock::now();
	unsigned long duration =
		std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	printf("If you can trust me, the number you are "
			"looking for is %lu\n", res);
	printf("Execution time: %lu,%03lu ms\n", duration/1000, duration%1000);
}

