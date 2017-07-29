#include <stdio.h>
#include <math.h>

#define MAX_PROPERTY 11

bool is_prime(unsigned long num){
    if(num <= 1) return false;
    for(unsigned long i=2; i<=num/i; i++){
        if(num % i == 0) return false;
    }
    return true;
}

unsigned long reverse(unsigned long number){
    unsigned long res = 0;
    while(number > 0){
        res *= 10;
        res += number % 10;
        number /= 10;
    }
    return res;
}

bool magic(unsigned long number){
    if(!is_prime(number)) return false;

    unsigned long temp = number / 10;
    while(temp){
        if(!is_prime(temp))
            return false;
        temp /= 10;
    }
    
    temp = reverse(reverse(number) / 10);
    while(temp){
        if(!is_prime(temp))
            return false;
        temp = reverse(reverse(temp) / 10);
    }
    
    return true;
}

int main(){
    unsigned long res = 0;
    
    unsigned long nums = 0;
    
    for(unsigned long i=10; nums<MAX_PROPERTY; i++){
        if(magic(i)){
            nums++;
            res += i;
        }
    }
    
    printf("If you can trust me, the number you are looking for is %lu.\n", res);
    return 0;
}
