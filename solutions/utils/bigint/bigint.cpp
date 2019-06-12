#include "bigint.h"

#include <stdint.h>

BigInt::BigInt() : _cells() {

}

BigInt::BigInt(uintmax_t number) : _cells() {
  _cells.push_back(number);
}

BigInt& BigInt::operator+(const BigInt & other){
  BigInt *result = new BigInt();
  result->_cells.at(0) += other._cells.at(0);
  return *result;
}
