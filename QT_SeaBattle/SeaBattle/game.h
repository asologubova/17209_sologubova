#ifndef GAME_H
#define GAME_H

#include "player.h"

enum GameStatus
{
    startNewGame,       // Начать новую игру
    player1Attack,      // Ходит первый игрок
    player2Attack,      // Ходит второй игрок
    endOfGame           // Конец игры
};

class Game
{
    GameStatus status;
public:
    Game();
    void doGame();
};

#endif // GAME_H
