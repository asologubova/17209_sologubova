#include "computerplayer.h"

std::pair<unsigned, unsigned> computerPlayer::makeDecision(std::array<bool, 100> enemyField){
    srand(static_cast<unsigned>(time(nullptr)));
    std::pair<unsigned, unsigned> coordinates;
    unsigned x, y;
    do {
        x = rand() % 10;
        y = rand() % 10;
    } while (enemyField[10 * y + x]);
    coordinates.first = x;
    coordinates.second = y;

    return coordinates;
}