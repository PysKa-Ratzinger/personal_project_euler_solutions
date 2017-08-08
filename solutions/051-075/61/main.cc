#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "../../utils/figurate_numbers.hpp"

#define NUM_NUMBERS 6

struct recurr_variables{
    unsigned long buffer[NUM_NUMBERS]{0};
    unsigned long sides[NUM_NUMBERS]{0};
    long long indexes[NUM_NUMBERS]{0};
};

unsigned long recurr_magic(struct recurr_variables* var, unsigned long sides, unsigned long depth){
    unsigned long prev_number, start, target;

    if(depth > 0){
        prev_number = var->buffer[depth-1];
        start = (prev_number % 100) * 100;
        if(depth == NUM_NUMBERS-1){
            start += var->buffer[0] / 100;
            target = start + 1;
        }else{
            target = start + 100;
        }
    }else{
        start = 100;
        target = 10000;
    }

    long long index = 0;
    for(unsigned long number = start; number < target; number++){
        index = is_polygonal_number(number, sides);
        if(index != -1) break;
    }

    if(index == -1) return 0;
    unsigned long number = polygonal_number(sides, index);
    while(number < target){
        if(number % 100 <= 10){
            number = polygonal_number(sides, ++index);
            continue;
        }

        bool unique_index = true;
        for(unsigned i=0; i<depth; i++){
            if(var->indexes[i] == index){
                unique_index = false;
                break;
            }
        }

        if(unique_index){
            if(depth < NUM_NUMBERS-1){
                var->buffer[depth] = number;
                var->indexes[depth] = index;
                var->sides[depth] = sides;
                for(unsigned long n_sds = 3; n_sds < NUM_NUMBERS+3; n_sds++){
                    bool unique_side = true;
                    for(unsigned i=0; i<=depth; i++){
                        if(n_sds == var->sides[i]){
                            unique_side = false;
                        }
                    }
                    if(!unique_side) continue;

                    unsigned long temp = recurr_magic(var, n_sds, depth+1);

                    if(temp != 0){
                        return number + temp;
                    }
                }

            }else{
                return number;
            }
        }

        number = polygonal_number(sides, ++index);
    }

    return 0;
}

unsigned long recurr_magic(struct recurr_variables* var, unsigned long depth){
    unsigned long answer = 0;
    for(unsigned long sides = 3; sides < NUM_NUMBERS+3; sides++){
        answer = recurr_magic(var, sides, depth);
        if(answer != 0) break;
    }
    return answer;
}
unsigned long magic(){
    struct recurr_variables variables;
    return recurr_magic(&variables, 0);
}

int main(){
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    unsigned long res = magic();

    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    unsigned long duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("If you can trust me, the number you are "
            "looking for is %lu\n", res);
    printf("Execution time: %lums\n", duration/1000);
    return 0;
}
