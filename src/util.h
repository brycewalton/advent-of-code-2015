#ifndef UTIL_H
#define UTIL_H

#include <vector>

template <typename T, unsigned S>
inline unsigned arraySize(const T (&v)[S]) {
	return S;
}

template <typename T>
inline const T& min(const T &a, const T &b) {
	return a < b ? a : b;
}

template <typename T>
inline const T& max(const T &a, const T &b) {
	return a > b ? a : b;
}

template <typename T>
inline const T& clamp(const T &a, const T &minValue, const T &maxValue) {
	return max(minValue, min(maxValue, a));
}

template <typename T>
void deleteVector(std::vector<T*> *v) {
	for (auto iter = v->begin(); iter != v->end(); ++iter) {
		delete (*iter);
	}
	delete v;
}

template <typename T>
void clearVector(std::vector<T*> &v) {
	for (auto iter = v.begin(); iter != v.end(); ++iter) {
		delete (*iter);
	}
	v.clear();
}

char * readFile(const char *filename);

#endif
