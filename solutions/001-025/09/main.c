#include <stdio.h>
#include <math.h>

#define TARGET 1000

int main(){
    unsigned long long res = -1;

    for(unsigned a=1; a<TARGET/2; a++){
        for(unsigned b=a+1; b<TARGET/2; b++){
            unsigned c = sqrt((double)a*a + (double)b*b);
            if(c*c == a*a + b*b && a+b+c == TARGET){
                res = a*b*c;
                goto end;
            }
        }
    }
    end:

    printf("If you can trust me, the number you "
            "are looking for is %llu\n", res);
    return 0;
}

