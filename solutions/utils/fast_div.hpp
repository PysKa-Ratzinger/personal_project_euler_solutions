#pragma once

#include <gmpxx.h>

#include <functional>
#include <tuple>
#include <exception>

class DivisibleOperation {
public:
	DivisibleOperation(long unsigned bits,
			bool op1, long unsigned shft,
			bool op2, mpz_class mult1,
			mpz_class mult2) :
		_m((mpz_class(1) << bits) - 1), _op1(op1), _shft(shft),
		_op2(op2), _mult(mult1), _mult2(mult2) {}

	bool div(mpz_class num) const {
		if (_op1 && ((num << _shft) & _m) != 0) {
				return false;
		}
		if (_op2 && ((num * _mult) & _m) > _mult2) {
				return false;
		}
		return true;
	}

private:
	mpz_class _m;
	bool _op1;
	long unsigned _shft;
	bool _op2;
	mpz_class _mult;
	mpz_class _mult2;
};

std::tuple<mpz_class, mpz_class, mpz_class>
egcd(mpz_class a, mpz_class b)
{
	if (a == 0)
		return std::make_tuple(b, 0, 1);

	mpz_class g, y, x;
	std::tie(g, y, x) = egcd(b % a, a);
	return std::make_tuple(g, x - (b / a) * y, y);
}

DivisibleOperation
getFastDivOp(mpz_class d, long unsigned bits)
{
	mpz_class m = mpz_class(1) << bits;

	unsigned long j = 0;
	while (d % 2 == 0) {
		d >>= 1;
		j++;
	}

	mpz_class a1, a2, a3;
	std::tie(a1, a2, a3) = egcd(d, m);

	DivisibleOperation res(bits, j > 0, bits - j, d > 1, a2 % m, m / d);
	return res;
}

