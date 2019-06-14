#pragma once

#include <stdlib.h>
#include <vector>

template<typename T, typename R>
bool processPermutationsImpl(std::vector<T>& buf, size_t idx,
		std::vector<T>& curr, bool (&cb)(std::vector<T>& buf, R& arg),
		R& arg)
{
	if (idx >= buf.size()) {
		if (curr.size() > 0) {
			return cb(curr, arg);
		}
		return true;
	} else {
		if (!processPermutationsImpl(buf, idx + 1, curr, cb, arg)) {
			return false;
		}
		curr.push_back(buf.at(idx));
		bool result = processPermutationsImpl(buf, idx + 1, curr, cb,
				arg);
		curr.pop_back();
		return result;
	}
}

template<typename T, typename R>
bool processPermutations(std::vector<T>& buf,
		bool (&cb)(std::vector<T>& buf, R& arg), R& arg)
{
	std::vector<T> curr_elems;
	return processPermutationsImpl(buf, 0, curr_elems, cb, arg);
}

