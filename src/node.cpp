#include <algorithm>
#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace speeddemon {
namespace cfg {

class Node {
	typedef std::chrono::microseconds duration;
	typedef std::chrono::microseconds time_microseconds;
	typedef std::pair<Node*, std::vector<time_microseconds>> child;

	const int id;

	// Vector of pairs consitsing of:
	// 	- First: Node* child
	// 	- Second: std::vector<duration>
	std::vector<child> children;

	// Returns a child node given its id
	child& get_child_by_id(const int id) {
		// children type: std::vector<child>
		for (auto it = children.begin(); it != children.end(); it++) {
			if (it->first->get_id() == id) {
				return *it;
			}
		}
		throw std::invalid_argument(
		    "get_child_by_id received non-existing id");
	}

       public:
	// Constructor
	// ID is given by the user when creating a new timestamp
	Node(const int id) : id(id) {}

	void add_duration(duration timeDuration, Node* childNode) {
		// Check if child has been visited before from this node, else
		// we are given a pointer to a newly created node or a node
		// that exists somewhere else in the graph
		try {
			child stamped_child =
			    get_child_by_id(childNode->get_id());
			// Add new duration
			stamped_child.second.push_back(timeDuration);
		} catch (const std::invalid_argument& ia) {
			// The node is not yet registered as a child node to
			// the current node
			if (childNode) {
				children.push_back(child(
				    childNode, std::vector<duration>(
						   timeDuration.count())));
			}
		}
	}

	void print() {
		for (const auto& it : children) {
			std::cout << "ID: " << it.first->get_id() << std::endl;
			for (const auto& it_time : it.second) {
				std::cout << "Duration " << it_time.count()
					  << std::endl;
			}
		}
	}

	const int get_id() { return id; }
};  // namespace cfg
}  // namespace cfg
}  // namespace speeddemon
