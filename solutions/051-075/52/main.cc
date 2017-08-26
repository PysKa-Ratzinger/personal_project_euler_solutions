#include <stdio.h>
#include <string.h>
#include <math.h>
#include <chrono>

int numDigits(unsigned long number){
    int res = 0;
    while(number){
        number /= 10;
        res++;
    }
    return res;
}

void fillDigits(unsigned long number, unsigned char array[10]){
    memset(array, 0, 10);
    while(number){
        array[number % 10]++;
        number /= 10;
    }
}

int main(){
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();
    unsigned long res = 0;

    unsigned long curr = 1;
    int numDigitsCurr = numDigits(curr);
    unsigned char currDigits[10];
    bool foundSolution = false;
    while(true){
        fillDigits(curr, currDigits);
        if(numDigits(curr*6) > numDigitsCurr){
            curr = powl(10, numDigitsCurr);
            numDigitsCurr++;
        }else{
            for(int i=0; i<5; i++){
                unsigned long multiple = curr * (i+2);
                unsigned char mulDigits[10];
                fillDigits(multiple, mulDigits);
                foundSolution = true;
                if(memcmp(currDigits, mulDigits, 10) != 0){
                    foundSolution = false;
                    break;
                }
            }
            if(!foundSolution){
                curr++;
            }else{
                res = curr;
                break;
            }
        }
    }

    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    unsigned long duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("If you can trust me, the number you are "
            "looking for is %lu\n", res);
    printf("Execution time: %lums\n", duration/1000);
    return 0;
}
