#include "FloorParser.h"
#include <iostream>

// Returns the value of the floor after parser all input
int FloorParser::getFinalFloor(const char *input) {
	return traverse(input);
}

// Returns the 1-based index of that the desired floor is reached
// If the desired floor is not reached, returns -1
int FloorParser::getFloorIndex(const char *input, const int floor) {
	return traverse(input, floor);
}

// Parses input, calculating floor value
// If a specific floor is desired, returns the 1-based index that the input first reaches that floor
// If seekFloor is 0, returns the final floor after parsing all input
int FloorParser::traverse(const char *input, const int seekFloor) {
	if (input == nullptr) return seekFloor ? -1 : 0;

	int floor = 0;
	const char *start = input;
	while (*input != 0) {
		if (*input == _upKey) {
			++floor;
		}
		else if (*input == _downKey) {
			--floor;
		}

		// Debug print
		//std::cout << *input << " -> " << floor << std::endl;
		
		++input;

		if (seekFloor && seekFloor == floor) {
			return input - start;
		}
	}

	return seekFloor ? -1 : floor;
}