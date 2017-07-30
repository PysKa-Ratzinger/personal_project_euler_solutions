#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>

#define NUM_DIGITS 8
#define NUM_PRIMES 8
#define PRIME_BUFFER 2048

unsigned primes[PRIME_BUFFER] = {2, 3, 0};
unsigned primes_sz = 2;

bool isPrime(unsigned long number);

unsigned getPrime(unsigned index){
    if(index >= PRIME_BUFFER){
        fprintf(stderr, "Buffer overflow imminent. Stopping execution.\n");
        exit(EXIT_FAILURE);
    }
    while(index >= primes_sz){
        unsigned number = primes[primes_sz-1]+2;
        while(!isPrime(number)) number += 2;
        primes[primes_sz++] = number;
    }
    return primes[index];
}

bool isPrime(unsigned long number){
    unsigned index = 0;
    unsigned prime = getPrime(index);
    while(prime <= number/prime){
        if(number % prime == 0) return false;
        index++;
        prime = getPrime(index);
    }
    return true;
}

unsigned numDigits(unsigned long number){
    unsigned res = 0;
    while(number){
        res++;
        number /= 10;
    }
    return res;
}

unsigned long reverse(unsigned long numDigits, unsigned long number){
    unsigned numZeros = 0;
    while(number && number % 10 == 0){
        numZeros++;
        number /= 10;
    }
    unsigned digits = 0;
    unsigned long res = 0;
    while(number){
        res *= 10;
        res += number % 10;
        number /= 10;
        digits++;
    }
    return res * powl(10, numDigits - numZeros - digits);
}

unsigned long mask(unsigned long numDigits, unsigned long number){
    unsigned numNotZeros = 0;
    while(number && number % 10 != 0){
        numNotZeros++;
        number /= 10;
    }
    unsigned digits = 0;
    unsigned long res = 0;
    while(number){
        res *= 10;
        if(number % 10 == 0) res++;
        number /= 10;
        digits++;
    }
    while(numNotZeros + digits < numDigits){
        digits++;
        res *= 10;
        res++;
    }
    return reverse(numDigits, res);
}

unsigned long magic2(unsigned long number, unsigned long msk,
                    bool debug){
    unsigned long numPrimes = 10;
    unsigned long firstPrime = 0;
    unsigned long curr = number;
    for(int i=0; i<10; i++, curr += msk){
        if(!isPrime(curr)){
            numPrimes--;
            if(numPrimes < 8){
                firstPrime = 0;
                break;
            }
        }else{
            if(debug)
                printf("    %lu\n", curr);
            if(firstPrime == 0)
                firstPrime = curr;
        }
    }
    if(numPrimes != 8){
        return 0;
    }else{
        return firstPrime;
    }
}

unsigned long modMask(unsigned long mask, unsigned long numOnes,
                        unsigned long binMod){
    int index = 0;
    int arr[20];
    while(mask){
        arr[index++] = mask % 10;
        mask /= 10;
    }
    int currIndex = 0;
    for(unsigned i=0; i<numOnes; i++){
        int ch = binMod & 0x1;
        binMod >>= 1;
        while(!arr[currIndex]) currIndex++;
        if(ch){
            arr[currIndex] = arr[currIndex] == 0 ? 1 : 0;
        }
        currIndex++;
    }
    unsigned long res = 0;
    for(int i=0; i<index; i++){
        res *= 10;
        res += arr[index - i - 1];
    }
    return res;
}

unsigned long magic(unsigned long numDigits, unsigned long number,
                    bool debug){
    unsigned long msk = mask(numDigits, number);
    if(msk == 0) return 0;

    unsigned long tmp = msk;
    unsigned long numOnes = 0;
    while(tmp){
        int digit = tmp % 10;
        tmp /= 10;
        if(digit == 1){
            numOnes++;
        }
    }

    if(debug){
        printf("Testing number %lu with %lu digits.\n", number, numDigits);
        printf("List of primes:\n");
    }

    unsigned long res = 0;
    for(unsigned k=0; k<(unsigned)(1<<(numOnes-1))-1; k++){
        unsigned long tmpMask = modMask(msk, numOnes, k);
        if(debug){
            printf("Trying mask %08lu\n", tmpMask);
        }
        res = magic2(number, tmpMask, false);
        if(res){
            if(debug){
                magic2(number, tmpMask, true);
                printf("Mask calculated to be %lu\n", tmpMask);
            }
            break;
        }
    }
    return res;
}

int main(){
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    unsigned long res = 0;
    unsigned long numDigits = 0;

    for(int i=2; i<=NUM_DIGITS; i++){
        //  Apparently, project Euler does not like
        //the number 000109 with mask 111000
        for(int j=powl(10, i-2)+1; j<powl(10, i); j+=2){
            if(j % 5 == 0) continue;
            if((res = magic(i, j, false)) != 0){
                magic(i, j, false);
                numDigits = (unsigned)i;
                break;
            }
        }
        if(res != 0) break;
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

