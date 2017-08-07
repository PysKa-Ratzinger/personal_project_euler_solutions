#include <stdio.h>
#include <stdlib.h>
#include "primes.hpp"

#define PRIME_BUFFER 200000

unsigned primes[PRIME_BUFFER] = {2, 3, 0};
unsigned primes_sz = 2;

unsigned long getPrime(unsigned index){
    if(index >= PRIME_BUFFER){
        fprintf(stderr, "Buffer overflow imminent. Stopping execution.\n");
        exit(EXIT_FAILURE);
    }
    while(index >= primes_sz){
        unsigned number = primes[primes_sz-1]+2;
        while(!isPrime(number)) number += 2;
        primes[primes_sz++] = number;
    }
    return primes[index];
}

bool isPrime(unsigned long number){
    if(number == 0 || number == 1) return false;
    unsigned index = 0;
    unsigned prime = getPrime(index);
    while(prime <= number/prime){
        if(number % prime == 0) return false;
        index++;
        prime = getPrime(index);
    }
    return true;
}
