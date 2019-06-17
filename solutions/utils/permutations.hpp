#pragma once

#include <stdlib.h>
#include <vector>
#include <algorithm>

template <typename T, typename R>
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

template <typename T, typename R>
bool processCombinationsImpl(typename std::map<T, unsigned>::iterator it1,
		typename std::map<T, unsigned>::iterator it2,
		std::vector<T>& curr_elems,
		bool (&cb)(std::vector<T>& buf, R& arg), R& arg)
{
	if (it1 == it2) {
		if (curr_elems.size() > 0) {
			return cb(curr_elems, arg);
		}
		return true;
	} else {
		std::pair<T, unsigned> curr = *it1;
		it1++;
		if (!processCombinationsImpl(it1, it2, curr_elems, cb, arg)) {
			return false;
		}
		bool res = true;
		int i;
		for (i=0; i<curr.second; i++) {
			curr_elems.push_back(curr.first);
			if (!processCombinationsImpl(it1, it2, curr_elems, cb,
						arg)) {
				res = false;
				break;
			}
		}
		while (i) {
			curr_elems.pop_back();
			i--;
		}
		return res;
	}
}

template <typename T, typename R>
bool processPermutations(std::vector<T>& buf,
		bool (&cb)(std::vector<T>& buf, R& arg), R& arg)
{
	std::vector<T> curr_elems;
	return processPermutationsImpl(buf, 0, curr_elems, cb, arg);
}

template <typename T, typename R>
bool processCombinations(std::vector<T>& buf,
		bool (&cb)(std::vector<T>& buf, R& arg), R& arg)
{
	std::vector<T> curr_elems;
	std::vector<T> r_buf(buf.begin(), buf.end());
	std::sort(buf.begin(), buf.end());
	std::map<T, unsigned> reduced_buf;
	for (auto it = buf.begin(); it != buf.end(); it++) {
		auto it2 = reduced_buf.find(*it);
		if (it2 == reduced_buf.end()) {
			reduced_buf.insert(std::pair<T, unsigned>(*it, 1));
		} else {
			it2->second++;
		}
	}

	return processCombinationsImpl(reduced_buf.begin(), reduced_buf.end(),
			curr_elems, cb, arg);
}

template <typename T>
std::vector<std::vector<T>> getPermutations(std::vector<T>& buf)
{
	std::vector<std::vector<T>> res;
	processPermutations(buf, [](std::vector<T>& buf,
				std::vector<std::vector<T>>& all) -> bool {
			all.push_back(buf);
			return true;
			}, res);
	return res;
}

