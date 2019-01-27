#ifndef CELL_H
#define CELL_H

enum State
{
    ALIVE,
    DEAD
   // empty,
   // shooted
};

class Cell
{
    State alive;
    bool busy;
public:
    Cell();
    bool isBusy();
    void setBusy();
    bool isAlive();
    void setAlive();
    void setDead();
   // void setEmpty();
   // void setShooted();

};

#endif // CELL_H
