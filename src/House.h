#ifndef HOUSE_H
#define HOUSE_H

class House {
public:
	House(const int x, const int y) :
		_x(x),
		_y(y),
		_presents(0)
		{}

	inline bool operator==(const House &rhs) {
		return _x == rhs._x && _y == rhs._y;
	}

	inline const int getX() {
		return _x;
	}

	inline const int getY() {
		return _y;
	}

	inline const int getPresents() {
		return _presents;
	}

	inline void givePresent() {
		++_presents;
	}

private:
	int _x, _y, _presents;
};

#endif
