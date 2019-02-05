#include "game.h"

Game::Game(){
    status = StartNewGame;

}

const std::array<Cell, 100> & Game::getEnemyField(int k){
    if (k == 1) return f2.getFieldInstance();
    else return f1.getFieldInstance();
}


void Game::doGame(){
    bool shooted = false;
    bool contin = false;
    std::pair<int, int> decision;
    //bool point = false;

    while(status != EndOfGame){
        if (status == StartNewGame) // Начинаем новую игру
            status = Player1Attack;

        else if (status == Player1Attack){  // Ход первого игрока

            if (contin)
                decision = Player1.makeRawDecision(getEnemyField(2));
            //else - человечье решение
            shooted = f2.shoot(decision.first, decision.second);

            if (/*уничтожен последний корабль противника*/ 1)
                status = EndOfGame;

            if (!shooted){
                 status = Player2Attack; // Мимо :)
                 contin = false;
            }
            else {
                status = Player1Attack; // Снова ходит первый игрок (но делает человечье решение)
                contin = true;
            }
        }

        else if (status == Player2Attack){  // Ход второго игрока
            if (contin)
                decision = Player2.makeRawDecision(getEnemyField(1));
            //else - человечье решение
            shooted = f1.shoot(decision.first, decision.second);

            if (/*уничтожен последний корабль противника*/ 1)
                status = EndOfGame;

            if (!shooted){
                 status = Player1Attack; // Мимо :)
                 contin = false;
            }
            else {
                status = Player2Attack; // Снова ходит первый игрок (но делает человечье решение)
                contin = true;
            }
        }

        // После каждого хода отрисовываем текущее состояние игроков и ждем нажатия любой клавиши
        //Player1.DrawBoard();
        //Player2.DrawBoard();
        //getch();
    }

    //Выводим результаты игры
    //cout << "Первый игрок: " << Player1.PlayerStatus() << endl;
    //cout << "Второй игрок: " << Player2.PlayerStatus() << endl;
    //cout << "Игра окончена." << endl;
    //getch();

}
bool Game::checkPlacing(const std::array<Cell, 100> & fld) const // + УЧЕСТЬ, ЯВЛЯЕТСЯ ЛИ КЛЕТКА КРАЙНЕЙ!!!
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
                        //проверка окружения
                        // + УЧЕСТЬ, ЯВЛЯЕТСЯ ЛИ КЛЕТКА КРАЙНЕЙ!!!
                        if (tmp[c + count - 11] == Cell::CL_SHIP ||
                                tmp[c + count - 10] == Cell::CL_SHIP ||
                                tmp[c + count - 9] == Cell::CL_SHIP ||
                                tmp[c + count + 9] == Cell::CL_SHIP||
                                tmp[c + count + 10] == Cell::CL_SHIP||
                                tmp[c + count + 11] == Cell::CL_SHIP){
                            return false;
                        }
                        tmp[c + count] = Cell::CL_CLEAR;
                        count++;
                    }
                    if (count > 4) return false;
                    if (count == 4) fourDeck++;
                    else if (count == 3) threeDeck++;
                    else if (count == 2) doubleDeck++;
                    else if (count == 1) singleDeck++;
                    count = 0;

                } else { // вертикальный или однопалубный
                    while ((y + count < 10) && (tmp[c + 10 * count] == Cell::CL_SHIP)){
                        //проверка окружения
                        // + УЧЕСТЬ, ЯВЛЯЕТСЯ ЛИ КЛЕТКА КРАЙНЕЙ!!!
                        if (tmp[c + 10 * count - 11] == Cell::CL_SHIP ||
                                tmp[c + 10 * count - 9] == Cell::CL_SHIP ||
                                tmp[c + 10 * count + 9] == Cell::CL_SHIP||
                                tmp[c + 10 * count + 11] == Cell::CL_SHIP){
                            return false;
                        }
                        tmp[c + 10 * count] = Cell::CL_CLEAR;
                        count++;
                    }
                    if (count > 4) return false;
                    if (count == 4) fourDeck++;
                    else if (count == 3) threeDeck++;
                    else if (count == 2) doubleDeck++;
                    else if (count == 1) singleDeck++;
                    count = 0;
                }
            }
            tmp[c] = Cell::CL_CLEAR;
        }
    }
    if ((fourDeck != 1) || (threeDeck != 2) || (doubleDeck != 3) || (singleDeck != 4)) return false;
    return true;
}
