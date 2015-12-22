#include "CharacterCounter.h"

unsigned CharacterCounter::_codeLength = 0;
unsigned CharacterCounter::_stringLength = 0;
unsigned CharacterCounter::_encodedLength = 0;

// Note: Well formatted string begins and ends with quote
void CharacterCounter::countCharacters(const char *str) {
	// Reset values
	_codeLength = 0;
	_stringLength = 0;
	_encodedLength = 0;

	if (!isWellFormedString(str)) {
		return;
	}

	// Begin counting
	unsigned codeLength = 2;		// "" -> ""     -> 2
	unsigned stringLength = 0;	// "" ->        -> 0
	unsigned encodedLength = 6;	// "" -> "\"\"" -> 6

	// Ignore open/close quote at start/end of string
	++str;
	while (*(str+1) != 0) {
		++codeLength;
		++stringLength;
		++encodedLength;

		if (*str == '\\') {
			++encodedLength;
			const char next = *(str+1);
			// Escape: \\ or \"
			if (next == '\\' || next == '"') {
				++codeLength;
				encodedLength += 2;
				++str;
			}
			// Escape: \xhh
			else if (next == 'x') {
				if (isHexChar(*(str+2)) && isHexChar(*(str+3))) {
					codeLength += 3;
					encodedLength += 3;
					str += 3;
				}
			}
		}

		++str;
	}

	// No errors: Store values
	_codeLength = codeLength;
	_stringLength = stringLength;
	_encodedLength = encodedLength;
}

bool CharacterCounter::isWellFormedString(const char *str) {
	if (str != nullptr) {
		if (*str == '"') {
			for (/*blank*/; *str != 0; ++str) {
				if (*(str+1) == 0 && *str == '"') {
					return true;
				}
			}
		}
	}

	return false;
}

bool CharacterCounter::isHexChar(const char c) {
	bool isNumber = '0' <= c && c <= '9';
	bool isLower = 'a' <= c && c <= 'f';
	bool isUpper = 'A' <= c && c <= 'F';

	return isNumber || isLower || isUpper;
}