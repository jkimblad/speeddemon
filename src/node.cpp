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

	const unsigned int id;

	// Vector of pairs consitsing of:
	// 	- First: Node* child
	// 	- Second: std::vector<duration>
	std::vector<child> children;

	// Returns a child node given its id
	// TODO: This should return a pointer, as we might want to mess with the
	// child that is returned
	child get_child_by_id(const unsigned int id) {
		// TODO: Find uses == to compare type contained in children,
		// the type however is pair, and not node. Use find_if or
		// lambda?

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
	Node(const unsigned int id) : id(id) {}

	// TODO only add_duration OR add_child should be callable from cfg,
	// because this is confusing my brain right now. Add duration should
	// probably be the public interface, and should take an argument which
	// points to the childnode, which may be empty (non-existing in the
	// graph up until now) or contain some data. Either which I dont think
	// matter.
	child add_child(Node* child_node, duration dur) {
		// Calculate duration since last visited Node
		child temp_child;
		temp_child.first = child_node;
		// Add child node
		children.push_back(std::move(temp_child));

		return children.back();
	}

	void add_duration(duration timeDuration, const unsigned int childId,
			  Node* childNode) {
		// Check if child has been visited before, else its a
		// new one
		try {
			child stamped_child = get_child_by_id(childId);
			// Add new duration
			stamped_child.second.push_back(timeDuration);
		} catch (const std::invalid_argument& ia) {
			// A node with the same id exists in the graph, but it
			// is not yet registered as a childnode
			if (childNode) {
				children.push_back(child(
				    childNode, std::vector<duration>(
						   timeDuration.count())));
			} else {
				// This is the first time we see this node, so
				// we add it to the graph and as a child
				// TODO: This node wont end up in cfg.nodes.
				add_child(new Node(childId), timeDuration);
			}
		}
	}

	void print() {
		for (const auto& it : children) {
			std::cout << "ID: " << it.first->get_id() << std::endl;
			for (const auto& it_time : it.second) {
				std::cout << "Node reached at"
					  // it_time is a time_point and not a
					  // duration, a duration consists of
					  // something like time_point -
					  // time_point
					  << std::chrono::duration_cast<
						 std::chrono::microseconds>(
						 it_time - it_time)
						 .count();
			}
		}
	}

	const unsigned int get_id() { return id; }
};
}  // namespace cfg
}  // namespace speeddemon
