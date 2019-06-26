#pragma once

#include <gmpxx.h>

#include <stdlib.h>

#include <map>

long long PartitionsMod(long long n, long long mod) {
	static std::map<long long, long long> cache;
	static long long lastMod = -1;
	if (lastMod == -1 || lastMod != mod) {
		lastMod = mod;
		cache.clear();
	}

	if (n == 0)
		return 1;
	if (n < 0)
		return 0;
	auto it = cache.find(n);
	if (it != cache.end())
		return it->second;

	long long res = 0;
	for (long long k=1; k<=n; k++) {
		long long d;
		long long k31 = 3*k - 1;
		long long km1 = k * k31;
		long long km2 = km1 + 2 * k;
		d =  PartitionsMod(n - km1 / 2, mod);
		d += PartitionsMod(n - km2 / 2, mod);
		if (k % 2 != 0)
			res += d;
		else
			res -= d;
	}

	res %= mod;
	if (res < 0)
		res += mod;

	cache.insert(std::make_pair(n, res));
	return res;
}

// See http://mathworld.wolfram.com/PartitionFunctionP.html (Formula 11)
mpz_class Partitions(mpz_class n) {
	static std::map<mpz_class, mpz_class> cache;

	if (n == 0)
		return 1;
	if (n < 0)
		return 0;
	auto it = cache.find(n);
	if (it != cache.end())
		return it->second;

	mpz_class res = 0;
	for (mpz_class k=1; k<=n; k++) {
		mpz_class d;
		mpz_class k31 = 3*k - 1;
		mpz_class km1 = k * k31;
		mpz_class km2 = km1 + 2 * k;
		d =  Partitions(n - km1 / 2);
		d += Partitions(n - km2 / 2);
		if (k % 2 != 0)
			res += d;
		else
			res -= d;
	}

	cache.insert(std::make_pair(n, res));
	return res;
}

