#ifndef GAME_H
#define GAME_H

#include "computerplayer.h"

enum GameStatus
{
    StartNewGame,       // Начать новую игру
    Player1Attack,      // Ходит первый игрок
    Player2Attack,      // Ходит второй игрок
    EndOfGame           // Конец игры
};

class Game
{
    GameStatus status;
    computerPlayer Player1;
    computerPlayer Player2;
public:
    Game();
    void doGame();
};

#endif // GAME_H
