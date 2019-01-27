#pragma once

#include <cstdio>
#include<vector>
#include "pack.h"

class Hand {
public:
	void clear() {
		cards.clear();
		sum = 0;
	}
	int takeCard(Pack &pack) {
		Card card = pack.getCard();
		cards.push_back(card);
		sum += card.weight;
		return card.weight;
	}
	int getSum() {
		return sum;
	}
private:
	int sum = 0;
	std::vector<Card> cards;
};