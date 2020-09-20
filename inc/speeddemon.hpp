#include <chrono>

#include "cfg.cpp"

namespace speeddemon {
class SpeedDemon {
	cfg::Cfg graph;
	std::chrono::steady_clock::time_point previousExitTime;

       public:
	// Constructor
	SpeedDemon();
	void time_stamp(int id);
	void print_dag();
};
}  // namespace speeddemon
