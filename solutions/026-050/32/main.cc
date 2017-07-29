#include <stdio.h>

int num_digs(int a){
    int res = 0;
    while(a>0){
        a/=10;
        res++;
    }
    return res;
}

void fill_digits(int num, bool *temp){
    while(num>0){
        int dig = num % 10;
        num /= 10;
        temp[dig] = true;
    }
}

bool is_pandigital(int num1, int num2, int num3){
    bool temp[10];
    for(int i=0; i<10; i++){
        temp[i] = false;
    }
    fill_digits(num1, temp);
    fill_digits(num2, temp);
    fill_digits(num3, temp);
    for(int i=1; i<10; i++){
        if(temp[i] == false)
            return false;
    }
    return true;
}

int main(){
    int res = 0;

    for(int i=1; i<100000; i++){
        for(int a=2; a<=i/a; a++){
            if(i % a != 0)
                continue;
            int div = i/a;
            if(num_digs(i) + num_digs(a) + num_digs(div) == 9 && is_pandigital(i, a, div)){
                printf("%d = %d * %d\n", i, a, div);
                res += i;
                break;
            }
        }
    }
    
    printf("If you can trust me, the number you are looking for is %d.\n", res);
    return 0;
}
