#include <algorithm>
#include <chrono>
#include <cstddef>
#include <sstream>
#include <stdexcept>

#include "node.cpp"

namespace speeddemon {
namespace cfg {
class Cfg {
	typedef std::chrono::microseconds duration;

	Node* lastVisited = nullptr;

	std::vector<Node*> nodes;

	Node* get_root() { return nodes.front(); };

       public:
	Cfg() {}

	// Called when a timestamp is triggered
	void stamp_trigger(const unsigned int id, duration timeDuration) {
		// Check if id exists or if we should create a new node
		if (get_node(id)) {
			// TODO: Check if node is start node, as no timing
			// information should be saved. We cant take time from
			// init() without creating the root node in init(),
			// since the timing information is kept in the parent
			// and not in the child.
			//
			// Update the last visited node with fresh information
			// We need to also provide a pointer to the node in the
			// graph with the same id if it exists
			lastVisited->add_duration(timeDuration, id,
						  get_node(id));
		} else {
			// Add new node to the graph
			// TODO: This call should be changed to an add_duration
			// call with a newly created node
			lastVisited->add_child(new Node(id), timeDuration);
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
			// Temp is an iterator, we want to return a pointer
			// to the current object its pointing to. We can do this
			// by dereferencing the iterator (*) and the get a
			// pointer tot he object via &.
			return *temp;
		} else {
			return nullptr;
		}
	}
};
}  // namespace cfg
}  // namespace speeddemon
