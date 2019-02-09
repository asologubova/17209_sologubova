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
    int numOfShips;
    std::array<Cell, 100> field;
    std::vector<_Ship> ships;

    void killFrameCells(const _Ship & s);

public:
    Field();
    int getNumOfShips();
    bool setShip(int x, int y, const Ship & ship, ShipPosition pos);
    void autoPlaceShips();
    char shoot(int x, int y);//0 - без попаданий, 1 - ранил, 2 - убил
    void clear();//очистка поля от всех кораблей
    const std::array<Cell, 100> & getFieldInstance() const;
};

#endif // FIELD_H
