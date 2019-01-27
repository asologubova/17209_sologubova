#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <array>
#include <ctime>

class computerPlayer
{
public:
    std::pair<unsigned,unsigned> makeDecision(std::array<bool, 100> enemyField);
};

#endif // COMPUTERPLAYER_H
