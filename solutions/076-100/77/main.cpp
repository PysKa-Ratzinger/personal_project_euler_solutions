#include <stdio.h>
#include <map>
#include <list>

#include "primes.hpp"

#define MIN(a,b) ((a) < (b) ? (a) : (b))

std::map<std::pair<int, int>, int> cache;

int fast_res(int diff, int prev) {
	auto it = cache.find(std::make_pair(diff, prev));
	if (it == cache.end())
		return -1;

	return it->second;
}

void set_cache(int diff, int prev, int res) {
	auto it = cache.find(std::make_pair(diff, prev));
	if (it == cache.end()) {
		cache.insert(std::make_pair(std::make_pair(diff, prev), res));
	}
}

int count2(int diff, int prev) {
	if (diff < 0)
		return 0;
	if (diff == 0) {
		return 1;
	}
	int res = fast_res(diff, prev);
	if (res != -1)
		return res;
	res = 0;
	unsigned long prime;
	int i = prev;
	while (i >= 0) {
		prime = getPrime(i);
		if (prime <= diff) {
			res += count2(diff-prime, i);
		}
		if (i == 0)
			break;
		i--;
	}
	set_cache(diff, prev, res);
	return res;
};

int count1(int num) {
	int res = 0;
	unsigned long prime;
	for (int i=0; (prime=getPrime(i))<=num; i++) {
		res += count2(num-prime, i);
	}
	return res;
}

int main (int argc, char* argv[]) {
	printf("Started searching...\n");
	for (int i=2; i<= 1000; i++) {
		int res = count1(i);
		printf("%d --> %d\n", i, res);
		if (res > 5000) {
			printf("Found: %d\n", res);
			break;
		}
	}
}

