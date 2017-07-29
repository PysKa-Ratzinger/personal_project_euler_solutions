#include <stdio.h>

#define TARGET 500

int num_divisors(unsigned long long number){
    if(number == 1) return 1;
    int res = 1;
    for(unsigned long long i=2; i<=number; i++){
        int cardinal = 0;
        while(number % i == 0){
            cardinal++;
            number /= i;
        }
        if(cardinal){
            res *= (cardinal+1);
        }
    }
    return res;
}

int main(){
    unsigned long long index = 1;
    unsigned long long curr_triangle = 1;
    while(num_divisors(curr_triangle) <= TARGET) curr_triangle += ++index;
    printf("If you can trust me, the number you "
            " are looking for is %llu, %d\n", curr_triangle,
            num_divisors(curr_triangle));
    return 0;
}

