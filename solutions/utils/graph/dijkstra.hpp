#ifndef GRAPH_DIJKSTRA_HPP_
#define GRAPH_DIJKSTRA_HPP_

#include "node.hpp"

#include <set>
#include <map>

namespace graph {

class DijkstraSolver {
private:
	DijkstraSolver() = delete;

public:
template<class T>
static std::list<T> solve(Graph<T> const& map,
		T startingNode, std::set<T> finalNodes)
{
	std::list<T> res;

	auto it = finalNodes.find(startingNode);
	if (it != finalNodes.end()) {
		res.push_back(startingNode);
		return res;
	}

	std::set<T> visited;
	std::set<std::pair<int, T>> unvisited;
	std::map<T, std::pair<int, T>> previousNodes;

	visited.insert(startingNode);

	T currentNode = startingNode;
	int currentWeight = 0;

	while (finalNodes.find(currentNode) == finalNodes.end()) {
		for (auto& p : map.getEdges(currentNode)) {
			if (visited.find(p.first) != visited.end()) {
				continue;
			}

			int newWeight = currentWeight + p.second;
			unvisited.insert({newWeight, p.first});

			auto it = previousNodes.find(p.first);
			if (it == previousNodes.end() ||
					newWeight < it->second.first) {
				previousNodes.insert({p.first,
						{newWeight, currentNode}});
			}
		}

		visited.insert(currentNode);

		auto it = unvisited.begin();
		if (it == unvisited.end()) {
			// No path found
			return res;
		}

		currentWeight = it->first;
		currentNode = it->second;

		unvisited.erase(it);
	}

	res.push_front(currentNode);
	while (currentNode != startingNode) {
		auto it = previousNodes.find(currentNode);
		currentNode = it->second.second;
		res.push_front(currentNode);
	}

	return res;
}

};

}; // namespace graph

#endif  // GRAPH_DIJKSTRA_HPP_


