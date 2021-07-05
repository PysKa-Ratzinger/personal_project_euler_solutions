#ifndef GRAPH_NODE_HPP_
#define GRAPH_NODE_HPP_

#include <list>

namespace graph {

template <class T>
class Graph {
public:
	virtual ~Graph() = default;

	virtual std::list<std::pair<T, int>> getEdges(const T& node) const = 0;
};

}; // namespace graph

#endif  // GRAPH_NODE_HPP_

