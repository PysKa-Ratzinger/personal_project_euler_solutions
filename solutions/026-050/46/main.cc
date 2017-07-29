#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#define VEC_MAX 1024

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

bool is_square(unsigned long number){
    unsigned long i=1;
    for(;i*i<number; i++);
    return i*i == number;
}

int main(){
    unsigned long res = 0;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(unsigned long i=3;; i+=2){
        if(is_prime(i)) continue;
        bool found_answer = false;
        for(unsigned long j=1;; j++){
            unsigned long prime = get_prime(j);
            if(prime >= i) break;
            if(is_square((i - prime)/2)){
                found_answer = true;
                break;
            }
        }
        if(!found_answer){
            res = i;
            break;
        }
    }
    
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    unsigned long duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("If you can trust me, the number you are looking for is %lu\n", res);
    printf("Execution time: %.6fs\n", ((double)duration)/1000000);
    return 0;
}
