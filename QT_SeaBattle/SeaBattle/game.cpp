#include "game.h"

Game::Game(){
    status = StartNewGame;

}

void Game::doGame(){
    while(status != EndOfGame){
        switch (status){
            case StartNewGame: // Начинаем новую игру
            {
                Player1.init();
                Player2.init();
                status = Player1Attack;
                break;
            }
            case Player1Attack: // Ход первого игрока
            {
                int x=0;
                int y=0;

                Player1.Attack(x, y);

                int result = Player2.TestCell(x, y);

                if (strcmp(Player2.PlayerStatus(), "Проиграл") == 0)
                    status=EndOfGame; // Был уничтожен последний корабль, завершаем игру

                if (result == Player::None) status=Player2Attack; // Промазал!!! Передаем ход противнику
                else status=Player1Attack; // Попал!!! Снова ходит первый игрок

                break;
            }
            case Player2Attack: // Ход второго игрока
            {
                int x=0;
                int y=0;

                Player2.Attack(x, y);

                int result=Player1.TestCell(x, y);

                if (strcmp(Player1.PlayerStatus(), "Проиграл") == 0)
                    status=EndOfGame; // Был уничтожен последний корабль, завершаем игру

                if (result == Player::None) status=Player1Attack; // Промазал!!! Передаем ход противнику
                else status=Player2Attack; // Попал!!! Снова ходит второй игрок

                break;
            }

            // После каждого хода отрисовываем текущее состояние игроков и ждем нажатия любой клавиши
            //Player1.DrawBoard();
            //Player2.DrawBoard();
            //getch();
        };

        //Выводим результаты игры
        //cout << "Первый игрок: " << Player1.PlayerStatus() << endl;
        //cout << "Второй игрок: " << Player2.PlayerStatus() << endl;
        //cout << "Игра окончена." << endl;
        //getch();
    }
}
