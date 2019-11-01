#include "DijkstraTest.hpp"

template <class T>
class BasicGraph : public graph::Graph<T> {
public:
	~BasicGraph() = default;

	void addNode(T node) {
		m_nodes.insert(node);
	}

	void addEdge(T a, T b, int dist) {
		auto it = m_edges.find(a);
		if (it == m_edges.end()) {
			auto r = m_edges.insert({a, std::map<T, int>()});
			if (r.second) {
				it = r.first;
			} else {
				throw std::runtime_error("What...");
			}
		}

		auto it2 = it->second.find(b);
		if (it2 == it->second.end()) {
			it->second.insert({b, dist});
		} else {
			it2->second = dist;
		}
	}

	bool edgeExists(T a, T b) {
		auto it = m_edges.find(a);
		if (it != m_edges.end()) {
			auto it2 = it->second.find(b);
			if (it2 != it->second.end()) {
				return true;
			}
		}

		return false;
	}

	std::list<std::pair<T, int>> getEdges(T node) const override
	{
		std::list<std::pair<T, int>> res;
		auto it = m_edges.find(node);
		if (it == m_edges.end()) {
			return res;
		}

		for (auto& p : it->second) {
			res.push_back(p);
		}
		return res;
	}

private:
	std::set<T> m_nodes;
	std::map<T, std::map<T, int>> m_edges;
};

Test*
DijkstraTest::suite() {
	TestSuite* res = new TestSuite("UtilsTest");
	res->addTest(new TestCaller<DijkstraTest>(
				"sample_test",
				&DijkstraTest::simpleTest));
	return res;
}

void
DijkstraTest::simpleTest() {
	BasicGraph<std::pair<int, int>> g;

	for (int x=0; x<4; x++) {
		for (int y=0; y<4; y++) {
			g.addNode({x, y});
		}
	}

	srand(time(nullptr));
	for (int x=0; x<3; x++) {
		for (int y=0; y<3; y++) {
			if (rand() % 2 == 0) {
				g.addEdge({x, y}, {x, y+1}, 1);
			} else {
				g.addEdge({x, y}, {x+1, y}, 1);
			}
		}
		g.addEdge({x, 3}, {x+1, 3}, 1);
	}
	for (int y=0; y<3; y++) {
		g.addEdge({3, y}, {3, y+1}, 1);
	}

	auto res = graph::DijkstraSolver::solve(g, {0, 0}, {3, 3});

	auto it = res.begin();
	auto prev = *it;
	it++;

	std::cout << "Path: ";
	std::cout << prev.first << ", " << prev.second;
	while (it != res.end()) {
		auto curr = *it;
		std::cout << " -> " << curr.first << ", " << curr.second;
		CPPUNIT_ASSERT(g.edgeExists(prev, curr));
		prev = curr;
		it++;
	}
	std::cout << std::endl;
}

