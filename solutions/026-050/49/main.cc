#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <list>

#define VEC_MAX 100000
#define START_VALUE 1000
#define END_VALUE 10000

unsigned long primes[VEC_MAX];
unsigned long prime_sz = 0;

bool is_prime(unsigned long number);

unsigned long get_prime(unsigned long index){
    if(index >= VEC_MAX){
        printf("WARNING! Buffer Overflow imminent! Stopping execution...\n");
        exit(EXIT_FAILURE);
    }

    if(prime_sz == 0){
        primes[0] = 2;
        prime_sz = 1;
    }

    while(index >= prime_sz){
        unsigned long i=primes[prime_sz-1]+1;
        for(; !is_prime(i); i++);
        primes[prime_sz++] = i;
    }
    return primes[index];
}

bool is_prime(unsigned long number){
    if(number == 1) return true;
    for(unsigned int i=0; ; i++){
        unsigned long prime = get_prime(i);
        if(prime > number / prime) return true;
        if(number % prime == 0) return false;
    }
}

class Number{
private:
    unsigned long _value;
    std::list<unsigned char> _digits;
public:
    Number(unsigned long value);
    unsigned long getValue();
    bool compareDigits(Number& other);
    bool operator == (Number& other);
};

Number::Number(unsigned long value) : _value(value)
{
    while(value){
        _digits.push_back(value % 10);
        value /= 10;
    }
    _digits.sort();
}

unsigned long Number::getValue()
{
    return _value;
}

bool Number::compareDigits(Number& other)
{
    return _digits == other._digits;
}

bool Number::operator==(Number& other)
{
    return _value == other._value;
}

int main(){
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    
    std::list<Number> all_numbers;
    for(unsigned long i=START_VALUE; i<END_VALUE; i++){
        if(!is_prime(i)) continue;
        Number *temp = new Number(i);
        unsigned long num_permutations = 0;
        for(Number num : all_numbers){
            if(num.compareDigits(*temp)){
                num_permutations++;
            }
        }
        all_numbers.push_back(*temp);
    }
    
    for(Number num : all_numbers){
        for(Number num2 : all_numbers){
            if(num2.getValue() <= num.getValue()) continue;
            if(!(num.compareDigits(num2))) continue;
            unsigned long distance = num2.getValue() - num.getValue();
            unsigned long targetValue = num2.getValue() + distance;
            Number temp(targetValue);
            if(!num2.compareDigits(temp)) continue;
            for(Number num3 : all_numbers){
                if(num3.getValue() == targetValue){
                    unsigned long res = num.getValue() * 100000000 + num2.getValue() * 10000 + targetValue;
                    printf("Solution found: %lu\n", res);
                }
            }
        }
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    unsigned long duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("Execution time: %.6fs\n", ((double)duration)/1000000);
    return 0;
}
