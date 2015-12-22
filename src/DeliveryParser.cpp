#include "DeliveryParser.h"

std::vector<House*>* DeliveryParser::createDeliveryList(const char* input, const unsigned numSantas) {
	std::vector<House*>* houses = new std::vector<House*>();

	if (numSantas == 0) return houses;

	houses->push_back(new House(0, 0));

	if (input == nullptr) return houses;

	int *x = new int[numSantas];
	int *y = new int[numSantas];
	unsigned activeSanta = 0;

	for (unsigned i = 0; i < numSantas; ++i) {
		x[i] = 0;
		y[i] = 0;
	}

	while (*input) {
		if (_upKey == *input) ++y[activeSanta];
		else if (_downKey == *input) --y[activeSanta];
		else if (_rightKey == *input) ++x[activeSanta];
		else if (_leftKey == *input) --x[activeSanta];

		bool isNewHouse = true;

		for (auto house = houses->begin(); house != houses->end(); ++house) {
			if ((*house)->getX() == x[activeSanta] && (*house)->getY() == y[activeSanta]) {
				(*house)->givePresent();
				isNewHouse = false;
				break;
			}
		}

		if (isNewHouse) {
			houses->push_back(new House(x[activeSanta], y[activeSanta]));
		}

		++input;
		activeSanta = (activeSanta + 1) % numSantas;
	}

	delete [] x;
	delete [] y;

	return houses;
}
