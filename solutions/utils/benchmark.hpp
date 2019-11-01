#pragma once

#include <stdlib.h>
#include <stdint.h>

class Benchmark {
public:
	Benchmark(void (*func)());
	~Benchmark();

	double run();
	double run(uint64_t times);

private:
	void startTimer();
	void stopTimer();

	void (*_func)();

	struct timespec _start;
	struct timespec _end;
};

