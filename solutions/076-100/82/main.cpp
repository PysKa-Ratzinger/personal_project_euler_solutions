#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "graph/dijkstra.hpp"
#include "graph/node.hpp"

class EulerGraph : public graph::Graph<std::pair<int, int>> {
public:
	EulerGraph(int width, int height) :
		m_width(width),
		m_height(height),
		m_nodes(width * height)
	{

	}

	~EulerGraph() = default;

	int getWidth() {
		return m_width;
	}

	int getHeight() {
		return m_height;
	}

	void setWeight(int x, int y, int weight) {
		m_nodes.at(y * m_height + x) = weight;
	}

	int at(int x, int y) const {
		return m_nodes.at(y * m_height + x);
	}

	void print(std::set<std::pair<int, int>> visited = std::set<std::pair<int, int>>()) {
		for (int x=0; x<m_width; x++) {
			for (int y=0; y<m_height; y++) {
				auto it = visited.find({x, y});
				bool v = (it != visited.end());

				if (y != 0) {
					std::cout << " ";
				}
				std::cout << (v ? "#" : " ");
				std::cout << std::setw(4) << at(x, y);
				std::cout << (v ? "#" : " ");
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::list<std::pair<std::pair<int, int>, int>>
		getEdges(std::pair<int, int> node) const override
	{
		int x = node.first;
		int y = node.second;

		std::list<std::pair<std::pair<int, int>, int>> res;
		// Starting Node
		if (x == -1 && y == -1) {
			for (int i=0; i<m_height; i++) {
				res.push_back({{i, 0}, at(i, 0)});
			}
		} else {
			if (x > 0) {
				res.push_back({{x-1, y}, at(x-1, y)});
			}

			//up
			if (y > 0) {
				res.push_back({{x, y-1}, at(x, y-1)});
			}

			//right
			if (x < m_width - 1) {
				res.push_back({{x+1, y}, at(x+1, y)});
			}

			//down
			if (y < m_height - 1) {
				res.push_back({{x, y+1}, at(x, y+1)});
			}
		}
		return res;
	}

private:
	int m_width;
	int m_height;
	std::vector<int> m_nodes;
};

EulerGraph
importGraphFromFile(std::string fileName) {
	std::ifstream file(fileName, std::ios::binary);
	std::vector<std::vector<int>> map;
	std::string row;
	while ( std::getline(file, row) ) {
		std::stringstream ss(row);
		int n;
		std::vector<int> v;
		while (ss >> n) {
			v.push_back(n);
			if (ss.peek() == ',') {
				ss.ignore();
			}
		}
		map.push_back(v);
	}

	int width = map.size();
	int height = map.at(0).size();
	EulerGraph result(width, height);
	for (int x=0; x<width; x++) {
		for (int y=0; y<height; y++) {
			result.setWeight(x, y, map.at(x).at(y));
		}
	}
	return result;
}

int main (int argc, char* argv[]) {
	EulerGraph g = importGraphFromFile("./p082_matrix.txt");
	g.print();

	std::set<std::pair<int, int>> finalNodes;
	int width = g.getWidth();
	int height = g.getHeight();
	for (int i=0; i<width; i++) {
		finalNodes.insert({i, height-1});
	}

	std::list<std::pair<int, int>> path;
	path = graph::DijkstraSolver::solve(g, {-1, -1}, finalNodes);
	if (path.empty()) {
		std::cout << "Could not calculate path" << std::endl;
		return 0;
	}

	std::set<std::pair<int, int>> pathSet;

	for (auto& p : path) {
		pathSet.insert(p);
	}

	g.print(pathSet);

	int pathSum = 0;
	for (auto& p : path) {
		if (p.first != -1) {
			pathSum += g.at(p.first, p.second);
		}
	}

	std::cout << "Path cost: " << pathSum << std::endl;

	return 0;
}

