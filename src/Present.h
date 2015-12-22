#ifndef PRESENT_H
#define PRESENT_H

#include <vector>

class Present {
public:
	Present(int length, int width, int height) : 
		_length(length),
		_width(width),
		_height(height) 
		{}

	int getWrappingPaperRequired();
	int getRibbonRequired();
	
	static std::vector<Present*>* createPresentsFromFile(const char *filename);

private:
	int _length;
	int _width;
	int _height;

};

#endif
