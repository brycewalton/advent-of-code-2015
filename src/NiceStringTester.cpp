#include "NiceStringTester.h"

const char* NiceStringTester::DEFAULT_BANNED_SEQUENCES[] = {"ab", "cd", "pq", "xy"};

const bool NiceStringTester::isStringNice(const char *string) {
	if (string == nullptr || *string == 0) {
		_lastError = K_BAD_STRING;
		return false;
	}
	else {
		_lastError = K_SUCCESS;
	}

	if (_testFlags & K_VOWEL_COUNT) hasEnoughVowels(string);
	if (_testFlags & K_CONSECUTIVE_LETTERS) hasConsecutiveLetters(string);
	if (_testFlags & K_BANNED_SEQUENCES) hasBannedSequence(string);
	if (_testFlags & K_REPEATED_PAIR) hasSplitRepeatedLetter(string);
	if (_testFlags & K_SPLIT_REPEAT_LETTER) hasRepeatedPair(string);
	
	return _lastError == K_SUCCESS;
}

const bool NiceStringTester::hasEnoughVowels(const char *string) {
	unsigned vowelCount = 0;
	
	for (/*empty*/; *string != 0; ++string) {
		if (_vowelCount > 0) {
			switch (*string) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				++vowelCount;
			default:
				break;
			}
		}
	}

	if (vowelCount < _vowelCount) {
		_lastError |= K_VOWEL_COUNT;
		return false;
	}
	
	return true;
}

const bool NiceStringTester::hasConsecutiveLetters(const char *string) {
	unsigned repeatLettersCount = 1;
	unsigned mostRepeatedLetters = 1;
	char lastChar = 0;

	for (/*empty*/; *string != 0; ++string) {
		if (_repeatCount > 0) {
			if (*string == lastChar) {
				++repeatLettersCount;
				if (repeatLettersCount > mostRepeatedLetters) {
					mostRepeatedLetters = repeatLettersCount;
				}
			}
			else {
				repeatLettersCount = 1;
			}
		}
		lastChar = *string;
	}

	if (mostRepeatedLetters < _repeatCount) {
		_lastError |= K_CONSECUTIVE_LETTERS;
		return false;
	}
	
	return true;
}

const bool NiceStringTester::hasBannedSequence(const char *string) {
	for (/*empty*/; *string != 0; ++string) {
		for (unsigned i = 0; i < _bannedSequenceCount; ++i) {
			const char *bannedSequence = _bannedSequences[i];
			const char *subString = string;
			for (/*empty*/; *bannedSequence == *subString; ++bannedSequence, ++subString) {
				// Will also prevent hitting the end of subString
				if (*(bannedSequence+1) == 0) {
					_lastError |= K_BANNED_SEQUENCES;
					return true;
				}
			}
		}
	}

	return false;
}

const bool NiceStringTester::hasRepeatedPair(const char *string) {
	char lastChar = 0;
	for (/*empty*/; *string && *(string+1); ++string) {
		for (const char *subString = string+2; *subString && (*subString+1); ++subString) {
			if (*string == *subString && *(string+1) == *(subString+1)) {
				return true;
			}
		}
	}

	_lastError |= K_REPEATED_PAIR;
	return false;
}

const bool NiceStringTester::hasSplitRepeatedLetter(const char *string) {
	if (*string && *(string+1)) {
		++string;
		for (/*empty*/; *(string+1) != 0; ++string) {
			if (*(string-1) == *(string+1)) {
				return true;
			}
		}
	}

	_lastError |= K_SPLIT_REPEAT_LETTER;
	return false;
}
