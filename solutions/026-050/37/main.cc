#include <stdio.h>
#include <math.h>
#include "../../utils/primes.hpp"

#define MAX_PROPERTY 11

unsigned long reverse(unsigned long number){
    unsigned long res = 0;
    while(number){
        res *= 10;
        res += number % 10;
        number /= 10;
    }
    return res;
}

bool magic(unsigned long number){
    unsigned long temp = number;
    while(temp){
        if(!isPrime(temp)) return false;
        temp /= 10;
    }

    temp = reverse(reverse(number) / 10);
    while(temp){
        if(!isPrime(temp)) return false;
        temp = reverse(reverse(temp) / 10);
    }

    return true;
}

int main(){
    unsigned long res = 0;

    unsigned long nums = 0;

    for(unsigned long i=11; nums<MAX_PROPERTY; i+=2){
        if(magic(i)){
            nums++;
            res += i;
        }
    }

    printf("If you can trust me, the number you are looking for is %lu.\n", res);
    return 0;
}
