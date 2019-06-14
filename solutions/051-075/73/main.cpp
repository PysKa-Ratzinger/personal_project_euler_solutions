#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "primes.hpp"
#include "permutations.hpp"

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define BUF_SZ 100
#define DEBUG 0

struct cresult {
	long max;
	long min;
	long result;
};

bool handle_permutation(std::vector<long>& perm, struct cresult& res) {
	long mult = 1;
	for (long num : perm) mult *= num;
	long num_mults = res.max / mult - res.min / mult;
	res.result += (perm.size() % 2 != 0 ? -1 : 1) * num_mults;
	return true;
}

long get_quant_numbers(long min, long max, std::vector<long>& divs) {
	struct cresult res;
	res.max = max;
	res.min = min;
	res.result = max - min;
#if DEBUG
	printf("Processing max (%ld) for divs: ", max);
	for (long num : divs) {
		printf("%ld, ", num);
	}
	printf("\n");
#endif
	processPermutations(divs, handle_permutation, res);
#if DEBUG
	printf("There are (%ld) numbers between (%ld) and (%ld) for divs: ",
			res.result, min, max);
	for (long num : divs) {
		printf("%ld, ", num);
	}
	printf("\n");
#endif
	return res.result;
}

std::vector<long> get_divs(long number) {
	long index = 0;
	long prime = getPrime(index);
	std::vector<long> res;
	while (prime <= number/prime) {
		if (number % prime == 0) {
			number /= prime;
			res.push_back(prime);
			while (number % prime == 0) {
				number /= prime;
			}
		}
		index++;
		prime = getPrime(index);
	}
	if (number != 1) {
		res.push_back(number);
	}
	return res;
}

long list_fractions(long max_number) {
	long res = 0;
	for (long i=2; i<max_number; i++) {
		std::vector<long> divs = get_divs(i);
		long range_min = MIN(i*2-1, max_number);
		long range_max = MIN(i*3, max_number);
		res += get_quant_numbers(range_min, range_max, divs);
	}
	return res;
}

int main (int argc, char* argv[]) {
	long result = list_fractions(12000);
	printf("Got result: %ld\n", result);
}

