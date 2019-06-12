#pragma once

#include <stdlib.h>

/**
 * @brief Iterates over all the permutations possible
 *
 * @param buf Buffer of elements
 * @param elem_size The size of each element
 * @param num_elems The number of elements in the buffer
 * @param cb Callback to process each permutation
 */
bool processPermutations(void* buf, size_t elem_size, size_t num_elems,
		bool (*cb)(void* buf, size_t num_elems, void* arg), void* arg);

