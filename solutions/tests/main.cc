#include <cppunit/ui/text/TestRunner.h>

#include "./graph/DijkstraTest.hpp"

int main () {
	CppUnit::TextUi::TestRunner runner;

	runner.addTest( DijkstraTest::suite() );

	runner.run();
	return 0;
}

