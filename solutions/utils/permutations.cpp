#include "permutations.hpp"

#include <string.h>
#include <stdlib.h>

bool processPermutationsImpl(char* buf, size_t elem_size, size_t num_elems,
		char* curr_elems, size_t curr_size,
		bool (*cb)(void* buf, size_t num_elems, void* arg), void* arg)
{
	if (num_elems == 0) {
		if (curr_size > 0) {
			return cb((void*)curr_elems, curr_size, arg);
		}
		return true;
	} else {
		if (!processPermutationsImpl(buf + elem_size, elem_size,
					num_elems - 1, curr_elems, curr_size,
					cb, arg)) {
			return false;
		}
		memcpy(curr_elems + (curr_size * elem_size), buf, elem_size);
		return processPermutationsImpl(buf + elem_size, elem_size,
				num_elems - 1, curr_elems, curr_size + 1, cb,
				arg);
	}
}

bool processPermutations(void* buf, size_t elem_size, size_t num_elems,
		bool (*cb)(void* buf, size_t num_elems, void* arg), void* arg)
{
	void* curr_elems = calloc(num_elems, elem_size);
	return processPermutationsImpl((char*) buf, elem_size, num_elems,
			(char*) curr_elems, 0, cb, arg);
}

