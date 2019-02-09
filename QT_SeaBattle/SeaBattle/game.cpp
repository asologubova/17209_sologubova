#include "game.h"

Game::Game(){
    status = GameStatus::StartNewGame;
}

//const std::array<Cell, 100> & Game::getEnemyField(int k){
//    if (k == 1) return f2.getFieldInstance();
//    else return f1.getFieldInstance();
//}

bool Game::checkPlacing(const std::array<Cell, 100> & fld) const
{
    int singleDeck = 0,
            doubleDeck = 0,
            threeDeck = 0,
            fourDeck = 0;
    int count = 0;
    std::array<Cell, 100> tmp = fld;

    for (int y = 0; y < 10; y++){
        for (int x = 0; x < 10; x++){
            int c = 10 * y + x;
            if(tmp[c] == Cell::CL_SHIP){
                if((x < 9) && (tmp[c + 1] == Cell::CL_SHIP)){ // горизонтальный
                    while ((x + count < 10) && (tmp[c + count] == Cell::CL_SHIP)){

                        if ((tmp[c + count - 11] == Cell::CL_SHIP && y > 0 && (x + count) > 0) ||
                                (tmp[c + count - 10] == Cell::CL_SHIP && y > 0) ||
                                (tmp[c + count - 9] == Cell::CL_SHIP && y > 0 && (x + count) < 9) ||
                                (tmp[c + count + 9] == Cell::CL_SHIP && y < 9 && (x + count) > 0)||
                                (tmp[c + count + 10] == Cell::CL_SHIP && y < 9)||
                                (tmp[c + count + 11] == Cell::CL_SHIP && y < 9 && (x + count) < 9)){
                            return false;
                        }
                        tmp[c + count] = Cell::CL_CLEAR;
                        count++;
                    }

                } else { // вертикальный или однопалубный
                    while ((y + count < 10) && (tmp[c + 10 * count] == Cell::CL_SHIP)){

                        if ((tmp[c + 10 * count - 11] == Cell::CL_SHIP  && x > 0 && (y + count) > 0) ||
                                (tmp[c + 10 * count - 9] == Cell::CL_SHIP  && x < 9 && (y + count) > 0) ||
                                (tmp[c + 10 * count - 1] == Cell::CL_SHIP  && x > 0) ||
                                (tmp[c + 10 * count + 1] == Cell::CL_SHIP  &&  x < 9 ) ||
                                (tmp[c + 10 * count + 9] == Cell::CL_SHIP && x > 0 && (y + count) < 9)||
                                (tmp[c + 10 * count + 11] == Cell::CL_SHIP && x < 9 && (y + count) < 9)){
                            return false;
                        }
                        tmp[c + 10 * count] = Cell::CL_CLEAR;
                        count++;
                    }
                }

                if (count > 4) return false;
                if (count == 4) fourDeck++;
                else if (count == 3) threeDeck++;
                else if (count == 2) doubleDeck++;
                else if (count == 1) singleDeck++;
                count = 0;
            }
            tmp[c] = Cell::CL_CLEAR;
        }
    }
    if ((fourDeck != 1) || (threeDeck != 2) || (doubleDeck != 3) || (singleDeck != 4)) return false;
    return true;
}
