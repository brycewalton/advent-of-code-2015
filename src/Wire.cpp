#include "Wire.h"

Wire::Wire(const uint16_t label, Wire *lWire, Wire *rWire, const Wire::Op operation)
: _value(0)
{
	init(label, lWire, rWire, operation);
}

void Wire::init(const uint16_t label, Wire *lWire, Wire *rWire, const Wire::Op operation) {
	_label = label;
	_lWire = lWire;
	_rWire = rWire;
	_operation = operation;
	_processValue = true;
}
