#include "field.h"

Field::Field()
{

}

bool Field::setSheep(int x, int y, const Ship & ship, ShipPosition pos){
    int rk = ship.getRank();
    _Ship s;
    std::vector<std::pair<int, int>> shipsCoord;
    std::pair<int, int> coord;

    switch(pos){
    case HORIZONTAL:
        if ((x + rk - 1) >= 10) return false;
        for (int i = 0; i < rk; i++){
            field[10 * y + x + i].setBusy();
            coord.first = x + i;
            coord.second = y;
            shipsCoord.push_back(coord);
        }
        break;
    case VERTICAL:
        if ((y + rk - 1) >= 10) return false;
        for (int i = 0; i < rk; i++){
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

bool Field::shoot(int x, int y){
    size_t coord = 10 * (y - 1) + x;
    if (!field[coord].isAlive())  return false;

    field[coord].setDead();
    if (field[coord].isBusy()){
        for (int i = 0; i < ships.size(); i++){
            for (int j = 0; j<ships[i].coordinates.size(); j++){
                if (ships[i].coordinates[j].first == x
                      && ships[i].coordinates[j].second == y)
                  ships[i].ship.shoot(j);
                if (!ships[i].ship.isAlive()){
                    //убить клетки вокруг корабля

                    //уменьшить счетчик кораблей, если счетчик == 0 - конец (в игре)
                }
            }
        }
    }
        return true;


}

void Field::clear(){
    field.fill(Cell());
}
