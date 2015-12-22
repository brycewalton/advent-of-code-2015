#ifndef LOGIC_PARSER_H
#define LOGiC_PARSER_H

#include <cstdint>
#include <vector>
#include <sstream>

class LogicParser {
public:
	void parseFile(const char* filename);
	uint16_t getWireSignal(const char* name);
	void processInstruction(std::stringstream &instruction);

	inline void clear() {
		_wires.clear();
	}

	void print();

private:

	// SET: value -> wire
	// AND/OR: wire AND wire -> wire
	// L/RSHIFT: wire LSHIFT value -> wire
	// NOT: NOT wire -> wire

	class Bitmask {
	public:
		const static uint32_t Signal = (1 << 16) - 1;
		const static uint32_t Name = ~Signal;
	};

	enum Operation {
		OP_SET,
		OP_NOT,
		OP_AND,
		OP_OR,
		OP_LSHIFT,
		OP_RSHIFT
	};

	Operation getOperation(const std::string &instruction);

	// Let's do some bit packing :D
	uint16_t convertNameToShort(const char* name);
	uint16_t getWireName(uint32_t wire);
	uint16_t getWireSignal(uint32_t wireName);
	uint32_t getWire(uint16_t name, uint16_t signal);

	void setWireSignal(uint16_t name, uint16_t value);

	std::vector<uint32_t> _wires;
};

#endif
