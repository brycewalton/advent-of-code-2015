#include "util.h"
#include <fstream>

// Reads a file into a created character buffer
// Caller is responsible for deleting this memory
char * readFile(const char *filename) {
	std::ifstream input(filename);
	if (input.is_open()) {
		input.seekg(0, input.end);
		unsigned length = static_cast<unsigned>(input.tellg());
		input.seekg(0, input.beg);

		char *buffer = new char[length+1];
		buffer[length] = 0;
		input.read(buffer, length);
		input.close();

		return buffer;
	}

	return nullptr;
}
