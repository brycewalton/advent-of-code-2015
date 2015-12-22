#ifndef CHARACTER_COUNTER_H
#define CHARACTER_COUNTER_H

class CharacterCounter {
public:
	// Primary usage: Count, get last count
	static void countCharacters(const char *str);
	inline static unsigned getCodeLength() {
		return _codeLength;
	}
	inline static unsigned getStringLength() {
		return _stringLength;
	}
	inline static unsigned getEncodedLength() {
		return _encodedLength;
	}

	// Secondary usage: Count and immediately get
	inline static unsigned countCodeLength(const char *str) {
		countCharacters(str);
		return getCodeLength();
	}
	inline static unsigned countStringLength(const char *str) {
		countCharacters(str);
		return getStringLength();
	}
	inline static unsigned countEncodedLength(const char *str) {
		countCharacters(str);
		return getEncodedLength();
	}

private:
	static unsigned _codeLength;
	static unsigned _stringLength;
	static unsigned _encodedLength;

	static bool isWellFormedString(const char *str);
	static bool isHexChar(const char c);
};

#endif
