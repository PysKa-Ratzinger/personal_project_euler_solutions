#include "bigint.h"

#include <stdint.h>
#include <stdexcept>
#include <string>
#include <algorithm>

BigInt::BigInt() : _cells() {}

BigInt::BigInt(std::string number) : _cells() {
	uintmax_t curr = 0;
	int mult = 1;
	for (auto it = number.rbegin(); it != number.rend(); it++) {
		curr += (*it - '0') * mult;
		mult *= 10;
		if (mult == _base) {
			_cells.push_back(curr);
			curr = 0;
			mult = 1;
		}
	}
	if (curr > 0) {
		_cells.push_back(curr);
	}
}

std::string BigInt::getString()
{
	std::string result = "";
	int digits = 0;
	uintmax_t base = _base;
	while ((base /= 10)) {
		digits++;
	}
	for (auto it = _cells.begin(); it != _cells.end(); it++) {
		uintmax_t num = *it;
		if (it == _cells.end() -1) {
			while (num) {
				int dig = num % 10;
				num /= 10;
				result += (char)(dig + '0');
			}
		} else {
			for (int i=0; i<digits; i++) {
				int dig = num % 10;
				num /= 10;
				result += (char)(dig + '0');
			}
		}
	}
	if (result.empty()) {
		return "0";
	} else {
		reverse(result.begin(), result.end());
		return result;
	}
}

BigInt& BigInt::operator+(const BigInt & other){
	uintmax_t carry = 0;
	auto it1 = _cells.begin();
	auto it2 = other._cells.begin();
	while (it1 != _cells.end() || it2 != other._cells.end()) {
		uintmax_t num1, num2, sum;
		num1 = (it1 != _cells.end()) ? *it1 : 0;
		num2 = (it2 != other._cells.end()) ? *it2 : 0;
		sum = num1 + num2 + carry;
		carry = (sum >= _base) ? sum / _base : 0;
		if (it1 != _cells.end()) {
			*it1 = sum;
			it1++;
		} else {
			_cells.push_back(sum);
			it1 = _cells.end();
		}

		if (it2 != other._cells.end()) {
			it2++;
		}
	}
	if (carry != 0) {
		_cells.push_back(carry);
	}
	return *this;
}
