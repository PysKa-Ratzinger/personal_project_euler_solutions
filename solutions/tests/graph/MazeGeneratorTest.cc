#include "MazeGeneratorTest.hpp"

Test*
MazeGeneratorTest::suite()
{
	TestSuite* res = new TestSuite("MazeGeneratorTest");
	res->addTest(new TestCaller<MazeGeneratorTest>(
				"simple_test",
				&MazeGeneratorTest::simpleTest));
	res->addTest(new TestCaller<MazeGeneratorTest>(
				"maze_generation_test",
				&MazeGeneratorTest::mazeGenerationTest));
	return res;
}

void
MazeGeneratorTest::simpleTest()
{
	graph::Maze2D m(3, 3);
	m.ConnectTiles(0, 0, 0, 1);
	m.ConnectTiles(1, 1, 0, 1);

	std::list<std::pair<std::pair<int, int>, int>> expectedResult = {
		{{0,0}, 1},
		{{1,1}, 1}
	};

	auto result = m.getEdges(std::make_pair(0, 1));
	CPPUNIT_ASSERT(result == expectedResult);
}

void
MazeGeneratorTest::mazeGenerationTest()
{
	auto m = graph::MazeGenerator::generateMaze(20, 10);
	std::cout << std::endl << m;
}

