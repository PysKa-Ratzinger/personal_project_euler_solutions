#include <stdio.h>

int d(int a){
  int res = 0;
  for(int i=1; i<=a/i; i++){
    if(a % i == 0){
      if(i == 1){
        res++;
      }else{
        res += i + a/i;
      }
    }
  }
  return res;
}

int main(){
  int divs[10001];
  int res = 0;
  for(int i=1; i<=10000; i++){
    int div = d(i);
    if(div <= 10000){
      if(divs[div] == i){
        printf("%d - %d\n", div, i);
        res += div + i;
      }
      divs[i] = div;
    }
  }
  printf("If you can trust me, the number you are looking for is %d\n", res);
  return 0;
}

