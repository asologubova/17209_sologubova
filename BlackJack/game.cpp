#include "game.h"

void Game::treatData(int n, const char** rawData) {
	std::vector<std::string> IDs;
	int i = 0;

	for (i = 0; i < n; i++) {
		if (rawData[i] == "--mode=detailed")
			gameMode = Mode::DETAILED;
		else if (rawData[i] == "--mode=tournament")
			gameMode = Mode::TOURNAMENT;
		else if (rawData[i] == "--mode=fast")
			gameMode = Mode::FAST;
		else if (rawData[i][0] == '-' && rawData[i][1] == '-') {
			//std::string tmp(rawData[i]), templ = "--configs="; // ×Å ÇÀ ÄÈ×Ü?

			if (std::strncmp(rawData[i], "--configs=", 10))
				continue;

			path.resize(std::strlen(rawData[i]) - 10);
			std::copy(rawData[i][10], rawData[i][std::strlen(rawData[i])], path.begin());
		}
		else
			IDs.push_back(rawData[i]);
	}
}

void Game::fullStrats() {
	//std::vector<Strategy*> strats;
	Factory<std::string, Strategy> * f = Factory<std::string, Strategy>::getInstance();
	Strategy *str;
	for (int i = 0; i < IDs.size(); i++) {
		str = f->createStrategyByID(IDs[i]);
		if (str) {
			strategies.push_back(str);
			stratsCount++;
		}
	}
}