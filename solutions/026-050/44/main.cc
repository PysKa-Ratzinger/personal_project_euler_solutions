#include <stdio.h>
#include <chrono>

unsigned long pentagonal_number(unsigned long index){
    return ((index + 1) * (3 * (index + 1) - 1)) / 2;
}

bool is_pentagonal_number(unsigned long number){
    unsigned long min=0;
    unsigned long max=1;
    for(;pentagonal_number(max) < number; max*=2);
    unsigned long mid;
    unsigned long pent;
    while(min < max){
        mid = (max + min) / 2;
        pent = pentagonal_number(mid);
        if(pent < number){
            min = mid+1;
        }else if(pent > number){
            max = mid-1;
        }else{
            return true;
        }
    }
    return pentagonal_number(max) == number;
}

bool should_run(unsigned long index, unsigned long curr_min_diff){
    if(curr_min_diff == 0) return true;
    unsigned long min_diff = pentagonal_number(index) - pentagonal_number(index-1);
    return min_diff <= curr_min_diff;
}

int main(){
    unsigned long res = 0;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    unsigned long first, second, sum, diff;
    for(unsigned long i=1; should_run(i, res); i++){
        second = pentagonal_number(i);
        for(unsigned long j=i-1;; j--){
            first = pentagonal_number(j);
            sum = second + first;
            diff = second - first;
            if(is_pentagonal_number(sum) && is_pentagonal_number(diff)){
                if(res == 0 || diff < res){
                    res = diff;
                }
            }
            if(j == 0 || diff < res) break;
        }
    }
    
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    unsigned long duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("If you can trust me, the number you are looking for is %lu\n", res);
    printf("Execution time: %.2fs\n", ((double)duration)/1000000);
    return 0;
}
