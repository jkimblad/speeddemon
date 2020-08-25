#include <algorithm>
#include <chrono>
#include <csignal>
#include <iostream>
#include <string>
#include <vector>

#include "dag.cpp"

namespace speeddemon {

// TODO:
//	- Subtract duration spent in function calls inside this library from
// results
//
class SpeedDemon {
	static std::vector<unsigned int> existingStamps;
	static dag::Dag graph;
	static std::chrono::steady_clock::time_point exit_time;

	static void signal_handler(int signum) {
		// Make sure we print all the results before returning
		std::cout << "Interrupt signal (" << signum << ") received"
			  << std::endl;

		print_dag();
		return;
	}

       public:
	// Constructor
	SpeedDemon() {}

	void init() {
		// Perform counter approximations
		//	- How long does it take to add a node
		//	- How long does it take to make a timestamp

		// Make sure that we capture kill signals so we can clean up and
		// print any results before we exit
		// TODO: This is good for now, but in the future we will
		// probably want to have continous updates printed out on the
		// CLI. Maybe using something like "ncurses"?
		signal(SIGINT, signal_handler);
		return;

		//
	}

	// perform a new timestamp somewhere in the code
	void time_stamp(unsigned int id) {
		// Use steady_clock, as the usage of high_resolution_clock
		// should be avoided due to inconsistent implementations across
		// different standard libraries.
		std::chrono::steady_clock::time_point timeStamp =
		    std::chrono::steady_clock::now();

		graph.stamp_trigger(id, timeStamp);

		exit_time = std::chrono::steady_clock::now();
		return;
	}

	static void print_dag() { return; }
};

}  // namespace speeddemon
