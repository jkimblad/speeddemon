#include <algorithm>
#include <chrono>
#include <cstddef>
#include <sstream>
#include <stdexcept>

#include "node.cpp"

namespace speeddemon {
namespace dag {
class Dag {
	typedef std::chrono::steady_clock::time_point timestamp;

	static unsigned int id_counter;
	static Node* lastVisited;

	std::vector<Node> nodes;

	Node get_root() { return nodes.front(); };

       public:
	Dag() {
		// Initialize if_counter if this is the first instance of the
		// class
		if (!id_counter) {
			id_counter = 0;
		}

		lastVisited = nullptr;
	}

	// Called when a timestamp is triggered
	void stamp_trigger(const unsigned int id, timestamp timeStamp) {
		// Check if id exists or if we should create a new node
		if (std::find(nodes.begin(), nodes.end(), id) != nodes.end()) {
			// TODO: Check if node is start node, as no timing
			// information should be saved
			//
			// Update the last visited node with fresh information
			lastVisited->add_timestamp(timeStamp, id);
		} else {
			new_node(id, timeStamp);
		}

		// Set this visited node to lastVistited for the next function
		// call
		lastVisited = get_node(id);
	}

	// Add a new node
	void new_node(const unsigned int id, timestamp timeStamp) {
		Node* node = new Node(id);

		// Add parent nodes
		lastVisited->add_child(node, timeStamp);
	}

	// Get an existing node
	Node* get_node(const unsigned int id) {
		std::vector<Node>::iterator temp =
		    std::find(nodes.begin(), nodes.end(), id);

		// A match was found
		if (temp != nodes.end()) {
			// TODO temp is an iterator, we want to return a pointer
			// to the current object its pointing to. We can do this
			// by dereferencing the iterator (*) and the get a
			// pointer tot he object via &.
			return &*temp;
		} else {
			// TODO: throw proper error including id
			throw std::runtime_error(
			    "Error! Could not get node by given id!");
		}
	}
};
}  // namespace dag
}  // namespace speeddemon
