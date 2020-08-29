#include <algorithm>
#include <chrono>
#include <cstddef>
#include <sstream>
#include <stdexcept>

#include "node.cpp"

namespace speeddemon {
namespace cfg {
class Cfg {
	typedef std::chrono::steady_clock::time_point timestamp;

	Node* lastVisited = nullptr;

	std::vector<Node*> nodes;

	Node* get_root() { return nodes.front(); };

       public:
	Cfg() {}

	// Called when a timestamp is triggered
	void stamp_trigger(const unsigned int id, timestamp timeStamp) {
		// Check if id exists or if we should create a new node
		if (std::find_if(nodes.begin(), nodes.end(),
				 [id](Node* n) -> bool {
					 return n->get_id() == id;
				 }) != nodes.end()) {
			// TODO: Check if node is start node, as no timing
			// information should be saved. We cant take time from
			// init() without creating the root node in init(),
			// since the timing information is kept in the parent
			// and not in the child.
			//
			// Update the last visited node with fresh information
			lastVisited->add_timestamp(timeStamp, id);
		} else {
			// Add new node to the graph
			lastVisited->add_child(new Node(id), timeStamp);
		}

		// Set this visited node to lastVistited for the next function
		// call to object
		lastVisited = get_node(id);
	}

	void print() {
		// Iterate each node one by one
		for (std::vector<Node*>::iterator it = nodes.begin();
		     it != nodes.end(); it++) {
			(*it)->print();
		}
	}

       private:
	// Get an existing node
	Node* get_node(const unsigned int id) {
		auto&& temp = std::find_if(
		    nodes.begin(), nodes.end(),
		    [id](Node* n) -> bool { return n->get_id() == id; });

		// A match was found
		if (temp != nodes.end()) {
			// TODO temp is an iterator, we want to return a pointer
			// to the current object its pointing to. We can do this
			// by dereferencing the iterator (*) and the get a
			// pointer tot he object via &.
			return *temp;
		} else {
			// TODO: throw proper error including id
			throw std::runtime_error(
			    "Error! Could not get node by given id!");
		}
	}
};
}  // namespace dag
}  // namespace speeddemon
