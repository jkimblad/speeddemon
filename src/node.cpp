#include <algorithm>
#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>
#include <vector>

namespace speeddemon {
namespace cfg {

class Node {
	typedef std::chrono::steady_clock::time_point timestamp;
	typedef std::pair<Node*, std::vector<timestamp>> child;

	const unsigned int id;

	// Vector of pairs consitsing of:
	// 	- First: Node* child
	// 	- Second: std::vector<timestamp>
	std::vector<child> children;

	// Returns a child node given its id
	child* get_child_by_id(const unsigned int id) {
		// TODO: I dont like using auto
		// TODO: Find uses == to compare type contained in children,
		// the type however is pair, and not node. Use find_if or
		// lambda?

		for (auto it = children.begin(); it != children.end(); it++) {
			if (it->first->get_id() == id) {
				return &*it;
			}
		}
		return nullptr;
	}

       public:
	// Constructior
	// ID is given by the user when creating a new timestamp
	Node(const unsigned int id) : id(id) {}

	void add_child(Node* child, timestamp timeStamp) {
		// Add child node pointer
		children.push_back(std::pair<Node*, std::vector<timestamp>>(
		    child, std::vector<timestamp>() = {timeStamp}));
	}

	void add_timestamp(timestamp stamp, const unsigned int childId) {
		child* child_stamp = get_child_by_id(childId);
		// Check if child has been visited before, else its a
		// new one
		if (child_stamp) {
			child_stamp->second.push_back(stamp);
		} else {
			// Check if child already exist in graph before creating a new one
			child* child_node = get_child_by_id(childId);
			if(child_node) {
				add_child(child_node->first, stamp);
			} else {
				add_child(new Node(childId), stamp);
			}
		}
	}

	void print() {
		// for (auto it = children.begin(); it != children.end(); it++)
		// {
		// for (std::vector<timestamp>::iterator it_time
		// = it->second.begin();
		// it_time != it->second.end(); it_time++) {
		for (const auto& it : children) {
			std::cout << "ID: " << it.first->get_id() << std::endl;
			for (const auto& it_time : it.second) {
				std::cout
				    << "Node reached at"
				    // it_time is a time_point and not a
				    // duration, a duration consists of
				    // something like time_point - time_point
				    << std::chrono::duration_cast<
					   std::chrono::microseconds>(it_time -
								      it_time)
					   .count();
			}
		}
	}

	const unsigned int get_id() { return id; }

	// Override == operator
	bool operator==(const Node& other) {
		// Compare id's to determine equalness
		if (id == other.id) {
			return true;
		} else {
			return false;
		}
	}
};
}  // namespace dag
}  // namespace speeddemon
