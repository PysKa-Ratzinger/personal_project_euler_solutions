#include <stdio.h>
#include <chrono>

#include "../../utils/figurate_numbers.hpp"

int main(){
    unsigned long res = 0;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    unsigned long values[3];
    unsigned long indexs[3]{285, 165, 144};
    unsigned long sides[3]{3, 5, 6};

    for(int i=0; i<3; i++){
        values[i] = polygonal_number(sides[i], indexs[i]);
    }

    while(values[0] != values[1] || values[1] != values[2]){
        int min_index = 0;
        for(int i=1; i<3; i++){
            if(values[i] < values[min_index]){
                min_index = i;
            }
        }
        indexs[min_index]++;
        values[min_index] = polygonal_number(sides[min_index], indexs[min_index]);
    }
    res = values[0];

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    unsigned long duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("If you can trust me, the number you are looking for is %lu\n", res);
    printf("Execution time: %.6fs\n", ((double)duration)/1000000);
    return 0;
}
