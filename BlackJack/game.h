#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "pack.h"
#include "hand.h"
#include "strategy.h"
#include "factory.h"

enum class Mode : char {
	DETAILED,
	FAST,
	TOURNAMENT
};

class Game {
	Mode gameMode;
	size_t stratsCount;
	std::string path;
	
public:
	void treatData(int argc, const char** rawData);
	void fullStrats();
	std::vector<std::string> IDs;
	std::vector<Hand> hands;
	std::vector<Strategy*> strategies;
	std::vector<bool> inGame;

	Game(int n, const char** rawData) {
		stratsCount = 0;
		gameMode = Mode::DETAILED;
		treatData(n, rawData);
		fullStrats();
	}
};
