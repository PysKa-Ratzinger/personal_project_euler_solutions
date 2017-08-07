#include <stdio.h>
#include "../../utils/primes.hpp"

#define NUM_DIGITS 9

bool is_pandigital(unsigned long number){
    bool vec[9];
    for(int i=0; i<9; i++){
        vec[i] = false;
    }
    while(number){
        int dig = number % 10;
        number /= 10;
        if(dig == 0) return false;
        if(vec[dig-1] == true) return false;
        vec[dig-1] = true;
    }
    for(int i=0; i<9; i++){
        if(vec[i] == false){
            for(int j=i+1; j<9; j++){
                if(vec[j] == true) return false;
            }
            break;
        }
    }
    return true;
}

bool isContinuous(bool* buffer, unsigned long buffer_size){
    for(unsigned i=1; i<buffer_size; i++){
        if(buffer[i] == true && buffer[i-1] == false){
            return false;
        }
    }
    return true;
}

unsigned long recursive_magic(bool buffer[NUM_DIGITS], unsigned long curr, int depth){
    unsigned long solution = 0;
    if(isPrime(curr) && isContinuous(buffer, NUM_DIGITS)){
        solution = curr;
    }
    for(int i=8; i>=0; i--){
        if(!buffer[i]){
            buffer[i] = true;
            unsigned long temp = recursive_magic(buffer, curr*10 + i+1, depth+1);
            if(temp > solution){
                solution = temp;
                break;
            }
            buffer[i] = false;
        }
    }
    return solution;
}

int main(){
    unsigned long res = 0;

    bool buffer[NUM_DIGITS]{false};
    res = recursive_magic(buffer, 0, 0);

    printf("If you can trust me, the number you are looking for is %lu\n", res);

    return 0;
}
