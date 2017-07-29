#include <stdio.h>

int main(){
  double a = 1.0;
  double b = 1.0;
  double c = a + b;

  double limit = 10.0;
  int digits = 1;
  int index = 3;

  while(digits < 1000){
    a = b;
    b = c;
    c = a + b;
    if(c >= limit){
      a /= limit;
      b /= limit;
      c /= limit;
      digits++;
    }
    index++;
  }
  
  printf("If you can trust me, the number you are looking for is %d\n", index);
  return 0;
}

