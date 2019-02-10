#include "ship.h"

Ship::Ship(int rk)
{
    if(rk >= 1 && rk <= 4) {
        rank = rk;
        alive = true;
        for(int i = 0; i < rank; i++)
            state[i] = ShipState::ALIVE;

        return;
    }
    else {
        alive = false;
        rank = 0; //rank = 1;
    }
}

int Ship::getRank() const{
    return rank;
}

const std::array<ShipState, 5> & Ship::getStates() const{
    return state;
}

void Ship::shoot(int num){
    if(num >= 0 && num < rank) {
        state[num] = ShipState::DESTROYED;

        for(int i = 0; i < rank; i++)
            if (state[i] == ShipState::ALIVE) return;

        alive = false;
    }
}

bool Ship::isAlive() const {
    return alive;
}
