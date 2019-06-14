#include <stdio.h>
#include <stdlib.h>
#include "primes.hpp"

#define PRIME_BUFFER 200000

unsigned *primes;
unsigned primes_sz = 0;
bool primes_initialized = false;

void initialize_primes() {
	primes = (unsigned*)malloc(sizeof(unsigned)*PRIME_BUFFER);
	primes[0] = 2;
	primes[1] = 3;
	primes[2] = 0;
	primes_sz = 2;
	primes_initialized = true;
}

unsigned long getPrime(unsigned index){
	if (!primes_initialized)
		initialize_primes();

	if(index >= PRIME_BUFFER){
		fprintf(stderr, "Buffer overflow imminent. Stopping "
				"execution.\n");
		exit(EXIT_FAILURE);
	}

	while(index >= primes_sz){
		unsigned number = primes[primes_sz-1]+2;
		while(!isPrime(number))
			number += 2;
		primes[primes_sz++] = number;
	}

	return primes[index];
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

