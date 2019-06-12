#include "figurate_numbers.hpp"

unsigned long polygonal_number(unsigned long sides, unsigned long index){
    if(sides <= 2) return 1;
    return ((sides - 2) * index * (index + 1)) / 2 + index + 1;
}

long long is_polygonal_number(unsigned long number, unsigned long sides){
    long long min = 0;
    long long max = 1;
    while(polygonal_number(sides, max) < number){
        min = max + 1;
        max = min * 2;
    }

    while(min < max){
        long long mid = (min + max) / 2;
        unsigned long temp = polygonal_number(sides, mid);
        if(temp > number){
            max = mid - 1;
        }else if(temp < number){
            min = mid + 1;
        }else{
            return mid;
        }
    }

    if(polygonal_number(sides, min) == number) return min;
    if(polygonal_number(sides, max) == number) return max;
    return -1;
}
