#include "cell.h"

Cell::Cell(){
    alive = ALIVE;
    busy = false;
}

bool Cell::isBusy(){
    return busy;
}

void Cell::setBusy(){
    busy = true;
}

bool Cell::isAlive(){
    return (alive == ALIVE);
}

void Cell::setAlive(){
    alive = ALIVE;
}

void Cell::setDead(){
    alive = DEAD;
}
