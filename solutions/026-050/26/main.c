#include <stdio.h>

int recurr(int num){
  int top = 1;
  int vars[10000];
  int v_size = 0;

  vars[v_size++] = top;
  while(top != 0){
    top %= num;
    top *= 10;
    vars[v_size++] = top;
    for(int i=v_size-2; i>=0; i--){
      if(vars[i] == top){
        return v_size - i - 1;
      }
    }
  }

  return 0;
}

int main(){
  int max = 0;
  int index = 0;
  for(int i=2; i<1000; i++){
    int temp = recurr(i);
    if(temp > max){
      max = temp;
      index = i;
    }
  }
  printf("If you can trust me, the number you are looking for is %d(%d)\n", index, max);
  return 0;
}

