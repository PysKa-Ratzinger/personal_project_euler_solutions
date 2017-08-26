#include <stdio.h>
#include <stdlib.h>
#include "../../utils/primes.hpp"

#define LIMIT 2000000

int main(){
    unsigned long res = 2;

    for(unsigned long i=3; i<LIMIT; i+=2){
        if(isPrime(i)) res += i;
    }

    printf("If you can trust me, the number you "
            "are looking for is %lu\n", res);
    return 0;
}
