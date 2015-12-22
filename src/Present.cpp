#include "Present.h"
#include "util.h"
#include <fstream>
#include <iostream>

int Present::getWrappingPaperRequired() {
	int surfaceAreas[] = {
		_length * _width,
		_width * _height,
		_height * _length
	};

	int slackArea = min(surfaceAreas[0], min(surfaceAreas[1], surfaceAreas[2]));
	int presentArea = 2 * (surfaceAreas[0] + surfaceAreas[1] + surfaceAreas[2]);
	int totalArea = slackArea + presentArea;

	return totalArea;
}

int Present::getRibbonRequired() {
	int maxDimension = max(_length, max(_width, _height));
	int perimeter = 2 * (_length + _width + _height - maxDimension);
	int bow = _length * _width * _height;

	int ribbonRequired = perimeter + bow;
	
	return ribbonRequired;
}

std::vector<Present*>* Present::createPresentsFromFile(const char *filename) {
	std::vector<Present*>* presents = new std::vector<Present*>();

	int presentCount = 0;
	std::ifstream file(filename);
	if (file.is_open()) {
		while (file.peek() != EOF) {
			int l, w, h;
			char x;
			file >> l >> x >> w >> x >> h;
			file >> std::ws; // devour whitespace

			// Debug print
			//std::cout << "Present(" << l << ", " << w << ", " << h << ")" << std::endl;

			presents->push_back(new Present(l, w, h));
			++presentCount;
		}
	}

	// Debug print
	//std::cout << "Number of presents: " << presentCount << std::endl;
	
	return presents;
}
