#ifndef PLAYER_H
#define PLAYER_H

#include <array>


class Player
{
    std::array<bool, 100> playersBoard;
    std::array<bool, 100> enemysBoard;
public:
    Player();
};

#endif // PLAYER_H
