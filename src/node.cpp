#include <vector>

namespace speeddemon {
namespace dag {

class Node {
	const unsigned int id;

       public:
	std::vector<Node> children;

	// Constructior
	Node(unsigned int id) : id(id) {}

	void add_child() {}

	void update() {}

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
