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
