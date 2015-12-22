#include "AdventCoinMiner.h"
#include <cstdio>
#include "md5.h"

unsigned AdventCoinMiner::mineWithKey(const char *key) {
	_key = key;

	unsigned postfix = 1;
	std::string target(_targetPrefix);
	while (postfix != 0) {
		std::string attempt(key);
		char value[11] = {0};
		sprintf(value, "%d", postfix);
		attempt += value;
		std::string hash = md5(attempt);

		int test = hash.compare(0, target.length(), target);
		if (test == 0) {
			_postfix = postfix;
			_hash = hash;
			break;
		}
		
		++postfix;
	}

	return postfix;
}
