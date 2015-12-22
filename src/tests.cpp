#include "tests.h"
#include <iostream>
#include "util.h"
#include "FloorParser.h"
#include "Present.h"
#include "DeliveryParser.h"
#include "AdventCoinMiner.h"
#include "NiceStringTester.h"
#include <fstream>
#include "LightController.h"
#include "WireKit.h"

bool test01() {
	bool isOK = test01_1();
	isOK &= test01_2();
	char* buffer = readFile("res/input_01_1.txt");
	if (buffer != nullptr) {
		FloorParser fp;
		std::cout << "Answer (01.1): Santa should go to floor " << fp.getFinalFloor(buffer) << std::endl;
		std::cout << "Answer (01.2): Santa enters the basement at " << fp.getFloorIndex(buffer, -1) << std::endl;

		delete [] buffer;
	}

	return isOK;
}

bool test01_1() {
	char *input[] = {
		"(())",
		"()()",
		"(((",
		"(()(()(",
		"))(((((",
		"())",
		"))(",
		")))",
		")())())"
	};

	int output[] = {
		0, 0, 3, 3, 3, -1, -1, -3, -3
	};

	int length = arraySize(input);

	FloorParser fp;
	bool isOK = true;
	std::cout << "Test: FloorParser::getFinalFloor()" << std::endl;
	for (int i = 0; i < length; ++i) {
		int result = fp.getFinalFloor(input[i]);
		bool passed = result == output[i];
		std::cout << "  " << passed << ": getFinalFloor(\"" << input[i] << "\") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;
	}

	return isOK;
}

bool test01_2() {
	char *input[] = {
		")",
		"()())",
	};

	int output[] = {
		1, 5
	};

	int length = arraySize(input);

	FloorParser fp;
	bool isOK = true;
	std::cout << "Test: FloorParser::getFloorIndex()" << std::endl;
	for (int i = 0; i < length; ++i) {
		int result = fp.getFloorIndex(input[i], -1);
		bool passed = result == output[i];
		std::cout << "  " << passed << ": getFloorIndex(\"" << input[i] << "\") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;
	}

	return isOK;
}

////////////////////////////////////////////////////////////////////////////////
bool test02() {
	bool isOK = test02_1();
	isOK &= test02_2();

	int wrappingPaperRequired = 0;
	int ribbonRequired = 0;
	std::vector<Present*>* presents = Present::createPresentsFromFile("res/input_02_1.txt");
	for (auto present = presents->begin(); present != presents->end(); ++present) {
		wrappingPaperRequired += (*present)->getWrappingPaperRequired();
		ribbonRequired += (*present)->getRibbonRequired();
		delete (*present);
	}

	// Are individual presents deleted? Double delete? We'll find out!
	delete presents;

	std::cout << "Answer (02.1): The Elves need " << wrappingPaperRequired << " sqft of wrapping paper" << std::endl;
	std::cout << "Answer (02.2): The Elves need " << ribbonRequired << " feet of ribbon" << std::endl;

	return isOK;
}

bool test02_1() {
	int input[] = {
		2, 3, 4,
		1, 1, 10
	};

	int output[] = {
		58, 43
	};

	int length = arraySize(output);

	bool isOK = true;
	std::cout << "Test: Present::getWrappingPaperRequired()" << std::endl;
	for (int i = 0; i < length; ++i) {
		int index = i * 3;
		Present p(input[index], input[index+1], input[index+2]);
		int result = p.getWrappingPaperRequired();
		bool passed = result == output[i];
		std::cout << "  " << passed << ": getWrappingPaperRequired(" << input[index] << ", " << input[index+1] << ", " << input[index+2] << ") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;
	}

	return isOK;
}

bool test02_2() {
	int input[] = {
		2, 3, 4,
		1, 1, 10
	};

	int output[] = {
		34, 14
	};

	int length = arraySize(output);

	bool isOK = true;
	std::cout << "Test: Present::getRibbonRequired()" << std::endl;
	for (int i = 0; i < length; ++i) {
		int index = i * 3;
		Present p(input[index], input[index+1], input[index+2]);
		int result = p.getRibbonRequired();
		bool passed = result == output[i];
		std::cout << "  " << passed << ": getRibbonRequired(" << input[index] << ", " << input[index+1] << ", " << input[index+2] << ") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;
	}

	return isOK;
}

////////////////////////////////////////////////////////////////////////////////
bool test03() {
	bool isOK = test03_1();
	isOK &= test03_2();

	DeliveryParser dp;
	const char * input = readFile("res/input_03_1.txt");
	auto houses = dp.createDeliveryList(input);

	std::cout << "Answer (03.1): Santa visits " << houses->size() << " houses" << std::endl;

	deleteVector(houses);

	houses = dp.createDeliveryList(input, 2);
	std::cout << "Answer (03.2): Santas visit " << houses->size() << " houses" << std::endl;

	delete [] input;

	return isOK;
}

bool test03_1() {
	char *input[] = {
		">",
		"^>v<",
		"^v^v^v^v^v"
	};

	int output[] = {
		2, 4, 2
	};

	int length = arraySize(input);

	DeliveryParser dp;
	bool isOK = true;
	std::cout << "Test: DeliveryParser::getHousesVisited()" << std::endl;
	for (int i = 0; i < length; ++i) {
		auto houses = dp.createDeliveryList(input[i]);
		int result = houses->size();
		bool passed = result == output[i];
		std::cout << "  " << passed << ": getHousesVisited(\"" << input[i] << "\") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;

		deleteVector(houses);
	}

	return isOK;
}

bool test03_2() {
	char *input[] = {
		"^v",
		"^>v<",
		"^v^v^v^v^v"
	};

	int output[] = {
		3, 3, 11
	};

	int length = arraySize(input);

	DeliveryParser dp;
	bool isOK = true;
	std::cout << "Test: DeliveryParser::getHousesVisited(2 Santas)" << std::endl;
	for (int i = 0; i < length; ++i) {
		auto houses = dp.createDeliveryList(input[i], 2);
		int result = houses->size();
		bool passed = result == output[i];
		std::cout << "  " << passed << ": getHousesVisited(\"" << input[i] << "\") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;

		deleteVector(houses);
	}

	return isOK;
}

////////////////////////////////////////////////////////////////////////////////
bool test04() {
	bool isOK = test04_1();

	AdventCoinMiner miner;
	unsigned myValue = miner.mineWithKey();

	std::cout << "Answer (04.1): My key pairs with " << myValue << std::endl;

	AdventCoinMiner deepMiner("000000");
	myValue = deepMiner.mineWithKey();

	std::cout << "Answer (04.2): My key pairs with (six zeroes) " << myValue << std::endl;

	return isOK;
}

bool test04_1() {
	char *input[] = {
		"abcdef",
		"pqrstuv",
	};

	int output[] = {
		609043, 1048970
	};

	// Note[] = {
	// 000001dbbfa...
	// 000006136ef...

	int length = arraySize(input);

	bool isOK = true;
	AdventCoinMiner miner;
	std::cout << "Test: AdventCoinMiner::mineWithKey()" << std::endl;
	for (int i = 0; i < length; ++i) {
		unsigned result = miner.mineWithKey(input[i]);
		bool passed = result == output[i];
		std::cout << "  " << passed << ": mineWithKey(\"" << input[i] << "\") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;
	}

	return isOK;
}

////////////////////////////////////////////////////////////////////////////////
bool test05() {
	bool isOK = test05_1();
	isOK |= test05_2();

	NiceStringTester testers[2];
	testers[0].setupFirstRoundTests();
	testers[1].setupSecondRoundTests();
	int niceStringCount[2] = {0};
	std::ifstream file("res/input_05.txt");
	if (file.is_open()) {
		while (file.peek() != EOF) {
			char buffer[20] = {0};
			file.getline(buffer, 20);
			if (testers[0].isStringNice(buffer)) ++(niceStringCount[0]);
			if (testers[1].isStringNice(buffer)) ++(niceStringCount[1]);
		}
	}
	std::cout << "Answer (05.1): There are " << niceStringCount[0] << " nice strings" << std::endl;
	std::cout << "Answer (05.2): There are " << niceStringCount[1] << " nice strings" << std::endl;

	return isOK;
}

bool test05_1() {
	char *input[] = {
		"ugknbfddgicrmopn",
		"aaa",
		"jchzalrnumimnmhp",
		"haegwjzuvuyypxyu",
		"dvszwmarrgswjxmb",
	};

	int output[] = {
		NiceStringTester::K_SUCCESS,
		NiceStringTester::K_SUCCESS,
		NiceStringTester::K_CONSECUTIVE_LETTERS,
		NiceStringTester::K_BANNED_SEQUENCES,
		NiceStringTester::K_VOWEL_COUNT
	};

	int length = arraySize(input);

	bool isOK = true;
	NiceStringTester tester;
	tester.setupFirstRoundTests();
	std::cout << "Test: NiceStringTester::isStringNice()" << std::endl;
	for (int i = 0; i < length; ++i) {
		tester.isStringNice(input[i]);
		unsigned result = tester.getLastError();
		bool passed = result == output[i];
		std::cout << "  " << passed << ": isStringNice(\"" << input[i] << "\") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;
	}

	return isOK;
}

bool test05_2() {
	char *input[] = {
		"qjhvhtzxzqqjkmpb",
		"xxyxx",
		"uurcxstgmygtbstg",
		"ieodomkazucvgmuy",
	};

	int output[] = {
		NiceStringTester::K_SUCCESS,
		NiceStringTester::K_SUCCESS,
		NiceStringTester::K_SPLIT_REPEAT_LETTER,
		NiceStringTester::K_REPEATED_PAIR,
	};

	int length = arraySize(input);

	bool isOK = true;
	NiceStringTester tester;
	tester.setupSecondRoundTests();
	std::cout << "Test: NiceStringTester::isStringNice()" << std::endl;
	for (int i = 0; i < length; ++i) {
		tester.isStringNice(input[i]);
		unsigned result = tester.getLastError();
		bool passed = result == output[i];
		std::cout << "  " << passed << ": isStringNice(\"" << input[i] << "\") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;
	}

	return isOK;
}

////////////////////////////////////////////////////////////////////////////////
bool test06() {
	LightController lc;
	lc.parseFile("res/input_06.txt");
	std::cout << "Answer (06.1): There are " << lc.getLitCount() << " lights on" << std::endl;

	LightController lcInc(LightController::K_INCREMENTAL);
	lcInc.parseFile("res/input_06.txt");
	std::cout << "Answer (06.2): The lights are at " << lcInc.getBrightness() << " total brightness" << std::endl;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool test07() {
	bool isOK = test07_1();
	isOK &= test07_2();

	WireKit wk;
	wk.parseFile("res/input_07.txt");
	std::cout << "Answer (07.1): Wire 'a' carries a signal of " << wk.getWireValue("a") << std::endl;

	std::stringstream copyAtoB;
	copyAtoB << wk.getWireValue("a") << " -> b";
	wk.processInstruction(copyAtoB);
	wk.reset();
	std::cout << "Answer (07.2): Wire 'a' now carries a signal of " << wk.getWireValue("a") << std::endl;

	wk.clear();

	return true;
}

bool test07_1() {
	std::string input[] = {
		"123 -> x",
		"1 -> y",
		"x AND y -> z",
		"z LSHIFT 2 -> q",
		"NOT x -> f",
	};

	uint16_t output[] = {
		123,
		1,
		1,
		4,
		65535 - 123
	};

	const char *keys[] = {
		"x",
		"y",
		"z",
		"q",
		"f"
	};

	int length = arraySize(input);

	bool isOK = true;
	WireKit wk;
	std::cout << "Test: WireKit::processInstruction()" << std::endl;
	for (int i = 0; i < length; ++i) {
		wk.processInstruction(std::stringstream(input[i]));
		uint16_t result = wk.getWireValue(keys[i]);
		bool passed = result == output[i];
		std::cout << "  " << passed << ": processInstruction(\"" << input[i] << "\") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;
	}

	return isOK;
}

bool test07_2() {
	std::string input[] = {
		"123 -> xx",
		"456 -> yy",
		"xx AND yy -> dd",
		"xx OR yy -> ee",
		"xx LSHIFT 2 -> ff",
		"yy RSHIFT 2 -> gg",
		"NOT xx -> hh",
		"NOT yy -> ii",
		"NOT gg -> kk"
	};

	uint16_t output[] = {
		72,
		507,
		492,
		114,
		65412,
		65079,
		123,
		456,
		~(456 >> 2)
	};

	const char *keys[] = {
		"dd",
		"ee",
		"ff",
		"gg",
		"hh",
		"ii",
		"xx",
		"yy",
		"kk"
	};

	int length = arraySize(input);

	bool isOK = true;
	WireKit wk;
	std::cout << "Test: WireKit::getWireValue()" << std::endl;
	for (int i = 0; i < length; ++i) {
		wk.processInstruction(std::stringstream(input[i]));
	}
	for (int i = 0; i < length; ++i) {
		uint16_t result = wk.getWireValue(keys[i]);
		bool passed = result == output[i];
		std::cout << "  " << passed << ": getWireValue(\"" << keys[i] << "\") -> " << result << " (" << output[i] << ")" << std::endl;
		isOK &= passed;
	}

	wk.print();

	return isOK;
}
