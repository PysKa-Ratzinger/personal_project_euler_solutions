#include "benchmark.hpp"

Benchmark::Benchmark(void (*func)()) : _func(func) {}

Benchmark::~Benchmark() {}

void
Benchmark::startTimer()
{
}

double
Benchmark::run()
{
	return 0.0;
}

