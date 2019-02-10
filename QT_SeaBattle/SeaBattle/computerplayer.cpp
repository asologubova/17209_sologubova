#include "computerplayer.h"

std::pair<int, int> computerPlayer::makeRawDecision(const std::array<Cell, 100> & enemyField){
    srand(static_cast<unsigned>(time(nullptr)));
    std::pair<int, int> coordinates;
    int x, y;
    do {
        x = rand() % 10;
        y = rand() % 10;
    } while (enemyField[10 * y + x] == Cell::CL_DOT ||
             enemyField[10 * y + x] == Cell::CL_HALF ||
             enemyField[10 * y + x] == Cell::CL_FULL);
    coordinates.first = x;
    coordinates.second = y;

    return coordinates;
}

std::pair<int,int> computerPlayer::makeReasonDecision(const std::array<Cell, 100> & enemyField,
                                                std::vector<std::pair<int,int>> & shootedPoints){
    srand(static_cast<unsigned>(time(nullptr)));
    std::pair<int, int> coordinates;
    int x, y;

    //пишем тут
    //если раненая точка одна - смотрим вокруг нее
    //если больше - выбираем один из концов и стреляем в него (один из концов уже может не подходить)
    //+как-то учесть положение корабля (вертикальный / горизонтальный)

    coordinates.first = x;
    coordinates.second = y;

    return coordinates;
}
