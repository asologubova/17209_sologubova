#include "game.h"

Game::Game(int n, const char** rawData) {
	gamersCount = 0;
	gameMode = Mode::DETAILED;
	treatData(n, rawData);
	fullStrats();
	//int N;
	//pack(N);

}

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

			filePath.resize(std::strlen(rawData[i]) - 10);
			std::copy(&rawData[i][10], &rawData[i][std::strlen(rawData[i])], filePath.begin());
		}
		else
			IDs.push_back(rawData[i]);
	}
}

void Game::fullStrats() {
	//std::vector<Strategy*> strats;
	Factory<std::string, Strategy> * f = Factory<std::string, Strategy>::getInstance();
	Strategy *str;
	for (size_t i = 0; i < IDs.size(); i++) {
		str = f->createStrategyByID(IDs[i]);
		if (str) {
			gamers[i].strat = str;
			gamers[i].inGame = true;
			gamersCount++;
		}
	}
}

//***********************************************

void Game::doGame() {
	std::vector<Gamer> winners;
	size_t i = 0, j = 0;
	size_t gameIsOn = gamersCount;
	int takedCard;
	bool decision;
	int maxScore = 0, sum;

	switch (gameMode) {
	case DETAILED:
		while (gameIsOn) {
			for (; i < gamersCount; i++) {
				if (_kbhit()) {
					if (!gamers[i].inGame) continue;
					takedCard = gamers[i].hand.takeCard(pack);
					decision = gamers[i].strat->makeDecision(gamers[i].hand);
					std::cout << "*****************" << std::endl;
					std::cout << "Gamer is " << gamers[i].name << std::endl;
					std::cout << "Total score: " << gamers[i].hand.getSum() << std::endl;
					if (!decision) {
						gameIsOn--;
						gamers[i].inGame = false;
						std::cout << "This gamer finished the game." << std::endl;
					}
				}
			}
		}
		for (i = 0; i < gamersCount; i++) {
			sum = gamers[i].hand.getSum();
			if (sum > maxScore) maxScore = sum;
		}
		for (i = 0; i < gamersCount; i++) {
			sum = gamers[i].hand.getSum();
			if (sum == maxScore) winners.push_back(gamers[i]);
		}
		for (i = 0; i < winners.size(); i++) {
			std::cout << "* Winner is " << gamers[i].name << "! *" << std::endl;
			std::cout << "Total score: " << winners[i].name << std::endl << std::endl;
		}

	case FAST:

	case TOURNAMENT:
		for (i = 0; i < gamersCount - 1; i++) {
			for (j = 0; j < gamersCount; j++) {

			}
		}
	}
}