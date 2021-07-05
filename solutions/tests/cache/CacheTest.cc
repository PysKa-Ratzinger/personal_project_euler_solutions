#include "CacheTest.hpp"

#include <unistd.h>

Test*
CacheTest::suite() {
	TestSuite* res = new TestSuite("UtilsTest");
	res->addTest(new TestCaller<CacheTest>(
				"sample_test",
				&CacheTest::simpleTest));
	return res;
}

void
CacheTest::simpleTest() {
	LRUCache l(4, -1);

	std::vector<std::list<std::pair<int, int>>> expectedResult = {
		{
			{1, 1}
		},
		{
			{3, 3},
			{1, 1}
		},
		{
			{2, 2},
			{3, 3},
			{1, 1}
		},
		{
			{3, 3},
			{2, 2},
			{1, 1}
		},
		{
			{5, 5},
			{3, 3},
			{2, 2},
			{1, 1}
		},
		{
			{7, 7},
			{5, 5},
			{3, 3},
			{2, 2}
		},
		{
			{1, 1},
			{7, 7},
			{5, 5},
			{3, 3}
		},
		{
			{9, 9},
			{1, 1},
			{7, 7},
			{5, 5}
		}
	};

	int i = 0;
	for (int a : {1,3,2,3,5,7,1,9}) {
		l.set(a, a);

		CPPUNIT_ASSERT(expectedResult.at(i) == l.data);
		i++;
	}
}
