#include <stdio.h>

unsigned long long reverse(unsigned long long number){
    unsigned long long res = 0;
    while(number){
        res *= 10;
        res += number % 10;
        number /= 10;
    }
    return res;
}

int is_palindrome(unsigned long long number){
    return number == reverse(number);
}

unsigned long long magic(){
    unsigned long long res = 0;
    for(int i=100; i<1000; i++){
        for(int j=i+1; j<1000; j++){
            unsigned long long temp = (unsigned long long)i * j;
            if(temp > res && is_palindrome(temp)){
                res = temp;
            }
        }
    }
    return res;
}

int main(){
    unsigned long long res = 0;
    
    res = magic();

    printf("If you can trust me, the number "
           "you are looking for is %llu\n", res);
    return 0;
}

