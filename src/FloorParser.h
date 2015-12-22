#ifndef FLOOR_PARSER_H
#define FLOOR_PARSER_H

class FloorParser {
public:
	FloorParser(const char upKey = '(', const char downKey = ')') :
		_upKey(upKey),
		_downKey(downKey)
		{}

	int getFinalFloor(const char *input);
	int getFloorIndex(const char *input, const int floor);

private:
	const char _upKey;
	const char _downKey;

	int traverse(const char *input, const int seekFloor = 0);
};

#endif
