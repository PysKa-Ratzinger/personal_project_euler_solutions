#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "number.h"
#include "../../utils/bst.hpp"

#define ONE_OVER_MILLION 1E-6
#define TARGET_REPS 5

unsigned long magic(){
    BST<Number> bst;

    bool running = true;

    unsigned long long upper_limit = 10;
    unsigned long long curr = 3;
    unsigned long digits = 1;

    Number *result = NULL;

    while(running){
        curr++;
        unsigned long long square = curr * curr * curr;
        if(square > upper_limit){
            digits++;
            upper_limit *= 10;
            bst.clear();
        }

        Number *curr_number = new Number(square);
        Number *temp = bst.contains(*curr_number);
        if(temp){
            temp->incrementRep();
            delete curr_number;
            if(temp->getReps() == TARGET_REPS){
                running = false;
                result = temp;
            }
        }else{
            bst.insert(*curr_number);
        }
    }

    return result->getNum();
}

int main(){
    // Calculate time taken by a request
    struct timespec requestStart, requestEnd;
    clock_gettime(CLOCK_REALTIME, &requestStart);
    unsigned long res = magic();
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    printf("If you can trust me, the number you are "
            "looking for is %lu\n", res);
    double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
      + ( requestEnd.tv_nsec - requestStart.tv_nsec )
      * ONE_OVER_MILLION;
    printf("Execution time: %.3lf ms\n", accum);
    return 0;
}
