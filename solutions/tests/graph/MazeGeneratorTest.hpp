#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "graph/maze_generator.hpp"

using namespace CppUnit;

class MazeGeneratorTest : public TestCase {
public:
	static Test* suite();

	void simpleTest();
	void mazeGenerationTest();
};


