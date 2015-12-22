#include "LightController.h"
#include "util.h"
#include <fstream>
#include <string>
//#include <iostream>

void LightController::parseFile(const char *filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		while (file.peek() != EOF) {
			std::string action;
			std::string through;
			unsigned x0, y0, x1, y1;
			char x;
			file >> action;
			if (action.compare("turn") == 0) {
				file >> action;
			}

			file >> x0 >> x >> y0 >> through >> x1 >> x >> y1 >> std::ws;

			// Debug print
			//std::cout << action << " " << x0 << "," << y0 << through << x1 << "," << y1 << std::endl;

			if (action.compare("on") == 0) turnOn(x0, y0, x1, y1);
			else if (action.compare("off") == 0) turnOff(x0, y0, x1, y1);
			else if (action.compare("toggle") == 0) toggle(x0, y0, x1, y1);
		}
	}
}

// Note: x1 and y1 are inclusive
void LightController::actOnLights(Action act, unsigned x0, unsigned y0, unsigned x1, unsigned y1) {
  if (max(x0, x1) >= _width || max(y0, y1) >= _height) return;

	for (unsigned x = x0; x <= x1; ++x) {
		for (unsigned y = y0; y <= y1; ++y) {
			char newValue = 0;
			char modifyValue = 0;
			switch (act) {
			case K_ON:
				newValue = 1;
				modifyValue = 1;
				break;
			case K_OFF:
				newValue = 0;
				modifyValue = -1;
				break;
			case K_TOGGLE:
				newValue = _lights[x][y] ? 0 : 1;
				modifyValue = 2;
				break;
			default:
				break;
			}

			if (_lightStyle == K_BINARY) {
				_lights[x][y] = newValue;
			}
			else if (_lightStyle == K_INCREMENTAL) {
				if (modifyValue > 0 || _lights[x][y] > 0) {
					_lights[x][y] = max(0, _lights[x][y] + modifyValue);
				}
			}
		}
	}
}