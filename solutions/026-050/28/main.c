#include <stdio.h>

#define TARGET 1001

int main(){
  int size = 1;
  int step = 2;
  int curr = 1;
  int res = 1;

  while(size != TARGET){
    for(int i=0; i<4; i++){
      curr += step;
      res += curr;
    }
    size += 2;
    step += 2;
  }

  printf("If you can trust me, the number you are looking for is %d\n", res);
  return 0;
}

