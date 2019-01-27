#include <cstdlib>
#include <iostream>

#include "pack.h"
#include "game.h"
#include "factory.h"
#include "strategy.h"

int main(int argc, char **argv) {
	//std::vector<Strategy*> strats;
	//Factory<std::string, Strategy> * f = Factory<std::string, Strategy>::getInstance();
	//std::vector<std::string> IDs;

	Game BlackJack(argc, const_cast<const char**>(argv));
}