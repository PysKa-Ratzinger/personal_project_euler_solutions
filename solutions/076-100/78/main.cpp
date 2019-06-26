#include <stdio.h>

#include <gmpxx.h>

#include "fast_div.hpp"
#include "partitions.hpp"

int main (int argc, char* argv[]) {
	for (int i=2; i<200000; i++) {
		long long L = PartitionsMod(i, 1000000);
		if (L == 0) {
			printf("Got(%d) -> %lld\n", i, L);
			break;
		}
		if (i % 1000 == 0) {
			printf("%d\n", i);
		}
	}

	return 0;
}

