#ifndef DELIVERY_PARSER_H
#define DELIVERY_PARSER_H

#include "House.h"
#include <vector>

class DeliveryParser {
public:
	DeliveryParser(const char upKey = '^', const char downKey = 'v',
		const char rightKey = '>', const char leftKey = '<') :
		_upKey(upKey),
		_downKey(downKey),
		_rightKey(rightKey),
		_leftKey(leftKey)
		{}

	std::vector<House*>* createDeliveryList(const char* input, const unsigned numSantas = 1);

private:
	const char _upKey;
	const char _downKey;
	const char _rightKey;
	const char _leftKey;
};

#endif
