#include <stdio.h>

void permutate(char *result, int *vec, int *seq, int depth){
  for(int i=0; i<10; i++){
    if(vec[i] == 0){
      vec[i] = 1;
      if(depth == 1){
        *seq = *seq + 1;
      }else{
        permutate(result, vec, seq, depth-1);
      }
      if(*seq == 1000000){
        result[10 - depth] = i + '0';
        return;
      }
      vec[i] = 0;
    }
  }
}

int main(){
  char result[11];
  int vec[10];
  int seq = 0;

  for(int i=0; i<10; i++) vec[i] = 0;
  result[10] = '\0';
  permutate(result, vec, &seq, 10);

  printf("If you can trust me, the result you are looking for is %s\n", result);
  return 0;
}

