#include <stdio.h>

#include <map>
#include <chrono>

std::map<int, int> cache;

// See http://mathworld.wolfram.com/PartitionFunctionP.html (Formula 11)
int P(int n) {
	if (n == 0)
		return 1;
	if (n < 0)
		return 0;
	auto it = cache.find(n);
	if (it != cache.end()) {
		return it->second;
	}
	int res = 0;
	for (int k=1; k<=n; k++) {
		int d;
		d =  P(n - ((k * (3*k - 1)) / 2));
		d += P(n - ((k * (3*k + 1)) / 2));
		if (k % 2 != 0)
			res += d;
		else
			res -= d;
	}
	cache.insert(std::make_pair(n, res));
	return res;
}

int main (int argc, char* argv[]) {
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

	unsigned long res;
	res = P(100);
	printf("Cache size: %ld\n", cache.size());

	std::chrono::high_resolution_clock::time_point t2 =
		std::chrono::high_resolution_clock::now();
	unsigned long duration =
		std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	printf("If you can trust me, the number you are "
			"looking for is %lu\n", res);
	printf("Execution time: %lu,%03lu ms\n", duration/1000, duration%1000);
}

