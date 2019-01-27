#ifndef SHIP_H
#define SHIP_H

#include <array>

enum ShipState {
    ALIVE,
    DESTROYED
};

class Ship
{
public:
    Ship(unsigned rk = 1);//аргумент - ранг создаваемого корабля

    unsigned getRank() const;
    void shoot(unsigned num);
    //num - номер палубы (отсчёт от нуля);
    //вызывающий должен гарантировать, что num <= rank
    bool isAlive();

private:
    unsigned rank;
    std::array<ShipState, 4> state;
    //состояние каждой палубы; размер массива - всегда 4,
    //используются только первые rank элементов
    bool alive;
};

#endif // SHIP_H
