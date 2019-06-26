#ifndef UTILS_RANGE_HPP_
#define UTILS_RANGE_HPP_

class Range {
public:
	Range(unsigned min, unsigned max) :
		m_min(min), m_max(max) {}

private:
	unsigned m_min;
	unsigned m_max;
};

#endif  // UTILS_RANGE_HPP_

