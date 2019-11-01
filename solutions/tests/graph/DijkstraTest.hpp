#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "graph/dijkstra.hpp"
#include "graph/node.hpp"

using namespace CppUnit;

class DijkstraTest : public TestCase {
public:
	static Test* suite();

	void simpleTest();
};

