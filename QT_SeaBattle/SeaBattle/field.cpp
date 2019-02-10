#include "field.h"

Field::Field()
{
    for (int i = 0; i < 100; i++){
        field[i] = Cell::CL_CLEAR;
    }
    numOfShips = 0;
}

bool Field::setShip(int x, int y, const Ship & ship, ShipPosition pos){
    int rk = ship.getRank();
    std::array<ShipState, 4> shipStates = ship.getStates();
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
            if (!ship.isAlive())
                field[10 * y + (x + i)] = Cell::CL_FULL;
            else if (shipStates[i] == ShipState::DESTROYED)
                field[10 * y + (x + i)] = Cell::CL_HALF;
            else field[10 * y + (x + i)] = Cell::CL_SHIP;
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
            if (!ship.isAlive())
                field[10 * (y + i) + x] = Cell::CL_FULL;
            else if (shipStates[i] == ShipState::DESTROYED)
                field[10 * (y + i) + x] = Cell::CL_HALF;
            else field[10 * (y + i) + x] = Cell::CL_SHIP;
            coord.first = x;
            coord.second = y + i;
            shipsCoord.push_back(coord);
        }
        break;

    }
    s.ship = ship;
    s.coordinates = shipsCoord;
    ships.push_back(s);
    if (ship.isAlive()) numOfShips++;
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

    numOfShips = 10;
}

char Field::shoot(int x, int y){
    int coord = 10 * y + x;
    if (field[coord] == Cell::CL_DOT || field[coord] == Cell::CL_HALF || field[coord] == Cell::CL_FULL)  return 3;

    if (!(field[coord] == Cell::CL_SHIP)){
        field[coord] = Cell::CL_DOT;
        return 0;
    }
    field[coord] = Cell::CL_HALF;
    for (int i = 0; i < ships.size(); i++){
        for (int j = 0; j < ships[i].coordinates.size(); j++){
            if (ships[i].coordinates[j].first == x && ships[i].coordinates[j].second == y){
                ships[i].ship.shoot(j);
                if (!ships[i].ship.isAlive()){
                    field[coord] = Cell::CL_FULL;
                    killFrameCells(ships[i]);
                    numOfShips--;
                    return 2;
                }
            }
        }
    }
    return 1;
}

void Field::clear(){
    //for(Cell it : field)
        //it = Cell::CL_CLEAR;
    for (int i = 0; i < 100; i++)
        field[i] = Cell::CL_CLEAR;

    numOfShips = 0;
}

const std::array<Cell, 100> & Field::getFieldInstance() const{
    return field;
}

void Field::killFrameCells(const _Ship & s){ // в случае смерти всего корабля
    for (int i = 0; i < s.ship.getRank(); i++){
        int x = s.coordinates[i].first;
        int y = s.coordinates[i].second;
        for (int j = -1; j < 2; j++)
            for (int k = -1; k < 2; k++){
                if ((y + j) < 10 && (x + k) < 10 && (y + j) >= 0 && (x + k) >= 0){
                    int c = 10 * (y + j) + (x + k);
                    if (c >= 0 && c < 100){
                        if (field[c] == Cell::CL_CLEAR) field[c] = Cell::CL_DOT;
                        else if (field[c] == Cell::CL_HALF) field[c] = Cell::CL_FULL;
                    }
                }
            }
    }
}

void Field::fill(const std::array<Cell, 100> & fld) //Проверить, как работает
{
    clear();
    int count = 0, shipsCount = 0;
    std::array<Cell, 100> tmp = fld;
    ShipPosition pos;

    for (int y = 0; y < 10; y++){
        for (int x = 0; x < 10; x++){
            int c = 10 * y + x;
            if(tmp[c] == Cell::CL_SHIP || tmp[c] == Cell::CL_HALF || tmp[c] == Cell::CL_FULL){
                if((x < 9) && ((tmp[c + 1] == Cell::CL_SHIP) ||
                       (tmp[c + 1] == Cell::CL_HALF) ||
                        (tmp[c + 1] == Cell::CL_FULL))){ // горизонтальный
                    pos = ShipPosition::HORIZONTAL;
                    while ((x + count < 10) &&
                           ((tmp[c + count] == Cell::CL_SHIP) ||
                            (tmp[c + count] == Cell::CL_HALF) ||
                            (tmp[c + count] == Cell::CL_FULL))){
                        tmp[c + count] = Cell::CL_CLEAR;
                        count++;
                    }

                } else { // вертикальный или однопалубный
                    pos = ShipPosition::VERTICAL;
                    while ((y + count < 10) &&
                           ((tmp[c + 10 * count] == Cell::CL_SHIP) ||
                            (tmp[c + 10 * count] == Cell::CL_HALF)||
                            (tmp[c + 10 * count] == Cell::CL_FULL))){
                        tmp[c + 10 * count] = Cell::CL_CLEAR;
                        count++;
                    }
                }

                Ship sh(count);

                for (int i = 0; i < count; i++){
                    if (pos == ShipPosition::HORIZONTAL){
                        if (fld[10 * y + (x + i)] == Cell::CL_FULL || fld[10 * y + (x + i)] == Cell::CL_HALF)
                            sh.shoot(i);
                    }
                    else {
                        if (fld[10 * (y + i )+ x] == Cell::CL_FULL || fld[10 * y + (x + i)] == Cell::CL_HALF)
                            sh.shoot(i);
                    }
                }

                if (sh.isAlive()) shipsCount++;
                setShip(x, y, sh, pos);
                count = 0;
            }
            if (tmp[c] == Cell::CL_DOT) field[c] = Cell::CL_DOT;
            tmp[c] = Cell::CL_CLEAR;
        }
    }
}

int Field::getNumOfShips(){
    return numOfShips;
}
