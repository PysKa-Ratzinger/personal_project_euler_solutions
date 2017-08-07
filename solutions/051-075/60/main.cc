#include <stdio.h>
#include <math.h>
#include "../../utils/primes.hpp"

#define NUM_PRIMES 5

unsigned long num_digits(unsigned long number){
    unsigned long res = 0;
    while(number){
        number /= 10;
        res++;
    }
    return res;
}

unsigned long concat(unsigned long num1, unsigned long num2){
    return num1 * pow(10, num_digits(num2)) + num2;
}

bool checkConcatPrime(unsigned long num1, unsigned long num2){
    unsigned long concat1 = concat(num1, num2);
    unsigned long concat2 = concat(num2, num1);
    return isPrime(concat1) && isPrime(concat2);
}

bool recurr(unsigned long buffer[NUM_PRIMES], int depth){
    size_t index = NUM_PRIMES-depth-1;
    buffer[depth] = getPrime(index);
    while(depth == 0 || buffer[depth] < buffer[depth-1]){
        bool concatsWithAll = true;
        for(int i=0; i<depth; i++){
            if(!checkConcatPrime(buffer[i], buffer[depth])){
                concatsWithAll = false;
                break;
            }
        }
        if(concatsWithAll){
            if(depth == NUM_PRIMES-1){
                return true;
            }else if(recurr(buffer, depth+1)){
                return true;
            }
        }
        buffer[depth] = getPrime(++index);
    }
    return false;
}

int main(){
    unsigned long res = 0;

    unsigned long buffer[NUM_PRIMES];
    recurr(buffer, 0);

    for(int i=0; i<NUM_PRIMES; i++){
        res += buffer[i];
    }

    printf("If you can trust me, the number you are looking for is %lu\n", res);

    return 0;
}
