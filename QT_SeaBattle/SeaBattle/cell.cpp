#include "cell.h"

Cell::Cell(): state(alive), busy(false){

}

bool Cell::isBusy(){
    return busy;
}

void Cell::setBusy(){
    busy = true;
}

bool Cell::isAlive(){
    return (state == alive);
}

void Cell::setAlive(){
    state = alive;
}

void Cell::setDead(){
    state = dead;
}
