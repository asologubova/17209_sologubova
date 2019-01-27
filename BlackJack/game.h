#pragma once

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include <conio.h>

#include "pack.h"
#include "hand.h"
#include "strategy.h"
#include "factory.h"

//bool compareStrings(std::string str1, std::string str2, int n);

//enum class Mode : char {
enum Mode {
	DETAILED,
	FAST,
	TOURNAMENT
};

struct Gamer {
	std::string ID = "";
	std::string name = ""; //ЗАПОЛНИТЬ!
	Hand hand;
	Strategy* strat;
	bool inGame = false;
};

class Game {
public:
	Game(int n, const char** rawData);
	void doGame();

	std::vector<Gamer> gamers;

private:
	void fullStrats();
	void treatData(int n, const char** rawData);

private:
	std::vector<std::string> IDs;
	Mode gameMode;
	size_t gamersCount;
	std::string filePath;
	Pack pack;          //Как это будет зависеть от N? 
};
