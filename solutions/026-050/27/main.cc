#include <stdio.h>
#include <stdlib.h>
#include "../../utils/primes.hpp"

#define NUM_AUX_PRIMES 20000

int aux[NUM_AUX_PRIMES];
int aux_sz = 0;

int primitive_prime_incrementer(){
  int base = aux[aux_sz-1] + 1;
  while(base <= 1 || !isPrime(base)) base++;
  aux[aux_sz++] = base;
  printf("New prime: %d\n", base);
  return base;
}

int recurr(int a, int b){
  int n=0;
  for(;;){
    int temp = n*n + a*n + b;
    if(temp == 1 || (temp > 0 && isPrime(temp))){
      n++;
    }else{
      return n-1;
    }
  }
}

int main(){
  int max = 0;
  int vals[2] = {0, 0};

  aux[0] = 2;
  aux_sz = 1;

  for(int a=-999; a<1000; a++){
    for(int b=-1000; b<=1000; b++){
      int temp = recurr(a, b);
      if(temp > max){
        // printf("New maximum found %d - %d (%d)\n", a, b, temp);
        max = temp;
        vals[0] = a;
        vals[1] = b;
        recurr(a, b);
      }
    }
  }

  int res = vals[0] * vals[1];
  printf("If you can trust me, the number you are looking for is %d\n", res);
  return 0;
}
