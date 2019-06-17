#include <stdio.h>
#include <math.h>
#include <stdint.h>

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdexcept>

#include "permutations.hpp"
#include "primes.hpp"

bool isRightTrianglePossible(uint64_t b, uint64_t P) {
	return (P * P) % ((P - b) << 1) == 0;
}

double getLimit(uint64_t P) {
	return (double)P / (2 + sqrt(2));
}

struct triangleArgs {
	triangleArgs(uint64_t P) : P(P), half_P(P >> 1) {}

	uint64_t P;
	uint64_t half_P;
	std::set<unsigned long> results;
};

bool isTrianglePossible(std::vector<unsigned long>& factors,
		struct triangleArgs& args) {
	unsigned long number = 1;
	for (unsigned long f : factors) {
		number *= f;
	}

	unsigned long result = args.P - number;
	if (number > args.half_P && number < args.P) {
		args.results.insert(result);
	}
	return true;
}

int countTriangles2(uint64_t P) {
	int limit = (int) getLimit(P);
	std::vector<unsigned long> divs = getDivs(P, true);
	divs.insert(divs.end(), divs.begin(), divs.end());
	if (divs.front() == 2) {
		divs.erase(divs.begin());
	}
	int res = 0;
	struct triangleArgs args(P);
	processCombinations(divs, isTrianglePossible, args);
	return args.results.size() >> 1;
}

int countTriangles(uint64_t P) {
	int limit = (int) getLimit(P);
	int res = 0;
	for (int i=1; i<=limit; i++) {
		if (isRightTrianglePossible(i, P)) {
			res++;
		}
	}
	return res;
}

int magic() {
	int res = 0;
	for (int i=12; i <= 1500000; i+=2) {
		if (i % 10000 == 0) {
			printf("%d\n", i);
		}
		if (countTriangles2(i) == 1) {
			res++;
		}
	}
	return res;
}

int main (int argc, char* argv[]) {
	printf("Result: %d\n", magic());
}

