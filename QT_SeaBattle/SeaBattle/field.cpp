#include "field.h"

Field::Field()
{

}

bool Field::setSheep(unsigned x, unsigned y, const Ship & ship, ShipPosition pos){
    unsigned rk = ship.getRank();
    _Ship s;
    std::vector<std::pair<unsigned, unsigned>> shipsCoord;
    std::pair<unsigned, unsigned> coord;

    switch(pos){
    case HORIZONTAL:
        if ((x + rk - 1) >= 10) return false;
        for (unsigned i = 0; i < rk; i++){
            field[10 * y + x + i].setBusy();
            coord.first = x + i;
            coord.second = y;
            shipsCoord.push_back(coord);
        }
        break;
    case VERTICAL:
        if ((y + rk - 1) >= 10) return false;
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
                    //УМЕНЬШИТЬ СЧЕТЧИК КОРАБЛЕЙ, ЕСЛИ СЧЕТЧИК == 0 - КОНЕЦ (В ИГРЕ)
                }
            }
        }
    }
        return true;


}

void Field::clear(){
    field.fill(Cell());
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
