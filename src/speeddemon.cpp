#include "speeddemon.hpp"

#include <algorithm>
#include <chrono>
#include <csignal>
#include <iostream>
#include <string>
#include <vector>

namespace speeddemon {

// TODO: Is init really needed, or can we perform all of the action in
// the constructor? If we use several constructors we can use init for
// peforming common tasks
// void SpeedDemon::init() {
//// TODO: Perform counter approximations
////	- How long does it take to add a node
////	- How long does it take to make a timestamp

//// Make sure that we capture kill signals so we can clean up and
//// print any results before we exit

//// TODO: This is good for now, but in the future we will
//// probably want to have continous updates printed out on the
//// CLI. Maybe using something like "ncurses"?
//// We will also need to make sure information is printed if we
//// exit from the program normally, as we cant assume it will
//// always be interrupted.
// return;

////
//}

// Constructor
SpeedDemon::SpeedDemon() {
	// This value wont be used, but variable needs to be initialized
	previousExitTime = std::chrono::steady_clock::now();
}

// perform a new timestamp somewhere in the code
void SpeedDemon::time_stamp(int id) {
	// Use steady_clock, as the usage of high_resolution_clock
	// should be avoided due to inconsistent implementations across
	// different standard libraries.
	std::chrono::steady_clock::time_point timeNow =
	    std::chrono::steady_clock::now();

	graph.stamp_trigger(
	    id, std::chrono::duration_cast<std::chrono::microseconds>(
		    timeNow - previousExitTime));

	previousExitTime = std::chrono::steady_clock::now();
	return;
}

void SpeedDemon::print_dag() {
	// How do we best print the information? PepoThink
	// Ideas:
	// 	- Iterate over each individual node. Print its children
	// and the average duration to get to them.
	// 	- GUI :DDD

	graph.print();

	return;
}

}  // namespace speeddemon
