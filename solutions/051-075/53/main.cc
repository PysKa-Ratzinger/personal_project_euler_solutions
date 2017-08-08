#include <stdio.h>
#include <string.h>
#include <math.h>
#include <chrono>

#define MAX_NUMBER 100
#define LIMIT 1000000

unsigned long magic(unsigned long max_number){
    long array[max_number+1] = {1, 0};
    unsigned long arr_size = 1;
    unsigned long res = 0;
    while(arr_size <= max_number){
        for(unsigned long i=arr_size-1; i>0; i--){
            if(array[i-1] == -1 || array[i] == -1){
                array[i] = -1;
                res++;
            }else{
                array[i] = array[i-1] + array[i];
            }
            if(array[i] > LIMIT){
                array[i] = -1;
                res++;
            }
        }
        array[arr_size++] = 1;
    }
    return res;
}

int main(){
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    unsigned long res = magic(MAX_NUMBER);

    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    unsigned long duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("If you can trust me, the number you are "
            "looking for is %lu\n", res);
    printf("Execution time: %lums\n", duration/1000);
    return 0;
}
