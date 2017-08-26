#include <stdio.h>

#define MAX_NUM 1000

int sqrt(int number){
    for(int i=2; i<=number/i; i++){
        if(number % i == 0 && i == number / i)
            return i;
    }
    return -1;
}

int main(){
    int res = 0;
    int nums[MAX_NUM+1];
    
    for(int i=0; i<MAX_NUM+1; i++){
        nums[i] = 0;
    }
    
    for(int a=1; a<MAX_NUM; a++){
        for(int b=a; b+a < MAX_NUM; b++){
            int c = sqrt(a*a + b*b);
            if(c == -1)
                continue;

            int P = a + b + c;
            if(P > MAX_NUM)
                break;
            
            nums[P]++;
        }
    }
    
    for(int i=0; i<MAX_NUM+1; i++){
        if(nums[i] > nums[res]){
            res = i;
        }
    }

    printf("If you can trust me, the number you are looking for is %d\n", res);
    return 0;
}
