#include "WireKit.h"
#include <fstream>
#include <iostream>

uint16_t WireKit::getWireValue(const char *label) {
	return getWireValue(convertLabel(label));
}

uint16_t WireKit::getWireValue(const uint16_t label) {
	for (auto wire = _wires.begin(); wire != _wires.end(); ++wire) {
		if ((*wire)->getLabel() == label) {
			return (*wire)->getValue();
		}
	}

	return 0;
}

void WireKit::parseFile(const char *filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			// Debug output
			//std::cout << line << std::endl;

			std::stringstream instruction(line);
			processInstruction(instruction);
		}
	}
	return;
}

void WireKit::processInstruction(std::stringstream &instruction) {
	Operation op = getOperation(instruction.str());
	std::string devour;
	std::string lSourceWire, rSourceWire;
	Wire::Op operation = nullptr;
	std::string targetWire;
	
	// Read all as source wires, check if number, deal
	switch (op) {
	case OP_SET:
		{
			// value -> wire
			instruction >> lSourceWire >> devour >> targetWire;
			operation = &Wire::set;
		}
		break;
	case OP_NOT:
		{
			// NOT wire -> wire
			instruction >> devour >> lSourceWire >> devour >> targetWire;
			operation = &Wire::not;
		}
		break;
	case OP_AND:
		{
			// wire AND wire -> wire
			instruction >> lSourceWire >> devour >> rSourceWire >> devour >> targetWire;
			operation = &Wire::and;
		}
		break;
	case OP_OR:
		{
			// wire OR wire -> wire
			instruction >> lSourceWire >> devour >> rSourceWire >> devour >> targetWire;
			operation = &Wire::or;
		}
		break;
	case OP_LSHIFT:
		{
			// wire LSHIFT value -> wire
			instruction >> lSourceWire >> devour >> rSourceWire >> devour >> targetWire;
			operation = &Wire::lshift;
		}
		break;
	case OP_RSHIFT:
		{
			// wire RSHIFT value -> wire
			instruction >> lSourceWire >> devour >> rSourceWire >> devour >> targetWire;
			operation = &Wire::rshift;
		}
		break;
	default:
		break;
	}
	
	// Debug output
	//std::cout << targetWire << ": " << wireValue << std::endl;
	Wire* lWire = getWireFromSource(lSourceWire);
	Wire* rWire = getWireFromSource(rSourceWire);

	uint16_t label = convertLabel(targetWire.c_str());
	setupWire(label, lWire, rWire, operation);
}

Wire *WireKit::getWireFromSource(const std::string source) {
	if (!source.empty()) {
		if (source[0] >= 'a' && 'z' >= source[0]) {
			uint16_t label = convertLabel(source.c_str());
			return getWire(label);
		}
		else {
			uint16_t value = convertStringToUInt16(source);
			Wire *wire = new Wire(value);
			_wires.push_back(wire);
			return getWire(0);
		}
	}

	return nullptr;
}

Wire *WireKit::getWire(const uint16_t label) {
	if (label != 0) {
		for (auto wire = _wires.begin(); wire != _wires.end(); ++wire) {
			if ((*wire)->getLabel() == label) {
				return *wire;
			}
		}

		Wire *wire = new Wire(label, nullptr, nullptr, nullptr);
		_wires.push_back(wire);
	}

	return *(--_wires.end());
}

uint16_t WireKit::convertLabel(const char *label) {
	uint16_t result = 0;

	// Note: this isn't very scalable :(
	if (label && label[0] != 0) {
		result += 1 + label[0] - 'a';

		if (label[1] != 0) {
			result += 100 * (1 + label[1] - 'a');
		}
	}

	return result;
}

uint16_t WireKit::convertStringToUInt16(const std::string &number) {
	uint16_t result = 0;
	if (!number.empty()) {
		for (size_t i = 0; i < number.length(); ++i) {
			result *= 10;
			result += number[i] - '0';
		}
	}

	return result;
}

WireKit::Operation WireKit::getOperation(const std::string &instruction) {
	if (instruction.find("NOT") != std::string::npos) return OP_NOT;
	if (instruction.find("AND") != std::string::npos) return OP_AND;
	if (instruction.find("OR") != std::string::npos) return OP_OR;
	if (instruction.find("LSHIFT") != std::string::npos) return OP_LSHIFT;
	if (instruction.find("RSHIFT") != std::string::npos) return OP_RSHIFT;

	return OP_SET;
}

void WireKit::setupWire(const uint16_t label, Wire *lWire, Wire *rWire, const Wire::Op operation) {
	for (auto wire = _wires.begin(); wire != _wires.end(); ++wire) {
		if ((*wire)->getLabel() == label) {
			(*wire)->init(label, lWire, rWire, operation);
			return;
		}
	}

	// Note: if Wire is called wire (as above), data gets garbled? May just be debugger info
	Wire *newWire = new Wire(label, lWire, rWire, operation);
	// Debug print: Cautionary - only use on early values that use "set" op
	//std::cout << newWire.getLabel() << ": " << newWire.getValue() << std::endl;
	_wires.push_back(newWire);
}

void WireKit::reset() {
	for (auto wire = _wires.begin(); wire != _wires.end(); ++wire) {
		(*wire)->reset();
	}
}

void WireKit::print() {
	// Wire: value
	unsigned unnamedWireCount = 0;
	for (auto wire = _wires.begin(); wire != _wires.end(); ++wire) {
		uint16_t nameValue = (*wire)->getLabel();
		if (nameValue == 0) {
			++unnamedWireCount;
		}
		else {
			char name[3] = {0};
			name[0] = nameValue % 100;
			name[0] = name[0] ? (name[0] + 'a' - 1) : 0;
			name[1] = nameValue / 100;
			name[1] = name[1] ? (name[1] + 'a' - 1) : 0;

			std::cout << name << (name[1] == 0 ? " " : "") << ": " << (*wire)->getValue() << std::endl;
		}
	}
	std::cout << "+" << unnamedWireCount << " unnamed values" << std::endl;
}