#include <stdio.h>
#include <stdlib.h>

#define LIMIT 2000000
#define PRIME_BUFFER_SZ 512

unsigned long primes[PRIME_BUFFER_SZ];
unsigned long primes_size = 0;

bool isPrime(unsigned long number);

unsigned long getPrime(unsigned long index){
    if(index >= PRIME_BUFFER_SZ){
        printf("WARNING: Buffer overflow imminent. Stopping execution...\n");
        exit(EXIT_FAILURE);
    }
    while(index >= primes_size){
        unsigned long i = primes[primes_size-1]+2;
        while(!isPrime(i)) i+=2;
        primes[primes_size++] = i;
    }
    return primes[index];
}

bool isPrime(unsigned long number){
    bool result = true;
    if(number != 2){
        unsigned long i=0;
        unsigned long prime = getPrime(i);

        while(prime<=number/prime){
            if(number % prime == 0){
                result = false;
                break;
            }

            i++;
            prime = getPrime(i);
        }
    }
    return result;
}

int main(){
    unsigned long res = 2;

    primes[0] = 2;
    primes[1] = 3;
    primes_size = 2;
    for(unsigned long i=3; i<LIMIT; i+=2){
        if(isPrime(i)) res += i;
    }

    printf("If you can trust me, the number you "
            "are looking for is %lu\n", res);
    return 0;
}

