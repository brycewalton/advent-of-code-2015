#include "LogicParser.h"
#include <fstream>
#include <iostream>

void LogicParser::parseFile(const char *filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::cout << line << std::endl;
			std::stringstream instruction(line);
			processInstruction(instruction);
		}
	}
	return;
}

void LogicParser::processInstruction(std::stringstream &instruction) {
	Operation op = getOperation(instruction.str());
	std::string devour;
	std::string targetWire;
	uint16_t wireValue = 0;
		
	switch (op) {
	case OP_SET:
		{
			// value -> wire
			instruction >> wireValue >> devour >> targetWire;
		}
		break;
	case OP_NOT:
		{
			// NOT wire -> wire
			std::string sourceWire;
			instruction >> devour >> sourceWire >> devour >> targetWire;
			wireValue = ~(getWireSignal(sourceWire.c_str()));
		}
		break;
	case OP_AND:
		{
			// wire AND wire -> wire
			std::string aWire, bWire;
			instruction >> aWire >> devour >> bWire >> devour >> targetWire;
			wireValue = getWireSignal(aWire.c_str()) & getWireSignal(bWire.c_str());
		}
		break;
	case OP_OR:
		{
			// wire OR wire -> wire
			std::string aWire, bWire;
			instruction >> aWire >> devour >> bWire >> devour >> targetWire;
			wireValue = getWireSignal(aWire.c_str()) | getWireSignal(bWire.c_str());
		}
		break;
	case OP_LSHIFT:
		{
			// wire LSHIFT value -> wire
			std::string sourceWire;
			uint16_t shiftValue;
			instruction >> sourceWire >> devour >> shiftValue >> devour >> targetWire;
			wireValue = getWireSignal(sourceWire.c_str()) << shiftValue;
		}
		break;
	case OP_RSHIFT:
		{
			// wire RSHIFT value -> wire
			std::string sourceWire;
			uint16_t shiftValue;
			instruction >> sourceWire >> devour >> shiftValue >> devour >> targetWire;
			wireValue = getWireSignal(sourceWire.c_str()) >> shiftValue;
		}
		break;
	default:
		break;
	}

	// Debug output
	//std::cout << targetWire << ": " << wireValue << std::endl;

	setWireSignal(convertNameToShort(targetWire.c_str()), wireValue);
}

LogicParser::Operation LogicParser::getOperation(const std::string &instruction) {
	if (instruction.find("NOT") != std::string::npos) return OP_NOT;
	if (instruction.find("AND") != std::string::npos) return OP_AND;
	if (instruction.find("OR") != std::string::npos) return OP_OR;
	if (instruction.find("LSHIFT") != std::string::npos) return OP_LSHIFT;
	if (instruction.find("RSHIFT") != std::string::npos) return OP_RSHIFT;

	return OP_SET;

}

uint16_t LogicParser::getWireSignal(const char *name) {
	const uint16_t nameValue = convertNameToShort(name);
	uint16_t result = 0;

	if (nameValue) {
		for (auto wire = _wires.begin(); wire != _wires.end(); ++wire) {
			if (nameValue == getWireName(*wire)) {
				result = getWireSignal(*wire);
				break;
			}
		}
	}

	return result;
}

void LogicParser::setWireSignal(uint16_t name, uint16_t value) {
	uint16_t result = 0;
	const uint32_t wireValue = getWire(name, value);

	if (name) {
		for (auto wire = _wires.begin(); wire != _wires.end(); ++wire) {
			if (name == getWireName(*wire)) {
				*wire = wireValue;
				return;
			}
		}

		_wires.push_back(wireValue);
	}
}

uint16_t LogicParser::convertNameToShort(const char *name) {
	uint16_t result = 0;

	// Note: this isn't very scalable :(
	if (name && name[0] != 0) {
		result += 1 + name[0] - 'a';

		if (name[1] != 0) {
			result += 100 * (1 + name[1] - 'a');
		}
	}

	return result;
}

uint16_t LogicParser::getWireName(uint32_t wire) {
	uint16_t result = (uint16_t)((wire & Bitmask::Name) >> 16);

	return result;
}

uint16_t LogicParser::getWireSignal(uint32_t wire) {
	uint16_t result = (uint16_t)(wire & Bitmask::Signal);

	return result;
}

uint32_t LogicParser::getWire(uint16_t name, uint16_t signal) {
	uint32_t result = ((uint32_t)(name) << 16) + signal;

	return result;
}

void LogicParser::print() {
	// Wire: value
	for (auto wire = _wires.begin(); wire != _wires.end(); ++wire) {
		uint16_t nameValue = getWireName(*wire);
		char name[3] = {0};
		name[0] = nameValue % 100;
		name[0] = name[0] ? (name[0] + 'a' - 1) : 0;
		name[1] = nameValue / 100;
		name[1] = name[1] ? (name[1] + 'a' - 1) : 0;

		std::cout << name << (name[1] == 0 ? " " : "") << ": " << getWireSignal(*wire) << std::endl;
	}
}
