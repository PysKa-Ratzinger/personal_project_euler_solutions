#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>

#include "primes.hpp"

std::vector<unsigned> primes;
bool primes_initialized = false;

void initialize_primes() {
	primes.clear();
	primes.push_back(2);
	primes.push_back(3);
	primes_initialized = true;
}

unsigned long getPrime(unsigned index){
	if (!primes_initialized)
		initialize_primes();

	while(index >= primes.size()){
		unsigned number = primes[primes.size()-1]+2;
		while(!isPrime(number))
			number += 2;
		primes.push_back(number);
	}

	return primes[index];
}

std::list<unsigned long> getPrimesSmallerThan(unsigned long max) {
	unsigned index = 0;
	unsigned long prime = getPrime(index);
	std::list<unsigned long> res;

	while (prime < max) {
		res.push_back(prime);
		index++;
		prime = getPrime(index);
	}

	return res;
}

std::vector<unsigned long> getDivs(unsigned long number, bool withReps) {
	unsigned long index = 0;
	unsigned long prime = getPrime(index);
	std::vector<unsigned long> res;
	while (prime <= number/prime) {
		if (number % prime == 0) {
			number /= prime;
			res.push_back(prime);
			while (number % prime == 0) {
				number /= prime;
				if (withReps) {
					res.push_back(prime);
				}
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

bool isPrime(unsigned long number){
	if (!primes_initialized)
		initialize_primes();

	if(number == 0 || number == 1)
		return false;

	unsigned index = 0;
	unsigned prime = getPrime(index);
	while(prime*prime <= number){
		if(number % prime == 0)
			return false;
		index++;
		prime = getPrime(index);
	}
	return true;
}

