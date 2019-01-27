#pragma once

#include "strategy.h"
#include "factory.h"

class Strat1 : public Strategy {
public:
	bool makeDecision(const Hand & hand) override {
		int sum = hand.getSum();   //врн ме рюй? ашкн ф мнпл
		return (sum < 15);
	}
};


const Strategy *newStrat1() {
	return new Strat1;
}
bool isRegistered = Factory<std::string, Strategy>::getInstance()
->registerStrategy("strat1", newStrat1);