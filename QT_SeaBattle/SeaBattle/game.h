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

class Game
{
    //Field f1, f2; // сделать в поле подсчет кораблей
    //computerPlayer Player1, Player2;
public:
    GameStatus status;
    Game();
    //void doGame();
    //const std::array<Cell, 100> & getEnemyField(int k);
    bool checkPlacing(const std::array<Cell, 100> & fld) const;
};

#endif // GAME_H
