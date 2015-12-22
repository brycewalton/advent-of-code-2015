#ifndef ADVENT_COIN_MINER_H
#define ADVENT_COIN_MINER_H

#include <string>

class AdventCoinMiner {
public:
	AdventCoinMiner(const char* targetPrefix = "00000") :
		_targetPrefix(targetPrefix)
		{}
	unsigned mineWithKey(const char *key = "ckczppom");

private:
	std::string _targetPrefix;
	std::string _key;
	std::string _hash;
	unsigned _postfix;
};

#endif
