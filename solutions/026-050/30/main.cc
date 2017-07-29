#include <stdio.h>
#include <math.h>

#define TARGET 1000000 // Maximum expected value
#define POW 5

int magic(int a, int p){
    int res = 0;
    while(a > 0){
        int dig = a % 10;
        res += pow(dig, p);
        a /= 10;
    }
    return res;
}

int main(){
    int res = 0;
    for(int i=2; i<=TARGET; i++){
        if(i == magic(i, POW)){
            printf("%d\n", i);
            res+=i;
        }
    }
    
    printf("If you can trust me, the number you are looking for is %d.\n", res);
    return 0;
}
