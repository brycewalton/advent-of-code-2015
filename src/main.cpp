#include <iostream>
#include "tests.h"
#include "md5.h"

int main (void) {
	
	std::cout << "Advent of Code" << std::endl;

	test01();
	test02();
	//test03(); // This test is awfully slow - could refactor for fun?
	//test04(); // This test will always be slow - could try programming md5 myself
	test05();
	test06();
	test07();

	int pauser = 0;
	std::cin >> pauser;

	return 0;
}