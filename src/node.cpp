#include <algorithm>
#include <chrono>
#include <ctime>
#include <vector>

namespace speeddemon {
namespace dag {

class Node {
	typedef std::chrono::steady_clock::time_point timestamp;
	typedef std::pair<Node*, std::vector<timestamp>> child;

	const unsigned int id;

	// Vector of pairs consitsing of:
	// 	- First: Node* child
	// 	- Second: std::vector<timestamp>
	std::vector<child> children;

	// Returns a child node given its id
	Node* get_child_by_id(const unsigned int id) {
		// TODO: I dont like using auto
		auto it = std::find(children.begin(), children.end(), id);

		// Child al
		if (it != children.end()) {
			return it->first;
		} else {
			return nullptr;
		}
	}

       public:
	// Constructior
	Node(const unsigned int id) : id(id) {}

	void add_child(Node* child, timestamp timeStamp) {
		// Add child node pointer
		children.push_back(std::pair<Node*, std::vector<timestamp>>(
		    child, std::vector<timestamp>() = {timeStamp}));
	}

	void add_timestamp(timestamp stamp, const unsigned int child_id) {}

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
