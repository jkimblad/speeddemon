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
	Node* rootNode = nullptr;
	std::vector<Node*> nodes;

	Node* get_root() { return nodes.front(); };

       public:
	Cfg() {}

	// Called when a timestamp is triggered
	void stamp_trigger(const int id, duration timeDuration) {
		// Check if id exists or if we should create a new node
		if (get_node(id)) {
			// Update the last visited node with fresh information
			if (lastVisited) {
				lastVisited->add_duration(timeDuration,
							  get_node(id));
			}
		} else if (!lastVisited) {
			// First node we visit
			rootNode = new Node(id);
			lastVisited = rootNode;

		} else {
			// Create a new node and add it to the graph
			lastVisited->add_duration(timeDuration, new Node(id));
		}

		lastVisited = get_node(id);
	}

	void print() {
		for (std::vector<Node*>::iterator it = nodes.begin();
		     it != nodes.end(); it++) {
			(*it)->print();
		}
	}

       private:
	// Get an existing node
	Node* get_node(const int id) {
		auto&& temp = std::find_if(
		    nodes.begin(), nodes.end(),
		    [id](Node* n) -> bool { return n->get_id() == id; });

		// A match was found
		if (temp != nodes.end()) {
			return *temp;
		} else {
			return nullptr;
		}
	}
};
}  // namespace cfg
}  // namespace speeddemon
