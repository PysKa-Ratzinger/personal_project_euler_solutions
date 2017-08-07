#include <stdio.h>
#include <stdlib.h>
#include "../../utils/primes.hpp"
#include <chrono>

#define TARGET_RATIO 0.1

unsigned long magic(double target_ratio){
    unsigned long side = 1;
    unsigned long curr = 1;
    unsigned long step = 2;

    unsigned long primes = 0;
    unsigned long total = 1;
    bool running = true;
    while(running){
        side += 2;
        for(int i=0; i<4; i++){
            curr += step;
            if(isPrime(curr)){
                primes++;
            }
            total++;
            double ratio = (double) primes / total;
            if(ratio < target_ratio){
                running = false;
                break;
            }
        }
        step += 2;
    }

    return side;
}

int main(){
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    unsigned long res = magic(TARGET_RATIO);

    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    unsigned long duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("If you can trust me, the number you are "
            "looking for is %lu\n", res);
    printf("Execution time: %lums\n", duration/1000);
    return 0;
}
