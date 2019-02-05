#include "computerplayer.h"

std::pair<int, int> computerPlayer::makeRawDecision(const std::array<Cell, 100> & enemyField){
    srand(static_cast<unsigned>(time(nullptr)));
    std::pair<int, int> coordinates;
    unsigned x, y;
    do {
        x = rand() % 10;
        y = rand() % 10;
    } while (enemyField[10 * y + x] != Cell::CL_CLEAR);
    coordinates.first = x;
    coordinates.second = y;

    return coordinates;
}

std::pair<int,int> makeReasonDecision(const std::array<Cell, 100> & enemyField,
                                                std::pair<int,int> point){

}
