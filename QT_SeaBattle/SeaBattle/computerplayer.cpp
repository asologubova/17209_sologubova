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
                                                const std::array<Cell, 100> & shootedPoints){
    //srand(static_cast<unsigned>(time(nullptr)));
    std::pair<int, int> coordinates;
    //int x, y;

    //пишем тут
    //если раненая точка одна - смотрим вокруг нее
    //если больше - выбираем один из концов и стреляем в него (один из концов уже может не подходить)
    //+как-то учесть положение корабля (вертикальный / горизонтальный)

    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 10; x++){
            if (shootedPoints[10 * y + x] == Cell::CL_HALF){
                if (y > 0 && enemyField[10 * (y - 1) + x] != Cell::CL_HALF &&  //сверху
                        enemyField[10 * (y - 1) + x] != Cell::CL_DOT &&
                        shootedPoints[10 * y + (x - 1)] != Cell::CL_HALF &&
                        shootedPoints[10 * y + (x + 1)] != Cell::CL_HALF){
                    coordinates.first = x;
                    coordinates.second = y - 1;
                    return coordinates;
                }
                else if (x > 0 && enemyField[10 * y + (x - 1)] != Cell::CL_HALF && //слева
                         enemyField[10 * y + (x - 1)] != Cell::CL_DOT &&
                         shootedPoints[10 * (y - 1) + x] != Cell::CL_HALF &&
                         shootedPoints[10 * (y + 1) + x] != Cell::CL_HALF){
                    coordinates.first = x - 1;
                    coordinates.second = y;
                    return coordinates;
                }


                else if (x < 9 && enemyField[10 * y + (x + 1)] != Cell::CL_HALF && //справа
                         enemyField[10 * y + (x + 1)] != Cell::CL_DOT &&
                         shootedPoints[10 * (y - 1) + x] != Cell::CL_HALF &&
                         shootedPoints[10 * (y + 1) + x] != Cell::CL_HALF){
                    coordinates.first = x + 1;
                    coordinates.second = y;
                }


                else if (y < 9 && enemyField[10 * (y + 1) + x] != Cell::CL_HALF && //снизу
                         enemyField[10 * (y + 1) + x] != Cell::CL_DOT &&
                         shootedPoints[10 * y + (x - 1)] != Cell::CL_HALF &&
                         shootedPoints[10 * y + (x + 1)] != Cell::CL_HALF){
                    coordinates.first = x;
                    coordinates.second = y + 1;
                    return coordinates;
                }
            }
        }

//    coordinates.first = x;
//    coordinates.second = y;

    return coordinates;
}
