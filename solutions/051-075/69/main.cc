#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <sys/resource.h>

#include "../../utils/primes.hpp"
#include "../../utils/totient.hpp"

#define ONE_OVER_MILLION 1E-6

uint64_t magic() {
  double maxval = 0.0;
  uint64_t res = 0;

  for (unsigned i=2; i<=10000000; i++) {
    double value = (double)i/getTotient(i);
    if (value > maxval) {
      maxval = value;
      res = i;
    }
  }

  printf("Max value = %lf\n", maxval);

  return res;
}

int main() {
  // Calculate time taken by a request
  struct timespec requestStart, requestEnd;
  clock_gettime(CLOCK_REALTIME, &requestStart);
  uint64_t res = magic();
  clock_gettime(CLOCK_REALTIME, &requestEnd);

  printf("If you can trust me, the number you are "
      "looking for is %lu\n", res);
  double accum = (requestEnd.tv_sec - requestStart.tv_sec) * 1000
    + (requestEnd.tv_nsec - requestStart.tv_nsec)
    * ONE_OVER_MILLION;
  printf("Execution time: %.3lf ms\n", accum);
  return 0;
}

