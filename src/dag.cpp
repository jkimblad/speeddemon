#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "node.cpp"

namespace speeddemon {
namespace dag {
class Dag {
	static unsigned int id_counter;
	std::vector<Node> nodes;

       public:
	Dag() {
		// Initialize if_counter if this is the first instance of the
		// class
		if (!id_counter) {
			id_counter = 0;
		}
	}

	Node get_root() { return nodes.front(); };

	void add_node() {}

	Node& get_node(const unsigned int id) {
		std::vector<Node>::iterator temp =
		    std::find(nodes.begin(), nodes.end(), id);

		// A match was found
		if (temp != nodes.end()) {
			return *temp;
		} else {
			// std::string errorMessage =
			// std::string("get_node() was called with id (") +
			// id +
			// std::string(") which is not assigned to any node!");
			// TODO: throw proper error
			throw std::runtime_error("temp"
						 //(std::ostringstream()
						 //<< "Could not!"
						 //).str()
			);
		}
	}
};
}  // namespace dag
}  // namespace speeddemon
