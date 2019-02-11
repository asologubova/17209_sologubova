#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <array>
#include <ctime>
#include <field.h> // ??

class computerPlayer
{
public:
    std::pair<int,int> makeRawDecision(const std::array<Cell, 100> & enemyField);
    std::pair<int,int> makeReasonDecision(const std::array<Cell, 100> & enemyField,
                                                    const std::array<Cell, 100> & shootedPoints);
};

#endif // COMPUTERPLAYER_H
