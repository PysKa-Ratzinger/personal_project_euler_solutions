#include <stdio.h>

unsigned long res = 1;
unsigned long num_dig = 0;
unsigned long target = 1;
unsigned long target_nums = 7;

void process_digit(int digit){
    num_dig++;
    if(num_dig == target){
        res *= digit;
        target *= 10;
        target_nums--;
    }
}

int num_digits(int number){
    int res = 0;
    while(number){
        res++;
        number /= 10;
    }
    return res;
}

int reverse(int number){
    int res = 0;
    while(number){
        res *= 10;
        res += number % 10;
        number /= 10;
    }
    return res;
}

void process_number(int number){
    int digs = num_digits(number);
    number = reverse(number);
    int temp = 0;
    while(number){
        process_digit(number % 10);
        number /= 10;
        temp++;
    }
    for(;temp < digs; temp++){
        process_digit(0);
    }
}

int main(){
    for(int i=1; target_nums!=0; i++){
        process_number(i);
    }

    printf("If you can trust me, the number you are looking for is %lu\n", res);
    return 0;
}
