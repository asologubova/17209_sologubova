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
    ui->label_result->setStyleSheet("color: rgb(0,0,255)");
    ui->label_result->setAlignment(Qt::AlignHCenter);
    ui->pushButton_shoot->setText(tr("Сделать ход"));
    ui->pushButton_shoot->setHidden(true);
    ui->pushButton_place_ships->setText(tr("Расставить корабли"));
    ui->pushButton_clear->setText(tr("Очистить поле"));
    ui->label_1->setText(tr("Моё поле"));
    ui->label_2->setText(tr("Поле противника"));
    ui->menuGame->setTitle(tr("Игра"));
    ui->actionnew_game->setText(tr("Новая игра"));
    ui->actionsave_game->setText(tr("Сохранить игру"));
    ui->actionopen_saved_game->setText(tr("Открыть сохраненную игру"));

    connect(ui->pushButton_place_ships, SIGNAL(clicked()), this, SLOT(checkPlacing()));
    connect(ui->pushButton_auto_place_ships, SIGNAL(clicked()), this, SLOT(autoPlace()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clearField()));
}

MainWindow::~MainWindow()
{
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

    myField.clear();
    enemyField.clear();
    shootedPoints.fill(Cell::CL_CLEAR);

    ui->pushButton_shoot->setHidden(true);
    ui->label_result->setHidden(true);
    ui->pushButton_clear->setHidden(false);
    ui->pushButton_place_ships->setHidden(false);
    ui->pushButton_auto_place_ships->setHidden(false);

    ui->statusBar->showMessage(tr("Вы начали новую игру"));
}

void MainWindow::on_actionsave_game_triggered()
{
    ui->statusBar->showMessage(tr("Идет сохранение..."));

    QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить текущую игру"),
        QDir::homePath() + "/Desktop/SB/QT_SeaBattle/SeaBattle/saved games", tr("Game files *.txt (*.txt)")); //изменить

    if(filename.length() < 1)
        return;

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
        return;

    QString str;
    QChar ch;

    GameStatus s = seaBattle.status;
    switch(s){
    case GameStatus::StartNewGame: str = "StartNewGame"; break;
    case GameStatus::MeAttack: str = "MeAttack"; break;
    case GameStatus::EnemyAttack: str = "EnemyAttack"; break;
    case GameStatus::EndOfGame: str = "EndOfGame"; break;
    }
    file.write(str.toUtf8());
    str.clear();

    std::array<Cell, 100> mf = myField.getFieldInstance();
    std::array<Cell, 100> ef = enemyField.getFieldInstance();
    for (int i = 0; i < 10; i++){
        file.write("\r\n");
        for (int  j = 0; j < 10; j++){
            Cell c = mf[10 * i + j];
            switch(c){
            case Cell::CL_CLEAR: ch = 'c'; break;
            case Cell::CL_SHIP: ch = 's'; break;
            case Cell::CL_DOT: ch = 'd'; break;
            case Cell::CL_HALF: ch = 'h'; break;
            case Cell::CL_FULL: ch = 'f'; break;
            }
            str += ch;
        }
        file.write(str.toUtf8());
        str.clear();
    }

    for (int i = 0; i < 10; i++){
        file.write("\r\n");
        for (int  j = 0; j < 10; j++){
            Cell c = ef[10 * i + j];
            switch(c){
            case Cell::CL_CLEAR: ch = 'c'; break;
            case Cell::CL_SHIP: ch = 's'; break;
            case Cell::CL_DOT: ch = 'd'; break;
            case Cell::CL_HALF: ch = 'h'; break;
            case Cell::CL_FULL: ch = 'f'; break;
            }
            str += ch;
        }
        file.write(str.toUtf8());
        str.clear();
    }

    file.close();

    ui->statusBar->showMessage(tr("Игра сохранена"));
}

void MainWindow::on_actionopen_saved_game_triggered()
{
    ui->statusBar->showMessage(tr("Идет загрузка..."));

    for(int i = 0; i<10; i++){
        for (int j = 0; j<10; j++){
            ui->tableWidget_myField->item(i,j)->setBackgroundColor(Qt::white);
            ui->tableWidget_myField->item(i,j)->setIcon(QIcon());

            ui->tableWidget_enemyField->item(i,j)->setBackgroundColor(Qt::white);
            ui->tableWidget_enemyField->item(i,j)->setIcon(QIcon());
        }
    }

    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть сохраненную игру"),
        QDir::homePath() + "/Desktop/SB/QT_SeaBattle/SeaBattle/saved games", tr("Game files *.txt (*.txt)")); //изменить

    if(filename.length() < 1)
        return;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return;

    myField.clear();
    enemyField.clear();
    shootedPoints.fill(Cell::CL_CLEAR);

    QString str = "";
    str = file.readLine();

    if (str == "StartNewGame\r\n")
        seaBattle.status = GameStatus::StartNewGame;
    else if (str == "MeAttack\r\n")
        seaBattle.status = GameStatus::MeAttack;
    else if (str == "EnemyAttack\r\n")
        seaBattle.status = GameStatus::EnemyAttack;
    else
        seaBattle.status = GameStatus::EndOfGame;

    std::array<Cell, 100> currentField;

    for (int i = 0; i < 10; i++){
        str = file.readLine();
        for (int j = 0; j < 10; j++){
            if (str[j] == 'c')
                currentField[10 * i + j] = Cell::CL_CLEAR;
            else if (str[j] == 's')
                currentField[10 * i + j] = Cell::CL_SHIP;
            else if (str[j] == 'd')
                currentField[10 * i + j] = Cell::CL_DOT;
            else if (str[j] == 'h')
                currentField[10 * i + j] = Cell::CL_HALF;
            else //full
                currentField[10 * i + j] = Cell::CL_FULL;
        }
    }

    myField.fill(currentField);
    reprintField("my");

    for (int i = 0; i < 10; i++){
        str = file.readLine();
        for (int j = 0; j < 10; j++){
            if (str[j] == 'c')
                currentField[10 * i + j] = Cell::CL_CLEAR;
            else if (str[j] == 's')
                currentField[10 * i + j] = Cell::CL_SHIP;
            else if (str[j] == 'd')
                currentField[10 * i + j] = Cell::CL_DOT;
            else if (str[j] == 'h')
                currentField[10 * i + j] = Cell::CL_HALF;
            else
                currentField[10 * i + j] = Cell::CL_FULL;
        }
    }

    enemyField.fill(currentField);
    reprintField("enemy");

    file.close();

    ui->statusBar->showMessage(tr("Сохраненная игра загружена"));

    if (seaBattle.status == GameStatus::StartNewGame){
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                ui->tableWidget_enemyField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);

        checkPlacing();
        return;
    }
    else if (seaBattle.status == GameStatus::MeAttack){
        ui->pushButton_clear->setHidden(true);
        ui->pushButton_place_ships->setHidden(true);
        ui->pushButton_auto_place_ships->setHidden(true);
        ui->statusBar->showMessage(tr("Ваш ход"));
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                ui->tableWidget_enemyField->item(i,j)->setFlags(nullptr);
        return;
    }
    else if (seaBattle.status == GameStatus::EnemyAttack){
        ui->pushButton_clear->setHidden(true);
        ui->pushButton_place_ships->setHidden(true);
        ui->pushButton_auto_place_ships->setHidden(true);
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                ui->tableWidget_enemyField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);
        enemyAttack();
        return;
    }
}

void MainWindow::reprintField(const std::string & key)
{
    std::array<Cell, 100> currentField;
    if (key == "my"){
        currentField = myField.getFieldInstance();
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++){
                if (currentField[10 * i + j] == Cell::CL_FULL || currentField[10 * i + j] == Cell::CL_HALF){
                    ui->tableWidget_myField->item(i,j)->setBackgroundColor(Qt::blue);
                    ui->tableWidget_myField->item(i,j)->setIcon(img_cross);
//                    QTableWidgetItem *t = new QTableWidgetItem(img_cross, "");
//                    t->setBackgroundColor(Qt::blue);
//                    ui->tableWidget_myField->setItem(i,j,t);
                }
                else if (currentField[10 * i + j] == Cell::CL_DOT){
                    ui->tableWidget_myField->item(i,j)->setIcon(img_point);
//                    QTableWidgetItem *t = new QTableWidgetItem(img_point, "");
//                    t->setBackgroundColor(Qt::white);
//                    ui->tableWidget_myField->setItem(i,j,t);
                }
                else if (currentField[10 * i + j] == Cell::CL_SHIP){
                    ui->tableWidget_myField->item(i,j)->setBackgroundColor(Qt::blue);
                }
                else ui->tableWidget_myField->item(i,j)->setBackgroundColor(Qt::white);
            }
    }

    else if (key == "enemy"){
        currentField = enemyField.getFieldInstance();
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++){
                if (currentField[10 * i + j] == Cell::CL_FULL || currentField[10 * i + j] == Cell::CL_HALF){
                    ui->tableWidget_enemyField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);
                    ui->tableWidget_enemyField->item(i,j)->setIcon(img_cross);
//                    QTableWidgetItem *t = new QTableWidgetItem(img_cross, "");
//                    t->setBackgroundColor(Qt::white);
//                    ui->tableWidget_enemyField->setItem(i,j,t);
                }
                else if (currentField[10 * i + j] == Cell::CL_DOT){
                    ui->tableWidget_enemyField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);
                    ui->tableWidget_enemyField->item(i,j)->setIcon(img_point);
//                    QTableWidgetItem *t = new QTableWidgetItem(img_point, "");
//                    t->setBackgroundColor(Qt::white);
//                    ui->tableWidget_enemyField->setItem(i,j,t);
                }


//                //...............
//                else if (currentField[10 * i + j] == Cell::CL_SHIP){
//                    ui->tableWidget_enemyField->item(i,j)->setBackgroundColor(Qt::red);
//                    ui->tableWidget_enemyField->item(i,j)->setFlags(nullptr);
//                }
//                else{
//                    ui->tableWidget_enemyField->item(i,j)->setBackgroundColor(Qt::white);
//                    ui->tableWidget_enemyField->item(i,j)->setFlags(nullptr);
//                }
//                //...............


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
    if (!(ui->tableWidget_enemyField->item(row,column)->flags() == Qt::ItemIsDragEnabled)){
        meAttack(row, column);
    }
}

void MainWindow::autoPlace()
{
    myField.clear();
    myField.autoPlaceShips();
    reprintField("my");
}

void MainWindow::clearField()
{
    myField.clear();
    reprintField("my");
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

    bool ok = seaBattle.checkPlacing(currentField, myField);
    if (!ok){
        QString str = tr("Пожалуйста, расставьте корабли по правилу: ");
        str += tr("корабли не должны соприкасаться друг с другом бортами или углами,");
        str += tr("на поле должно располагаться 10 кораблей: \nодин 4-палубный,");
        str += tr("\nдва 3-палубных, \nтри 2 - палубных \nи четыре 1-палубных корабля.\n");
        str += tr("Клетки всех кораблей должны располагаться в ряд, не допускается ");
        str += tr("расстановка кораблей зиг-загом, углом или квадратом");
        QMessageBox::information(this, tr("Неправильная расстановка"), str);
    } else {

        ui->pushButton_auto_place_ships->setHidden(true);
        ui->pushButton_place_ships->setHidden(true);
        ui->pushButton_clear->setHidden(true);

        enemyField.autoPlaceShips();


//        //....................
//        reprintField("enemy");
//        //....................


        srand(static_cast<unsigned>(time(nullptr)));
        int r = rand() % 2;
        seaBattle.status =  (r == 1) ? GameStatus::MeAttack : GameStatus::EnemyAttack;
        if (seaBattle.status == GameStatus::EnemyAttack){
            enemyAttack();
            return;
        }
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++){
                ui->tableWidget_myField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);
                ui->tableWidget_enemyField->item(i,j)->setFlags(nullptr);
            }
        ui->statusBar->showMessage(tr("Ваш ход"));
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
    Field f; //такого случая не должно быть
    return f.getFieldInstance();
}

void MainWindow::meAttack(int x, int y)
{
    char contin = enemyField.shoot(y, x);
    reprintField("enemy");
    if (enemyField.getNumOfShips() == 0){
        seaBattle.status = GameStatus::EndOfGame;
        endGame("YOU HAVE WON!");
        return;
    }

    if (contin > 0){
        ui->tableWidget_enemyField->item(y,x)->setFlags(Qt::ItemIsDragEnabled);
        ui->statusBar->showMessage(tr("Ваш ход"));
        return;
    }

    seaBattle.status = GameStatus::EnemyAttack;
    enemyAttack();
}

void MainWindow::enemyAttack()
{
    ui->statusBar->showMessage(tr("Ходит противник"));
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            ui->tableWidget_enemyField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);

    char contin = 0;
    std::pair<int, int> decision;

    std::array<Cell, 100> tmp;
    tmp.fill(Cell::CL_CLEAR);

    if (shootedPoints != tmp)
        decision = comp.makeReasonDecision(myField.getFieldInstance(), shootedPoints);
    else decision = comp.makeRawDecision(myField.getFieldInstance());
    contin = myField.shoot(decision.first, decision.second);
    reprintField("my");

    if (contin == 1) shootedPoints[10 * decision.second + decision.first] = Cell::CL_HALF;

    while(contin != 0){
        if (myField.getNumOfShips() == 0){
            seaBattle.status = GameStatus::EndOfGame;
            endGame("THE OPPONENT HAS WON!");
            return;
        }
        if (contin == 1){ // Должно быть человечье решение (ранил)
            decision = comp.makeReasonDecision(myField.getFieldInstance(), shootedPoints);
            contin = myField.shoot(decision.first, decision.second);
            reprintField("my");

            if (contin == 1) shootedPoints[10 * decision.second + decision.first] = Cell::CL_HALF;
        }
        else{   // contin == 2 или 3 (убил или ткнул туда, где уже стоит отметка)
            if (contin == 2)
                shootedPoints.fill(Cell::CL_CLEAR);
            decision = comp.makeRawDecision(myField.getFieldInstance());
            contin = myField.shoot(decision.first, decision.second);
            reprintField("my");

            if (contin == 1) shootedPoints[10 * decision.second + decision.first] = Cell::CL_HALF;
        }
    }

    seaBattle.status = GameStatus::MeAttack;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            ui->tableWidget_enemyField->item(i,j)->setFlags(nullptr);

    ui->statusBar->showMessage(tr("Ваш ход"));
}

void MainWindow::endGame(const QString & str)
{
    ui->statusBar->showMessage(tr("Игра окончена"));
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++){
            ui->tableWidget_myField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);
            ui->tableWidget_enemyField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);
        }
    ui->label_result->setHidden(false);
    ui->label_result->setText(str);
}
