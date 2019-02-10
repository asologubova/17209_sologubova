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
    Ship(int rk = 1);//аргумент - ранг создаваемого корабля

    int getRank() const;
    const std::array<ShipState, 4> & getStates() const;
    void shoot(int num);
    //num - номер палубы (отсчёт от нуля);
    //вызывающий должен гарантировать, что num <= rank
    bool isAlive() const;

private:
    int rank;
    std::array<ShipState, 4> state;
    //состояние каждой палубы; размер массива - всегда 4,
    //используются только первые rank элементов
    bool alive;
};

#endif // SHIP_H
