#include <cstdio>
#include<vector>
#include "pack.h"
//#include "strategy.h"

class Hand {
public:


	unsigned char sum = 0;
	std::vector<Card> cards;
	void clear() {
		cards.clear();
		sum = 0;
	}
	void takeCard(Pack &pack) {
		cards.push_back(pack.getCard());
		sum += cards.back().weight;
	}
};