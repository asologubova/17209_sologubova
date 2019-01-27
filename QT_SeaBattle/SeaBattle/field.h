#ifndef FIELD_H
#define FIELD_H

#include <array>
#include <vector>
#include <ctime>

#include "cell.h"
#include "ship.h"

enum ShipPosition {
    VERTICAL,
    HORIZONTAL
};

struct _Ship {
    Ship ship;
    std::vector<std::pair<unsigned, unsigned>> coordinates;//координаты x, y
};

class Field {
public:
    Field();

    bool setShip(unsigned x, unsigned y, const Ship & ship, ShipPosition pos);
    void autoPlaceShips();
    bool shoot(unsigned x, unsigned y);//true - если было попадание; false - иначе
    void clear();//очистка поля от всех кораблей
    std::array<Cell, 100> getFieldInstance();

private:
// struct _Ship;
// const std::array<Ship, 10> all_ships =
// {1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
// массив из всех кораблей, которые должны быть расставленны

private:
    std::array<Cell, 100> field;
    std::vector<_Ship> ships;

    void killFrameCells(const _Ship & s);
    //const int weight = 10;
    //const int height = 10;
};



#endif // FIELD_H
