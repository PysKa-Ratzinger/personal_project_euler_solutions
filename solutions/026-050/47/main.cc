#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <list>

#define VEC_MAX 100000
#define START_VALUE 10
#define FINAL_SIZE 4

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
    std::list<unsigned long> _prime_factors;
    std::list<unsigned long> _prime_cardinality;
public:
    Number(unsigned long value);
    unsigned long getValue();
    int distinctPrimeNumbers();
    bool operator == (Number& other);
};

Number::Number(unsigned long value) : _value(value)
{
    for(unsigned long i=0;; i++){
        unsigned long prime = get_prime(i);
        if(prime > value) break;
        unsigned long cardinality = 0;
        while(value % prime == 0){
            cardinality++;
            value /= prime;
        }
        if(cardinality){
            _prime_factors.push_back(prime);
            _prime_cardinality.push_back(cardinality);
        }
    }
}

unsigned long Number::getValue()
{
    return _value;
}

int Number::distinctPrimeNumbers()
{
    return _prime_factors.size();
}

bool Number::operator==(Number& other)
{
    return _prime_factors == other._prime_factors && _prime_cardinality == other._prime_cardinality;
}

int main(){
    unsigned long res = 0;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    
    std::list<Number> curr_numbers;
    
    for(unsigned long i=START_VALUE;; i++){
        Number *temp = new Number(i);
        if(temp->distinctPrimeNumbers() != 4){
            curr_numbers.clear();
            delete temp;
            continue;
        }
        std::list<Number>::iterator it = curr_numbers.begin();
        for(; it != curr_numbers.end(); it++){
            if(*it == *temp){
                curr_numbers.clear();
                break;
            }
        }
        curr_numbers.push_back(*temp);
        if(curr_numbers.size() == FINAL_SIZE) break;
    }
    res = curr_numbers.begin()->getValue();

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    unsigned long duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("If you can trust me, the number you are looking for is %lu\n", res);
    printf("Execution time: %.6fs\n", ((double)duration)/1000000);
    return 0;
}
