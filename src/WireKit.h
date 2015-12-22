#ifndef WIRE_KIT_H
#define WIRE_KIT_H

#include <vector>
#include "Wire.h"
#include <sstream>
#include "util.h"

class WireKit {
public:
	inline void clear() {
		clearVector(_wires);
	}

	uint16_t getWireValue(const char *label);
	uint16_t getWireValue(const uint16_t label);

	void parseFile(const char* filename);
	void processInstruction(std::stringstream &instruction);
	void reset();
	void print();

private:
	std::vector<Wire*> _wires;

	enum Operation {
		OP_SET,
		OP_NOT,
		OP_AND,
		OP_OR,
		OP_LSHIFT,
		OP_RSHIFT
	};
	Operation getOperation(const std::string &instruction);
	static uint16_t convertSource(const std::string source) {
		return (!source.empty() && source[0] >= 'a' && 'z' >= source[0]) ? convertLabel(source.c_str()) : convertStringToUInt16(source);
	}
	Wire *getWireFromSource(const std::string source);
	Wire *getWire(const uint16_t);
	static uint16_t convertLabel(const char *label);
	static uint16_t convertStringToUInt16(const std::string &number);
	void setupWire(const uint16_t label, Wire *lWire, Wire *rWire, const Wire::Op operation);
};

#endif
