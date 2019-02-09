#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sea Battle");

    img_point.addFile(":/res/img/point.png");
    img_cross.addFile(":/res/img/cross.png");

    //QPixmap img_cross(":/res/img/point.png");
    //ui->tableWidget_myField->item(1,1)->setIcon(img_cross.scaled(20, 20, Qt::KeepAspectRatio));

    ui->tableWidget_myField->setColumnCount(10);
    ui->tableWidget_myField->setRowCount(10);
    ui->tableWidget_myField->setShowGrid(true);
    ui->tableWidget_myField->setSelectionMode(QAbstractItemView::SingleSelection);
    for (int i = 0; i < 10; i++){
        ui->tableWidget_myField->setColumnWidth(i, ui->tableWidget_myField->width()/10);
        ui->tableWidget_myField->setRowHeight(i, ui->tableWidget_myField->height()/10);
    }

    ui->tableWidget_enemyField->setColumnCount(10);
    ui->tableWidget_enemyField->setRowCount(10);
    ui->tableWidget_enemyField->setShowGrid(true);
    ui->tableWidget_enemyField->setSelectionMode(QAbstractItemView::SingleSelection);
    for (int i = 0; i < 10; i++){
        ui->tableWidget_enemyField->setColumnWidth(i, ui->tableWidget_enemyField->width()/10);
        ui->tableWidget_enemyField->setRowHeight(i, ui->tableWidget_enemyField->height()/10);
    }

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++){
            QTableWidgetItem *t = new QTableWidgetItem("");
            t->setBackgroundColor(Qt::white);
            ui->tableWidget_myField->setItem(i,j,t);
        }

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++){
            QTableWidgetItem *t = new QTableWidgetItem("");
            t->setBackgroundColor(Qt::white);
            ui->tableWidget_enemyField->setItem(i,j,t);
        }

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++){
            ui->tableWidget_enemyField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);
        }
    ui->tableWidget_myField->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_enemyField->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->label_result->setHidden(true);
    ui->pushButton_shoot->setHidden(true);

    connect(ui->pushButton_place_ships, SIGNAL(clicked()), this, SLOT(checkPlacing()));
    connect(ui->tableWidget_enemyField, SIGNAL(cellClicked(int x, int y)), this, SLOT(shoot(x, y)));

    myShips = 10;
    enemyShips = 10;
}


MainWindow::~MainWindow()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++){
            delete(ui->tableWidget_myField->item(i,j));
            delete(ui->tableWidget_enemyField->item(i,j));
        }
    delete ui;
}

//*****************************************************************************************************//

void MainWindow::on_actionnew_game_triggered()
{
    for(int i = 0; i<10; i++){
        for (int j = 0; j<10; j++){
            ui->tableWidget_myField->item(i,j)->setBackgroundColor(Qt::white);
            ui->tableWidget_myField->item(i,j)->setFlags(nullptr);
            ui->tableWidget_myField->item(i,j)->setIcon(QIcon());

            ui->tableWidget_enemyField->item(i,j)->setBackgroundColor(Qt::white);
            ui->tableWidget_enemyField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);
            ui->tableWidget_enemyField->item(i,j)->setIcon(QIcon());
        }
    }

    ui->pushButton_shoot->setHidden(true);
    ui->label_result->setHidden(true);
    ui->pushButton_place_ships->setHidden(false);

    myShips = 10;
    enemyShips = 10;

    ui->statusBar->showMessage("Вы начали новую игру");
}

void MainWindow::on_actionsave_game_triggered()
{
    ui->statusBar->showMessage("Идет сохранение...");

    //...

    ui->statusBar->showMessage("Игра сохранена");
}

void MainWindow::on_actionopen_saved_game_triggered()
{
    ui->statusBar->showMessage("Идет загрузка...");

    //...

    ui->statusBar->showMessage("Сохраненная игра загружена");
}

void MainWindow::reprintField(QTableWidget & wid) //наверное (после каждого хода)
{
    for (int i = 0; i < wid.rowCount(); i++){
        for (int j = 0; j < wid.columnCount(); j++){

        }
    }
}

void MainWindow::on_tableWidget_myField_cellClicked(int row, int column)
{
    if (!(ui->tableWidget_myField->item(row,column)->flags() == Qt::ItemIsDragEnabled)){
        if (ui->tableWidget_myField->item(row,column)->backgroundColor() == Qt::white)
            ui->tableWidget_myField->item(row, column)->setBackground(Qt::blue);
        else if (ui->tableWidget_myField->item(row,column)->backgroundColor() == Qt::blue)
            ui->tableWidget_myField->item(row, column)->setBackground(Qt::white);
    }
}


void MainWindow::on_tableWidget_enemyField_cellClicked(int row, int column)
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j< 10; j++)
            if (ui->tableWidget_enemyField->item(i,j)->backgroundColor() == Qt::yellow){
                ui->tableWidget_enemyField->item(i,j)->setBackgroundColor(Qt::white);
                if (!(ui->tableWidget_enemyField->item(row,column)->flags() == Qt::ItemIsDragEnabled)){
                    ui->tableWidget_enemyField->item(row, column)->setBackground(Qt::yellow);
                }
                return;
            }
    if (!(ui->tableWidget_enemyField->item(row,column)->flags() == Qt::ItemIsDragEnabled)){
        ui->tableWidget_enemyField->item(row, column)->setBackground(Qt::yellow);
    }
}

void MainWindow::checkPlacing()
{
    std::array<Cell, 100> currentField;
    currentField.fill(Cell::CL_CLEAR);
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (ui->tableWidget_myField->item(i,j)->backgroundColor() == Qt::blue){
                currentField[10 * i + j] = Cell::CL_SHIP;
            }
        }
    }

    bool ok = seaBattle->checkPlacing(currentField);
    if (!ok){
        QString str = "Пожалуйста, расставьте корабли по правилу: ";
        str += "корабли не должны соприкасаться друг с другом бортами или углами,";
        str += "на поле должно располагаться 10 кораблей: \nодин 4-палубный,";
        str += "\nдва 3-палубных, \nтри 2 - палубных \nи четыре 1-палубных корабля.\n";
        str += "Клетки всех кораблей должны располагаться в ряд, не допускается ";
        str += "расстановка кораблей зиг-загом, углом или квадратом";
        QMessageBox::information(this, "Неправильная расстановка", str);
    } else {
        ui->pushButton_place_ships->setHidden(true);

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++){
                ui->tableWidget_myField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);
                ui->tableWidget_enemyField->item(i,j)->setFlags(nullptr);
            }

        ui->pushButton_shoot->setHidden(false);
        doGame();
    }
}

const std::array<Cell, 100> & MainWindow::getFieldInstace(const std::string & key) const
{
    if (key == "my"){
        return myField.getFieldInstance();
    }
    else if (key == "enemy"){
        return enemyField.getFieldInstance();
    }
    Field f; //такого не должно быть
    return f.getFieldInstance();
}

void MainWindow::doGame()
{
//    bool shooted = false;
//    bool contin = false;
//    std::pair<int, int> decision;
//    //bool point = false;
//    computerPlayer comp;

//    while(seaBattle->status != GameStatus::EndOfGame){
//        if (seaBattle->status == StartNewGame) // Начинаем новую игру
//            seaBattle->status = Player1Attack;

//        else if (seaBattle->status == Player2Attack){  // Ход второго игрока

//            if (contin)
//                decision = comp.makeRawDecision(getEnemyField(2));
//            //else - человечье решение
//            shooted = f2.shoot(decision.first, decision.second);

//            if (/*уничтожен последний корабль противника*/ 1)
//                seaBattle->status = EndOfGame;

//            if (!shooted){
//                 seaBattle->status = Player1Attack; // Мимо :)
//                 contin = false;
//            }
//            else {
//                seaBattle->status = Player2Attack; // Снова ходит первый игрок (но делает человечье решение)
//                contin = true;
//            }
//        }

//        else if (seaBattle->status == Player1Attack){  // Ход второго игрока
//            if (contin)
//                decision = Player2.makeRawDecision(getEnemyField(1));
//            //else - человечье решение
//            shooted = f1.shoot(decision.first, decision.second);

//            if (/*уничтожен последний корабль противника*/ 1)
//                seaBattle->status = EndOfGame;

//            if (!shooted){
//                 seaBattle->status = Player1Attack; // Мимо :)
//                 contin = false;
//            }
//            else {
//                seaBattle->status = Player2Attack; // Снова ходит первый игрок (но делает человечье решение)
//                contin = true;
//            }
//        }

//        // После каждого хода отрисовываем текущее состояние игроков и ждем нажатия любой клавиши
//        //Player1.DrawBoard();
//        //Player2.DrawBoard();
//        //getch();
//    }

//    //Выводим результаты игры
//    //cout << "Первый игрок: " << Player1.PlayerStatus() << endl;
//    //cout << "Второй игрок: " << Player2.PlayerStatus() << endl;
//    //cout << "Игра окончена." << endl;
//    //getch();

}


