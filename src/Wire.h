#ifndef WIRE_H
#define WIRE_H

#include <cstdint>

class Wire {
public:
	typedef uint16_t (Wire::*Op)() const;

	Wire(const uint16_t value) : _operation(nullptr), _lWire(nullptr), _rWire(nullptr), _label(0), _value(value), _processValue(true) {};
	Wire(const uint16_t label, Wire *lWire, Wire *rWire, const Op operation);
	void init(const uint16_t label, Wire *lWire, Wire *rWire, const Op operation);

	inline void reset() {
		_processValue = true;
	}

	inline uint16_t getValue() {
		return (_processValue && _operation != nullptr) ? doOperation() : _value;
	}
	inline uint16_t getLabel() {
		return _label;
	}

	Wire &operator=(const Wire &rhs) {
		_label = rhs._label;
		_lWire = rhs._lWire;
		_rWire = rhs._rWire;
		_operation = rhs._operation;

		return *this;
	}

	// Operations
	uint16_t set() const {
		return _lWire->getValue();
	}
	uint16_t not() const {
		return ~(_lWire->getValue());
	}
	uint16_t and() const {
		return _lWire->getValue() & _rWire->getValue();
	}
	uint16_t or() const {
		return _lWire->getValue() | _rWire->getValue();
	}
	uint16_t lshift() const {
		return _lWire->getValue() << _rWire->getValue();
	}
	uint16_t rshift() const {
		return _lWire->getValue() >> _rWire->getValue();
	}


private:
	Op _operation;
	Wire* _lWire;
	Wire* _rWire;
	uint16_t _label;
	uint16_t _value;
	bool _processValue;

	inline uint16_t doOperation() {
		_value = (this->*_operation)();
		//_operation = nullptr;
		_processValue = false;
		return _value;
	}
};

#endif
