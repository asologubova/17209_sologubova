#include "field.h"

Field::Field()
{

}

bool Field::setShip(unsigned x, unsigned y, const Ship & ship, ShipPosition pos){
    unsigned rk = ship.getRank();
    _Ship s;
    std::vector<std::pair<unsigned, unsigned>> shipsCoord;
    std::pair<unsigned, unsigned> coord;

    switch(pos){
    case HORIZONTAL:
        if ((x + rk - 1) >= 10) return false;
        for (unsigned i = 0; i < rk; i++){ //проверка на занятость квадрата 3*3
            unsigned _x = x + i;
            for (int j = -1; j < 2; j++)
                for (int k = -1; k < 2; k++){
                    int c = 10 * (y + j) + _x + k;
                    if (c >= 0 && c < 100)
                        if (field[c].isBusy()) return false;
                }
        }
        for (unsigned i = 0; i < rk; i++){
            field[10 * y + x + i].setBusy();
            coord.first = x + i;
            coord.second = y;
            shipsCoord.push_back(coord);
        }
        break;
    case VERTICAL:
        if ((y + rk - 1) >= 10) return false;
        for (unsigned i = 0; i < rk; i++){ //проверка на занятость квадрата 3*3
            unsigned _y = y + i;
            for (int j = -1; j < 2; j++)
                for (int k = -1; k < 2; k++){
                    int c = 10 * (_y + j) + x + k;
                    if (c >= 0 && c < 100)
                        if (field[c].isBusy()) return false;
                }
        }
        for (unsigned i = 0; i < rk; i++){
            field[10 * (y + i) + x].setBusy();
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

void Field::autoPlaceShips(){ //ЭТО НОРМАЛЬНО ВООБЩЕ? МИЛЛИОН ЛЕТ РАБОТАТЬ НЕ БУДЕТ?
     srand(static_cast<unsigned>(time(nullptr)));
    //  алгоритм автоматичекого размещения кораблей

    //  определяем случайным образом положение корабля
    //  исключаем занятые клетки с массива, если места нет а корабли есть - обнуляем полe
    //  повторяем, пока не расставим все корабли
    std::array<unsigned, 10> arr = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    bool ok = false, placed = false;
    while(!placed){
        clear();
        for (unsigned i = 0; i < 10; i++){
            Ship sh(arr[i]);
            unsigned x = rand() % 10;
            unsigned y = rand() % 10;
            ShipPosition pos = (rand() % 2) ?  HORIZONTAL : VERTICAL;
            ok = setShip(x, y, sh, pos);
            if (!ok) continue;
        }
        placed = true;
    }
}

bool Field::shoot(unsigned x, unsigned y){
    size_t coord = 10 * (y - 1) + x;
    if (!field[coord].isAlive())  return false;

    field[coord].setDead();
    if (field[coord].isBusy()){
        //ПОКАЗАТЬ, ЧТО ТАМ БЫЛ КОРАБЛЬ
        for (unsigned i = 0; i < ships.size(); i++){
            for (unsigned j = 0; j<ships[i].coordinates.size(); j++){
                if (ships[i].coordinates[j].first == x
                      && ships[i].coordinates[j].second == y)
                  ships[i].ship.shoot(j);
                if (!ships[i].ship.isAlive()){
                    killFrameCells(ships[i]);
                    //(В ИГРЕ) УМЕНЬШИТЬ СЧЕТЧИК КОРАБЛЕЙ, ЕСЛИ СЧЕТЧИК == 0 - КОНЕЦ
                }
            }
        }
    }
        return true;


}

void Field::clear(){
    field.fill(Cell());
}

std::array<Cell, 100> Field::getFieldInstance(){
    return field;
}

void Field::killFrameCells(const _Ship & s){
    for (unsigned i = 0; i < s.ship.getRank(); i++){
        unsigned _x = s.coordinates[i].first;
        unsigned _y = s.coordinates[i].second;
        for (int j = -1; j < 2; j++)
            for (int k = -1; k < 2; k++){
                int c = 10 * (_y + j) + _x + k;
                if (c >= 0 && c < 100) field[c].setDead();
            }
    }
}
