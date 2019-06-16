#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <set>
#include <string>

uint64_t factorial_digits[20] = {0};

uint64_t factorial(uint64_t a) {
	uint64_t result = 1;
	while (a > 1) {
		result *= a;
		a--;
	}
	return result;
}

void init_digits() {
	for (int i=0; i<20; i++) {
		factorial_digits[i] = factorial(i);
	}
}

uint64_t getNextElem(uint64_t num) {
	uint64_t result = 0;
	while (num) {
		result += factorial_digits[num%10];
		num /= 10;
	}
	return result;
}

int countChain(uint64_t num) {
	std::set<uint64_t> set;
	set.insert(num);
	num = getNextElem(num);
	int result = 1;
	while (set.count(num) == 0) {
		set.insert(num);
		result++;
		if (result > 60) /* don't care about these ones */
			break;
		num = getNextElem(num);
	}
	return result;
}

uint64_t getPermutations(uint64_t num) {
	int digs[10] {0};
	while (num) {
		digs[num%10]++;
		num /= 10;
	}
	uint64_t numdigs = 0;
	uint64_t div = 1;
	for (int i=0; i<10; i++) {
		int num = digs[i];
		if (num) {
			numdigs += num;
			if (num > 1) {
				div *= factorial_digits[num];
			}
		}
	}
	return ((numdigs - digs[0]) * factorial_digits[numdigs-1]) / div;
}

int countChainMagicImpl(uint64_t curr, int digits, int gte, bool canZero) {
	int result = 0;
	if (digits) {
		if (curr && canZero) {
			result += countChainMagicImpl(curr * 10, digits-1, gte,
					canZero);
		}
		for (int i=gte; i<10; i++) {
			result += countChainMagicImpl(curr * 10 + i, digits-1,
					i, curr == 0);
		}
		return result;
	}
	if (countChain(curr) == 60) {
		printf("Number %ld passes, with %ld permutations.\n", curr,
				getPermutations(curr));
		return getPermutations(curr);
	}
	return 0;
}

int countChainMagic(int digits) {
	return countChainMagicImpl(0, digits, 0, true);
}

int main (int argc, char* argv[]) {
	init_digits();

	printf("Result: %d\n", countChainMagic(6));
}

