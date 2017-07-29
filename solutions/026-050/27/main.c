#include <stdio.h>
#include <stdlib.h>

#define NUM_AUX_PRIMES 20000

int aux[NUM_AUX_PRIMES];
int aux_sz = 0;

int is_prime(int num);

int primitive_prime_incrementer(){
  int base = aux[aux_sz-1] + 1;
  while(!is_prime(base)) base++;
  aux[aux_sz++] = base;
  printf("New prime: %d\n", base);
  return base;
}

int is_prime(int num){
  if(num < 0){
    return 0;
  }
  int i=0;
  while(1){
    int temp;
    if(i<aux_sz){
      temp = aux[i];
      i++;
    }else{
      temp = primitive_prime_incrementer();
    }
    if(temp >= num / temp){
      return 1;
    }else if(num % temp == 0){
      return 0;
    }
  }
}

int recurr(int a, int b){
  int n=0;
  for(;;){
    int temp = n*n + a*n + b;
    if(!is_prime(temp)){
      return n-1;
    }else{
      n++;
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
        printf("New maximum found %d - %d (%d)\n", a, b, temp);
        max = temp;
        vals[0] = a;
        vals[1] = b;
        recurr(a, b);
      }
    }
  }

  int res = vals[0] * vals[1];
  printf("If you can trust me, the number you are looking for is %d (%d * %d (%d))\n",
      res, vals[0], vals[1], max);
  return 0;
}

