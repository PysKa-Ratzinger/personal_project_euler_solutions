#include <stdio.h>
#include <stdlib.h>

#include "primes.hpp"
#include "permutations.hpp"

#define BUF_SZ 100
#define DEBUG 0

long get_quant_numbers_mult_until(long max, long div) {
	return max / div;
}

struct cresult {
	long max;
	long result;
};

long get_quant_numbers_until(long max, long* divs, long divs_size) {
	struct cresult res;
	res.max = max;
	res.result = max;
#if DEBUG
	printf("Processing max (%ld) for divs: ", max);
	for (long i=0; i<divs_size; i++) {
		printf("%ld%s", divs[i], i == divs_size - 1 ? "" : ", ");
	}
	printf("\n");
#endif
	processPermutations(divs, sizeof(long), divs_size,
			[](void* b, size_t num_elems, void* arg) -> bool {
			long* buf = (long*) b;
			long mult = 1;
			for (long i=0; i<num_elems; i++) {
			mult *= buf[i];
			}
			struct cresult* res = (struct cresult*) arg;
			long num_mults = get_quant_numbers_mult_until(res->max,
					mult);
			if (num_elems % 2 != 0) {
			res->result -= num_mults;
			} else {
			res->result += num_mults;
			}
			return true;
			}, &res);
	return res.result;
}

long get_quant_numbers(long min, long max, long* divs, long divs_size) {
	long result = get_quant_numbers_until(max, divs, divs_size) -
		get_quant_numbers_until(min-1, divs, divs_size);
#if DEBUG
	printf("There are (%ld) numbers between (%ld) and (%ld) for divs: ",
			result, min, max);
	for (long i=0; i<divs_size; i++) {
		printf("%ld%s", divs[i], i == divs_size - 1 ? "" : ", ");
	}
	printf("\n");
#endif
	return result;
}

long get_divs(long number, long* divs, long max_size) {
	long index = 0;
	long div_sz = 0;
	long prime = getPrime(index);
	while (prime <= number/prime) {
		if (number % prime == 0) {
			number /= prime;
			divs[div_sz] = prime;
			div_sz++;
			if (div_sz == max_size) {
				fprintf(stderr, "BUFFER full. Terminating "
						"program.");
				exit(1);
			}
			while (number % prime == 0) {
				number /= prime;
			}
		}
		index++;
		prime = getPrime(index);
	}
	if (number != 1) {
		divs[div_sz++] = number;
	}
	return div_sz;
}

long list_fractions(long max_number) {
	long res = 0;
	long divs[BUF_SZ];
	for (long i=1; i<max_number; i++) {
		long num_divs = get_divs(i, divs, BUF_SZ);
		res += get_quant_numbers(i+1, max_number, divs, num_divs);
	}
	return res;
}

int main (int argc, char* argv[]) {
	long result = list_fractions(1000000);
	printf("Got result: %ld\n", result);
}

