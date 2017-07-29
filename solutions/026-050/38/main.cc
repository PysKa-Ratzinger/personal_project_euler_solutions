#include <stdio.h>
#include <unordered_set>

#define MAX_PROPERTY 10000

int magic(unsigned long number){
    std::unordered_set<unsigned long> res;
    int numbers = 0;
    for(int i=1; i<10; i++){
        unsigned long temp = number * i;
        while(temp  > 0){
            int dig = temp % 10;
            temp /= 10;
            if(dig == 0)
                return 0;
            res.insert(dig);
            numbers++;
            if(numbers == 9){
                if(res.size() == 9){
                    return i;
                }else{
                    return 0;
                }
            }
        }
    }
    return 0;
}

int main(){
    unsigned long res = 0;

    int temp = 0;
    for(unsigned long i=9; i<MAX_PROPERTY; i++){
        if(magic(i) > 0){
            temp = magic(i);
            res = i;
        }
    }
    
    printf("If you can trust me, the number you are looking for is ");
    for(int i=1; i<=temp; i++){
        printf("%lu", res*i);
    }
    printf("\n");
    return 0;
}
