#include "bigint/bigint.h"

int main (int argc, char* argv[]) {
	BigInt a("9999999999999999999999999999999999999999999999");
	BigInt b("9999999999999999999999999999999999999999999999");

	printf("Number: %s\n", a.getString().c_str());
	printf("Number: %s\n", b.getString().c_str());

	a = a + b;
	printf("Number: %s\n", a.getString().c_str());

	return 0;
}

