#include "speeddemon.hpp"

#include <algorithm>
#include <chrono>
#include <csignal>
#include <iostream>
#include <string>
#include <vector>

namespace speeddemon {

// Constructor
SpeedDemon::SpeedDemon() {
	// This value wont be used, but variable needs to be initialized
	previousExitTime = std::chrono::steady_clock::now();
}

// perform a new timestamp somewhere in the code
void SpeedDemon::time_stamp(int id) {
	// Use steady_clock to do measurements, as the usage of
	// high_resolution_clock should be avoided due to inconsistent
	// implementations across different standard libraries.
	std::chrono::steady_clock::time_point timeNow =
	    std::chrono::steady_clock::now();

	graph.stamp_trigger(
	    id, std::chrono::duration_cast<std::chrono::microseconds>(
		    timeNow - previousExitTime));

	previousExitTime = std::chrono::steady_clock::now();
}

void SpeedDemon::print_dag() { graph.print(); }

}  // namespace speeddemon
