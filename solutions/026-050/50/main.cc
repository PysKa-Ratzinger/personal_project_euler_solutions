#include <stdio.h>
#include <stdlib.h>
#include "../../utils/primes.hpp"
#include <chrono>
#include <list>

#define VEC_MAX 100000
#define MAX_VALUE 1000000

int main(){
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    // Since the max_value is pretty small, we can brute-force the answer
    unsigned long res = 0;
    unsigned long num_digits = 0;
    for(unsigned long i = 0; getPrime(i) < MAX_VALUE; i++){
        unsigned long sum = 0;
        unsigned long temp = 0;
        for(unsigned long j = i;; j++){
            unsigned long prime = getPrime(j);
            temp++;
            if(sum + prime >= MAX_VALUE) break;
            sum += prime;
            if(temp > num_digits && isPrime(sum)){
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
