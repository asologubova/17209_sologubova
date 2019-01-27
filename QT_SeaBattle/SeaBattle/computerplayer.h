#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <array>
#include <ctime>

#include "cell.h"

class computerPlayer
{
public:
    std::pair<unsigned,unsigned> makeRawDecision(std::array<Cell, 100> enemyField);
};

#endif // COMPUTERPLAYER_H
