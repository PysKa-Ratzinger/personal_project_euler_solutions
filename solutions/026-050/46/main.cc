#include <stdio.h>
#include <stdlib.h>
#include "../../utils/primes.hpp"
#include <chrono>

bool is_square(unsigned long number){
    unsigned long i=1;
    for(;i*i<number; i++);
    return i*i == number;
}

int main(){
    unsigned long res = 0;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(unsigned long i=3;; i+=2){
        if(isPrime(i)) continue;
        bool found_answer = false;
        for(unsigned long j=1;; j++){
            unsigned long prime = getPrime(j);
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
