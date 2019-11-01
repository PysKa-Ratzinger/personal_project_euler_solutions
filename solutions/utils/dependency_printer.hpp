#ifndef DEPENDENCY_PRINTER_HPP_
#define DEPENDENCY_PRINTER_HPP_

#include <iostream>
#include <memory>
#include <vector>

class DependencyPrinter {
public:
	class Node {
	public:
		virtual ~Node() = default;

		virtual std::vector<std::shared_ptr<Node>> getDeps() const = 0;
	};

	std::ostream& print(std::ostream& os,
			std::vector<std::shared_ptr<Node>>) const;
};

#endif  // DEPENDENCY_PRINTER_HPP_

