#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "../../utils/figurate_numbers.hpp"

#define ONE_OVER_THOUSAND 1E-3
#define ONE_OVER_MILLION 1E-6
#define NUM_NUMBERS 6
#define POL_NUMBER_BUFFER_SIZE 500

struct recurr_variables{
    unsigned long buffer[NUM_NUMBERS]{0};
    bool sides[NUM_NUMBERS]{false};
};

unsigned long pol_numbers[POL_NUMBER_BUFFER_SIZE];
unsigned long pol_numbers_size = 0;
unsigned long pol_numbers_start[NUM_NUMBERS+1][100];
struct recurr_variables var;

unsigned long recurr_magic(unsigned long sides, unsigned long depth){
    unsigned long prev_number, start, target;

    if(depth > 0){
        prev_number = var.buffer[depth-1];
        start = (prev_number % 100) * 100;
        if(depth == NUM_NUMBERS-1){
            start += var.buffer[0] / 100;
            target = start + 1;
        }else{
            target = start + 100;
        }
    }else{
        start = 100;
        target = 10000;
    }

    unsigned long hundreds = start / 100;
    unsigned long index = pol_numbers_start[sides-3][hundreds - 10];
    unsigned long target_index = pol_numbers_start[sides-3][hundreds - 9];
    if(target_index == 0) target_index = pol_numbers_start[sides-2][0];
    unsigned long number = pol_numbers[index];
    if(number < start){
        unsigned long min, max;
        min = index;
        max = target_index;
        while(min < max){
            unsigned long mid = (min + max) / 2;
            number = pol_numbers[mid];
            if(number < start){
                min = mid + 1;
            }else if(number > start){
                max = mid - 1;
            }else{
                min = max = mid;
            }
        }
        index = max;
        number = pol_numbers[index];
    }
    // while(number < start) number = pol_numbers[++index];

    while(number < target && index < target_index){
        if(number % 100 <= 10){
            number = pol_numbers[++index];
            continue;
        }

        if(depth == NUM_NUMBERS-1){
            return number;
        }else{
            var.buffer[depth] = number;
            var.sides[sides-3] = true;
            for(unsigned long n_sds = 3; n_sds < NUM_NUMBERS+3; n_sds++){
                if(var.sides[n_sds-3]) continue;
                unsigned long temp = recurr_magic(n_sds, depth+1);
                if(temp != 0){
                    return number + temp;
                }
            }
            var.sides[sides-3] = false;
        }

        number = pol_numbers[++index];
    }

    return 0;
}

unsigned long recurr_magic(unsigned long depth){
    unsigned long answer = 0;
    for(unsigned long sides = 3; sides < NUM_NUMBERS+3; sides++){
        answer = recurr_magic(sides, depth);
        if(answer != 0) break;
    }
    return answer;
}
unsigned long magic(){
    // Initialization of figurate numbers cache
    for(unsigned long sds = 3; sds < NUM_NUMBERS + 3; sds++){
        unsigned long i=0;
        unsigned long number = polygonal_number(sds, i);
        while(number < 1000){
            number = polygonal_number(sds, ++i);
        }
        unsigned long target = 1000;

        for(;number < 10000; i++){
            number = polygonal_number(sds, i);
            while(number > target){
                pol_numbers_start[sds-3][(target / 100) - 10] = pol_numbers_size;
                target += 100;
            }
            pol_numbers[pol_numbers_size++] = number;
        }
        pol_numbers_start[sds-3][(target / 100) - 10] = pol_numbers_size;
    }
    pol_numbers_start[NUM_NUMBERS][0] = pol_numbers_size;

    return recurr_magic(0);
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
