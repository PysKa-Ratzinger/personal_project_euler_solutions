#include <stdio.h>
#include "../../utils/primes.hpp"
#include <unordered_set>
#include <cmath>

#define MAX_NUM 1000000

int num_digits(int num){
    int res = 0;
    while(num > 0){
        res++;
        num /= 10;
    }
    return res;
}

int rot(int num, int num_size){
    return num / 10 + num % 10 * pow(10, num_size-1);
}

bool magic(int num){
    int num_size = num_digits(num);
    if(isPrime(num)){
        for(int i=1; i<num_size; i++){
            num = rot(num, num_size);
            if(!isPrime(num)) return false;
        }
        return true;
    }
    return false;
}

int main(){
    int res = 0;

    for(int i=2; i<MAX_NUM; i++){
        if(magic(i)){
            res++;
        }
    }

    printf("If you can trust me, the number you are looking for is %d.\n", res);
    return 0;
}
