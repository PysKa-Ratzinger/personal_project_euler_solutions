#include <stdio.h>

unsigned long res = 0;
bool digits[10];
int rdigits[10];

int divs[7]{2, 3, 5, 7, 11, 13, 17};
void magic(int prev, int depth){
    if(depth == 10){
        unsigned long temp = 0;
        for(int i=0; i<10; i++){
            temp *= 10;
            temp += rdigits[i];
        }
        res += temp;
        return;
    }
    for(int i=0; i<10; i++){
        if(digits[i]) continue;
        int temp = (prev * 10 + i) % 1000;
        if(depth >= 3 && temp % divs[depth-3] != 0) continue;
        digits[i] = true;
        rdigits[depth] = i;
        magic(temp, depth+1);
        digits[i] = false;
    }
}

int main(){
    magic(0, 0);
    
    printf("If you can trust me, the number you are looking for is %lu\n", res);
    return 0;
}
