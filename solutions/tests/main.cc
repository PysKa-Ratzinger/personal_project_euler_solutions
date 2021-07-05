#include <cppunit/ui/text/TestRunner.h>

#include "./graph/DijkstraTest.hpp"
#include "./graph/MazeGeneratorTest.hpp"
#include "./cache/CacheTest.hpp"

int main () {
	CppUnit::TextUi::TestRunner runner;

	runner.addTest( DijkstraTest::suite() );
	runner.addTest( CacheTest::suite() );
	runner.addTest( MazeGeneratorTest::suite() );

	runner.run();
	return 0;
}

