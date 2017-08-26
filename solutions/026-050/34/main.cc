#include <stdio.h>

#define MAX_NUM 2600000

int facts[10];

int factorial(int num){
    if(num == 0)
        return 1;
    if(num == 1)
        return 1;
    return num * factorial(num-1);
}

bool magic(unsigned long long number){
    unsigned long long temp = number;
    unsigned long long temp2 = 0;
    while(temp > 0){
        unsigned long long dig = temp % 10;
        temp2 += facts[dig];
        temp /= 10;
    }
    return temp2 == number;
}

int main(){
    unsigned long long res = 0;
    
    for(int i=0; i<10; i++){
        facts[i] = factorial(i);
    }
    
    for(unsigned long long i=3; i<MAX_NUM; i++){
        if(magic(i)){
            printf("%llu is magic\n", i);
            res += i;
        }
    }
    
    printf("If you can trust me, the number you are looking for is %llu.\n", res);
    return 0;
}
