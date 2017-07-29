#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <list>

#define VEC_MAX 100000
#define MAX_VALUE 1000000

unsigned long primes[VEC_MAX];
unsigned long prime_sz = 0;

bool is_prime(unsigned long number);

unsigned long get_prime(unsigned long index){
    if(index >= VEC_MAX){
        printf("WARNING! Buffer Overflow imminent! Stopping execution...\n");
        exit(EXIT_FAILURE);
    }

    if(prime_sz == 0){
        primes[0] = 2;
        prime_sz = 1;
    }

    while(index >= prime_sz){
        unsigned long i=primes[prime_sz-1]+1;
        for(; !is_prime(i); i++);
        primes[prime_sz++] = i;
    }
    return primes[index];
}

bool is_prime(unsigned long number){
    if(number == 1) return true;
    for(unsigned int i=0; ; i++){
        unsigned long prime = get_prime(i);
        if(prime > number / prime) return true;
        if(number % prime == 0) return false;
    }
}

int main(){
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    
    // Since the max_value is pretty small, we can brute-force the answer
    unsigned long res = 0;
    unsigned long num_digits = 0;
    for(unsigned long i = 0; get_prime(i) < MAX_VALUE; i++){
        unsigned long sum = 0;
        unsigned long temp = 0;
        for(unsigned long j = i;; j++){
            unsigned long prime = get_prime(j);
            temp++;
            if(sum + prime >= MAX_VALUE) break;
            sum += prime;
            if(temp > num_digits && is_prime(sum)){
                printf("New max size: %lu, starting with prime number %lu\n", temp, get_prime(i));
                num_digits = temp;
                res = sum;
            }
        }
    }
    
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    unsigned long duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("If you can trust me, the number you are looking for is %lu\n", res);
    printf("Execution time: %.6fs\n", ((double)duration)/1000000);
    return 0;
}
