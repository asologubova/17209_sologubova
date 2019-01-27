#ifndef GAME_H
#define GAME_H

#include "computerplayer.h"
#include "field.h"

enum GameStatus
{
    StartNewGame,       // Начать новую игру
    Player1Attack,      // Ходит первый игрок
    Player2Attack,      // Ходит второй игрок
    EndOfGame           // Конец игры
};

//enum PlayerStatus {
//    InGAME,
//    LOST
//};

class Game
{
    GameStatus status;
    //PlayerStatus statusP1, statusP2;
    Field f1, f2;
    computerPlayer Player1, Player2;
public:
    Game();
    void doGame();
    std::array<Cell, 100> getEnemyField(int k);
};

#endif // GAME_H
