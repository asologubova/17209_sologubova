#ifndef FIELD_H
#define FIELD_H

#include <array>
#include <vector>

#include "cell.h"
#include "ship.h"

enum ShipPosition {
    VERTICAL,
    HORIZONTAL
};

struct _Ship {
    Ship ship;
    std::vector<std::pair<int, int>> coordinates;//координаты x, y
};

class Field {
public:
    Field();

    bool setSheep(int x, int y, const Ship & ship, ShipPosition pos);
    bool shoot(int x, int y);//true - если было попадание; false - иначе
    void clear();//очистка поля от всех кораблей

private:
// struct _Ship;
// const std::array<Ship, 10> all_ships =
// {1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
// массив из всех кораблей, которые должны быть расставленны

private:
    std::array<Cell, 100> field;
    std::vector<_Ship> ships;

    //const int weight = 10;
    //const int height = 10;
};



#endif // FIELD_H
