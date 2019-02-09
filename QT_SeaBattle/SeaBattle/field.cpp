#include "field.h"

Field::Field()
{
    for (int i = 0; i < 100; i++){
        field[i] = Cell::CL_CLEAR;
    }
    numOfShips = 10;
}

bool Field::setShip(int x, int y, const Ship & ship, ShipPosition pos){
    int rk = ship.getRank();
    _Ship s;
    std::vector<std::pair<int, int>> shipsCoord;
    std::pair<int, int> coord;

    switch(pos){
    case ShipPosition::HORIZONTAL:
        if ((x + rk - 1) >= 10) return false;
        for (int i = 0; i < rk; i++){ //проверка на занятость квадрата 3*3
            int _x = x + i;
            for (int j = -1; j < 2; j++)
                for (int k = -1; k < 2; k++){
                    int c = 10 * (y + j) + _x + k;
                    if (c >= 0 && c < 100)
                        if (field[c] == Cell::CL_SHIP) return false;
                        //много раз проходим по одним и тем же клеткам...
                }
        }
        for (int i = 0; i < rk; i++){
            field[10 * y + x + i] = Cell::CL_SHIP;
            coord.first = x + i;
            coord.second = y;
            shipsCoord.push_back(coord);
        }
        break;

    case ShipPosition::VERTICAL:
        if ((y + rk - 1) >= 10) return false;
        for (int i = 0; i < rk; i++){ //проверка на занятость квадрата 3*3
            int _y = y + i;
            for (int j = -1; j < 2; j++)
                for (int k = -1; k < 2; k++){
                    int c = 10 * (_y + j) + x + k;
                    if (c >= 0 && c < 100)
                        if (field[c] == Cell::CL_SHIP) return false;
                }
        }
        for (int i = 0; i < rk; i++){
            field[10 * (y + i) + x] = Cell::CL_SHIP;
            coord.first = x;
            coord.second = y + i;
            shipsCoord.push_back(coord);
        }
        break;

    }
    s.ship = ship;
    s.coordinates = shipsCoord;
    ships.push_back(s);
    return true;
}

void Field::autoPlaceShips(){
    srand(static_cast<unsigned>(time(nullptr)));
    std::array<int, 10> arr = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    bool ok = false;

    ShipPosition pos = ShipPosition::HORIZONTAL;
    for (int i = 0; i < 10; i++){
        ok = false;
        Ship sh(arr[i]);
        while (!ok) {
            int x = rand() % 10;
            int y = rand() % 10;
            ok = setShip(x, y, sh, pos);
            if(!ok){
                pos = ((pos == ShipPosition::HORIZONTAL) ? ShipPosition::VERTICAL : ShipPosition::HORIZONTAL);
                ok = setShip(x, y, sh, pos);
            }
        }
    }
}

char Field::shoot(int x, int y){
    size_t coord = 10 * (y - 1) + x;
    if (field[coord] == Cell::CL_DOT || field[coord] == Cell::CL_HALF)  return 0;

    field[coord] = Cell::CL_DOT;
    if (field[coord] == Cell::CL_SHIP){
        field[coord] = Cell::CL_HALF;
        //Если убили весь корабль - обрисовать его иначе
        for (int i = 0; i < ships.size(); i++){
            for (int j = 0; j < ships[i].coordinates.size(); j++){
                if (ships[i].coordinates[j].first == x && ships[i].coordinates[j].second == y)
                  ships[i].ship.shoot(j);
                if (!ships[i].ship.isAlive()){
                    killFrameCells(ships[i]);
                    numOfShips--;
                    return 2;
                    //(В ИГРЕ) УМЕНЬШИТЬ СЧЕТЧИК КОРАБЛЕЙ, ЕСЛИ СЧЕТЧИК == 0 - КОНЕЦ
                }
            }
        }
    }
    return 1;
}

void Field::clear(){
    for(Cell it : field)
        it = Cell::CL_CLEAR;
}

const std::array<Cell, 100> & Field::getFieldInstance() const{
    return field;
}

void Field::killFrameCells(const _Ship & s){ // в случае смерти всего корабля
    for (unsigned i = 0; i < s.ship.getRank(); i++){
        unsigned _x = s.coordinates[i].first;
        unsigned _y = s.coordinates[i].second;
        for (int j = -1; j < 2; j++)
            for (int k = -1; k < 2; k++){
                int c = 10 * (_y + j) + _x + k;
                if (c >= 0 && c < 100){
                    if (field[c] == Cell::CL_CLEAR) field[c] = Cell::CL_DOT;
                    else if (field[c] == Cell::CL_HALF) field[c] = Cell::CL_FULL;
                }

            }
    }
}

int Field::getNumOfShips(){
    return numOfShips;
}
