#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

class LightController {
public:
	enum LightStyle {
		K_BINARY,
		K_INCREMENTAL
	};

	LightController(LightStyle lightStyle = K_BINARY, unsigned width = 1000, unsigned height = 1000) :
		_width(width),
		_height(height),
		_lights(nullptr),
		_lightStyle(lightStyle)
	{
		if (_width && _height) {
			_lights = new char*[_width];
			for (unsigned x = 0; x < _width; ++x) {
				_lights[x] = new char[height];
				for (unsigned y = 0; y < _height; ++y) {
					_lights[x][y] = 0;
				}
			}
		}
	}

	~LightController() {
		if (_lights == nullptr) {
			for (unsigned x = 0; x < _width; ++x) {
				delete [] _lights[x];
			}
			delete [] _lights;
			_lights = nullptr;
		}
	}

	inline void turnOn(unsigned x0, unsigned y0, unsigned x1, unsigned y1) {
		actOnLights(K_ON, x0, y0, x1, y1);
	}
	inline void turnOff(unsigned x0, unsigned y0, unsigned x1, unsigned y1) {
		actOnLights(K_OFF, x0, y0, x1, y1);
	}
	inline void toggle(unsigned x0, unsigned y0, unsigned x1, unsigned y1) {
		actOnLights(K_TOGGLE, x0, y0, x1, y1);
	}

	void parseFile(const char *filename);

	unsigned getLitCount() {
		unsigned count = 0;
		for (unsigned x = 0; x < _width; ++x) {
			for (unsigned y = 0; y < _height; ++y) {
				count += _lights[x][y] ? 1 : 0;
			}
		}

		return count;
	}

	unsigned getBrightness() {
		unsigned count = 0;
		for (unsigned x = 0; x < _width; ++x) {
			for (unsigned y = 0; y < _height; ++y) {
				count += _lights[x][y];
			}
		}

		return count;
	}

private:
	const unsigned _width;
	const unsigned _height;
	char** _lights;
	const LightStyle _lightStyle;

	enum Action {
		K_ON,
		K_OFF,
		K_TOGGLE
	};

	void actOnLights(Action act, unsigned x0, unsigned y0, unsigned x1, unsigned y1);
};

#endif