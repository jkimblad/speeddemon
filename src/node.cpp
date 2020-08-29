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
	typedef std::chrono::steady_clock::time_point timestamp;
	typedef std::chrono::microseconds time_microseconds;
	typedef std::pair<Node*, std::vector<time_microseconds>> child;

	const unsigned int id;

	// Vector of pairs consitsing of:
	// 	- First: Node* child
	// 	- Second: std::vector<timestamp>
	std::vector<child> children;

	timestamp latestStamp;

	// Returns a child node given its id
	child get_child_by_id(const unsigned int id) {
		// TODO: I dont like using auto
		// 	- I think its fine when using iterators, maybe we want
		// to always note the type in a comment before?
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

	child add_child(Node* child_node, time_microseconds dur) {
		// Calculate duration since last visited Node
		child temp_child;
		temp_child.first = child_node;
		// Add child node
		children.push_back(std::move(temp_child));

		return children.back();
	}

	void update_latest_stamp(timestamp stamp) { latestStamp = stamp; }

	void add_duration(timestamp timeStamp, const unsigned int childId,
			  Node* childNode) {
		time_microseconds dur =
		    std::chrono::duration_cast<std::chrono::microseconds>(
			timeStamp - latestStamp);
		// Check if child has been visited before, else its a
		// new one
		try {
			child stamped_child = get_child_by_id(childId);
			// Add new duration
			stamped_child.second.push_back(dur);
			// Update its latest stamp
			stamped_child.first->update_latest_stamp(timeStamp);
		} catch (const std::invalid_argument& ia) {
			if (childNode) {
				children.push_back(child(
				    childNode, std::vector<time_microseconds>(
						   dur.count())));
			} else {
				add_child(new Node(childId), dur);
			}
		}

		// Update the childs stamp for when it last was visited
		get_child_by_id(id).first->update_latest_stamp(timeStamp);
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

	timestamp get_latest_stamp() { return latestStamp; }

	// Override == operator
	// bool operator==(const Node& other) {
	//// Compare id's to determine equalness
	// if (id == other.id) {
	// return true;
	//} else {
	// return false;
	//}
	//}
};  // namespace cfg
}  // namespace cfg
}  // namespace speeddemon
