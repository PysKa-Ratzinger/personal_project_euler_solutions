#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 30000

int perfect_score(int n){
  int res = 1;
  for(int i=2; i<=n/i; i++){
    if(n % i == 0){
      res += i;
      if(i*i != n){
        res += n/i;
      }
    }
  }
  if(res < n){
    return -1;
  }else if(res == n){
    return 0;
  }else{
    return 1;
  }
}

int main(){
  int arr[ARR_SIZE];
  int arr_sz = 0;

  for(int i=2; i<ARR_SIZE; i++)
    if(perfect_score(i) > 0)
      arr[arr_sz++] = i;

  unsigned long long res = 0;
  for(int i=1; i<24; i++) res += i;
  for(int i=24; i<ARR_SIZE; i++){
    int min = 0;
    int max = arr_sz - 1;
    int canBeSum = 0;
    while(min <= max){
      int temp = arr[min] + arr[max];
      if(temp > i){
        max--;
      }else if(temp < i){
        min++;
      }else{
        canBeSum = 1;
        break;
      }
    }
    if(!canBeSum){
      res += i;
    }
  }

  printf("If you can trust me, the number you are looking for is %llu\n", res);
}

