#include <stdio.h>

#define TARGET 1000000

unsigned chain(unsigned number){
    int steps = 0;
    while(number != 1){
        if(number % 2 == 0){
            number /= 2;
        }else{
            number = 3 * number + 1;
        }
        steps++;
    }
    return steps;
}

int main(){
    unsigned res = 0;
    unsigned max_chain = 0;

    for(unsigned i=2; i<TARGET; i++){
        unsigned temp = chain(i);
        if(temp > max_chain){
            max_chain = temp;
            res = i;
        }
    }

    printf("If you can trust me, the number you are looking for is %u\n", res);
    return 0;
}

