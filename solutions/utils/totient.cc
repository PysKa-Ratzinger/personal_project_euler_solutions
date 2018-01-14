#include "primes.hpp"
#include "totient.hpp"

uint64_t getTotient(uint64_t number) {
  if (number == 0 || number == 1) return 1;
  uint64_t index = 0;
  uint64_t buffer[20];
  size_t buffer_size = 0;
  unsigned prime = getPrime(index);
  uint64_t res = number;

  while (prime*prime <= number) {
    if (number % prime == 0) {
      buffer[buffer_size++] = prime;
      while (number % prime == 0) number /= prime;
    }
    prime = getPrime(++index);
  }

  if (number > 1) {
    buffer[buffer_size++] = number;
  }

  for (size_t i=0; i<buffer_size; i++) {
    uint64_t factor = buffer[i];
    res = (res * (factor - 1)) / factor;
  }

  return res;
}

