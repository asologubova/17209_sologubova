#ifndef FIELD_H
#define FIELD_H

#include <array>
#include <vector>
#include <ctime>

#include "ship.h"

enum class ShipPosition : bool {
    VERTICAL,
    HORIZONTAL
};

enum class Cell{
   CL_CLEAR,
   CL_SHIP,
   CL_DOT,
   CL_HALF,
   CL_FULL
};

struct _Ship {
    Ship ship;
    std::vector<std::pair<int, int>> coordinates;//координаты палуб корабля (x, y)
};

class Field {

private:
    std::array<Cell, 100> field;
    std::vector<_Ship> ships;

    void killFrameCells(const _Ship & s);

public:
    Field();
    bool setShip(int x, int y, const Ship & ship, ShipPosition pos);
    void autoPlaceShips();
    bool shoot(int x, int y);//true - если было попадание; false - иначе
    void clear();//очистка поля от всех кораблей
    const std::array<Cell, 100> & getFieldInstance() const;
};

#endif // FIELD_H
