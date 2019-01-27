#include "field.h"

Field::Field()
{

}

bool Field::setSheep(int x, int y, const Ship & ship, ShipPosition pos){
    int rk = ship.getRank();
    switch(pos){
    case HORIZONTAL:
        if ((x + rk - 1) >= 10) return false;
        for (int i = 0; i < rk; i++){
            field[10 * y + x + i].setBusy();
        }
        break;
    case VERTICAL:
        if ((y + rk - 1) >= 10) return false;
        for (int i = 0; i < rk; i++){
            field[10 * (y + i) + x].setBusy();
        }
        break;
    }
    return true;
}

bool Field::shoot(int x, int y){
    size_t coord = 10 * (y - 1) + x;
    if (field[coord].isAlive()){
        field[coord].setDead();
        if (field[coord].isBusy())
            //поранить корабль!!!!!!
        return true;
    }
    return false;
}

void Field::clear(){
    field.fill(Cell());
}
