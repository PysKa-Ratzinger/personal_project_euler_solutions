#pragma once

#include <stdint.h>
#include <vector>
#include <string>

class BigInt {
	private:
		std::vector<uintmax_t> _cells;
		uintmax_t _base = 10;

	public:
		BigInt();
		BigInt(std::string number);
		BigInt& operator+ (const BigInt & other);

		std::string getString();
};

