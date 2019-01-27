#ifndef SHIP_H
#define SHIP_H

#include <array>

enum class ShipState : bool {
    ALIVE,
    DESTROYED
};

class Ship
{
public:
    Ship(int rk);//аргумент - ранг создаваемого корабля

    int getRank() const;
    void shoot(int num);
    //num - номер палубы (отсчёт от нуля);
    //вызывающий должен гарантировать, что num <= rank
    bool isAlive();

private:
    int rank;
    std::array<ShipState, 4> state;
    //состояние каждой палубы; размер массива - всегда 4,
    //используются только первые rank элементов
    bool alive;
};

#endif // SHIP_H
