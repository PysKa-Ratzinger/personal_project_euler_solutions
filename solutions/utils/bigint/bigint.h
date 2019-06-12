#ifndef BIGINT_
#define BIGINT_

#include <stdint.h>
#include <vector>

class BigInt {
private:
  std::vector<uintmax_t> _cells;
public:
  BigInt();
  BigInt(uintmax_t);
  BigInt& operator+ (const BigInt & other);
};

#endif  // BIGINT_
