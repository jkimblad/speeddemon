#include "node.cpp"

namespace speeddemon {
	namespace dag {
		class Dag {

			std::vector<Node> nodes;

			public:

			Node get_root() {
				return nodes.front();
			};

			void add_node() {

			}

		};
	}
}
