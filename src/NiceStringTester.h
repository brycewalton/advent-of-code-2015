#ifndef NICE_STRING_TESTER_H
#define NICE_STRING_TESTER_H

class NiceStringTester {

public:

	enum Test_Flags {
		K_SUCCESS							= 0,
		K_BAD_STRING					= 1 << 0, // 1
		K_VOWEL_COUNT					= 1 << 1, // 2
		K_CONSECUTIVE_LETTERS = 1 << 2, // 4
		K_BANNED_SEQUENCES		= 1 << 3, // 8
		K_REPEATED_PAIR				= 1 << 4, // 16
		K_SPLIT_REPEAT_LETTER = 1 << 5, // 32
	};

	NiceStringTester() :
		_vowelCount(0),
		_repeatCount(0),
		_bannedSequenceCount(0),
		_bannedSequences(nullptr),
		_testFlags(0),
		_lastError(0)
		{}

	const NiceStringTester& setupVowelCountTest(unsigned vowelCount = 3) {
		_vowelCount = vowelCount;
		_testFlags |= K_VOWEL_COUNT;
		return *this;
	}
	const NiceStringTester& setupConsecutiveLettersTest(unsigned repeatCount = 2) {
		_repeatCount = repeatCount;
		_testFlags |= K_CONSECUTIVE_LETTERS;
		return *this;
	}
	const NiceStringTester& setupBannedSequenceTest(unsigned bannedSequenceCount = 4, const char** bannedSequences = DEFAULT_BANNED_SEQUENCES) {
		_bannedSequenceCount = bannedSequenceCount;
		_bannedSequences = bannedSequences;
		_testFlags |= K_BANNED_SEQUENCES;
		return *this;
	}
	const NiceStringTester& setupRepeatPairTest() {
		_testFlags |= K_REPEATED_PAIR;
		return *this;
	}
	const NiceStringTester& setupSplitRepeatLetterTest() {
		_testFlags |= K_SPLIT_REPEAT_LETTER;
		return *this;
	}
	const NiceStringTester& setupClear() {
		_testFlags = 0;
		return *this;
	}

	const NiceStringTester& setupFirstRoundTests() {
		setupClear();
		setupVowelCountTest();
		setupConsecutiveLettersTest();
		setupBannedSequenceTest();
		return *this;
	}

	const NiceStringTester& setupSecondRoundTests() {
		setupClear();
		setupRepeatPairTest();
		setupSplitRepeatLetterTest();
		return *this;
	}

	const bool isStringNice(const char *string);
	
	inline const int getLastError() {
		return _lastError;
	}

private:
	unsigned _vowelCount;
	unsigned _repeatCount;
	unsigned _bannedSequenceCount;
	const char** _bannedSequences;

	int _testFlags;
	int _lastError;

	const bool hasEnoughVowels(const char *string);
	const bool hasConsecutiveLetters(const char *string);
	const bool hasBannedSequence(const char *string);

	const bool hasRepeatedPair(const char *string);
	const bool hasSplitRepeatedLetter(const char *string);


	static const char* DEFAULT_BANNED_SEQUENCES[];
};

#endif