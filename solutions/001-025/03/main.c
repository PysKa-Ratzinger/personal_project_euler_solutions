#include <stdio.h>

unsigned long long magic(unsigned long long number){
    for(unsigned long long i=2; i<=number; i++){
        while(number%i == 0)
            number /= i;
        if(number == 1) return i;
    }
    return 0;
}

int main(){
    unsigned long long res = 0;
    
    res = magic(600851475143);

    printf("If you can trust me, the number "
           "you are looking for is %llu\n", res);
    return 0;
}

