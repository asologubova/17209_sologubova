#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <array>
#include <ctime>

enum PlayerStatus
{
    InGAME,
    LOST
};

class computerPlayer
{
    PlayerStatus status;
public:
    computerPlayer();
    void init();
    std::pair<unsigned,unsigned> makeDecision(std::array<bool, 100> enemyField);

};

#endif // COMPUTERPLAYER_H
