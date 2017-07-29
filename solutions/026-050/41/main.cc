#include <stdio.h>

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

bool is_prime(unsigned long number){
    for(unsigned long i=2; i<=number/i; i++){
        if(number % i == 0) return false;
    }
    return true;
}

int main(){
    for(unsigned long i = 1000000000; i>0; i--){
        if(is_pandigital(i)){
            printf("%lu\n", i);
            if(is_prime(i)){
                printf("If you can trust me, the number you are looking for is %lu\n", i);
                break;
            }
        }
    }

    return 0;
}
