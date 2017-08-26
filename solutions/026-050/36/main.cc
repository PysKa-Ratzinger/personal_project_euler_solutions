#include <stdio.h>

#define MAX_NUM 1000000

bool is_palyndrome(int num, int base){
    int rev = 0;
    int dup = num;
    while(dup > 0){
        rev *= base;
        rev += dup % base;
        dup /= base;
    }
    return rev == num;
}

bool magic(int i){
    return is_palyndrome(i, 10) && is_palyndrome(i, 2);
}

int main(){
    int res = 0;
    
    for(int i=1; i<MAX_NUM; i++){
        if(magic(i)){
            res += i;
        }
    }
    
    printf("If you can trust me, the number you are looking for is %d.\n", res);
    return 0;
}
