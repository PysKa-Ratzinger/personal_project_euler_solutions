#include <stdio.h>

int exists(int *arr, int size, int value) {
  while (size > 0) {
    if (*arr == value) return 1;
    arr++;
    size--;
  }
  return 0;
}

void printCode(int *arr) {
  int temp[10];
  int min_index = 0;
  for (int i=2; i<10; i+=2) {
    if (arr[i] < arr[min_index]) {
      min_index = i;
    }
  }
  for (int i=0; i<10; i++) {
    temp[i] = arr[(i+min_index)%10];
  }
  for (int i=0; i<10; i+=2) {
    printf("%d", temp[i]);
    printf("%d", temp[(i+1)%10]);
    printf("%d", temp[(i+3)%10]);
  }
  printf("\n");
}

void showSolution10(int *arr) {
  printf("      %2d\n", arr[2]);
  printf("        \\\n");
  printf("       _%2d  %2d\n", arr[3], arr[4]);
  printf("   _%2d    \\ /\n", arr[1]);
  printf("%2d   |    %2d\n", arr[0], arr[5]);
  printf("    %2d _  /\n", arr[9]);
  printf("     |  %2d _\n", arr[7]);
  printf("    %2d      %2d\n", arr[8], arr[6]);
  printf("\n");

  printCode(arr);
}

 /*
  *       2              a
  *        \              \
  *       _ 3   4        _ b   d
  *   _ 1    \ /     _ X    \ /
  * 0   |     5    X   |     c
  *     9 _  /         g _  /
  *     |   7 _        |   e _
  *     8       6      h       f
  */
int main() {
  int gon[10];
  gon[0] = 10;
  for (int a=9; a>0; a--) {
    gon[2] = a;
    for (int b=9; b>0; b--) {
      if (b == a) continue;
      gon[3] = b;
      for (int c=9; c>0; c--) {
        if (exists(gon+2, 2, c)) continue;
        gon[5] = c;
        int sum = a + b + c;
        gon[1] = sum - 10 - b;
        if (gon[1] < 1 || gon[1] > 9) continue;
        if (gon[1] == c) continue;
        if (exists(gon+2, 2, gon[1])) continue;
        for (int d=9; d>0; d--) {
          if (d == c) continue;
          if (exists(gon+1, 3, d)) continue;
          gon[4] = d;
          int e = sum - d - c;
          if (e < 1 || e > 9) continue;
          if (exists(gon+1, 5, e)) continue;
          gon[7] = e;
          for (int f=9; f>0; f--) {
            if (f == e) continue;
            if (exists(gon+1, 5, f)) continue;
            gon[6] = f;
            int g = sum - e - f;
            if (g < 1 || g > 9) continue;
            if (exists(gon+1, 7, g)) continue;
            gon[9] = g;
            int h = sum - gon[1] - g;
            if (h < 1 || h > 9) continue;
            if (exists(gon+1, 7, h)) continue;
            if (h == g) continue;
            gon[8] = h;

            showSolution10(gon);
          }
        }
      }
    }
  }

  printf("Given all these codes, you choose which one you like best.\n");

  return 0;
}

