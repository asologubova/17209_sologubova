#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sea Battle");

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

    connect(ui->pushButton_place_ships, SIGNAL(clicked()), this, SLOT(checkPlacing()));
    connect(ui->tableWidget_enemyField, SIGNAL(cellClicked(int x, int y)), this, SLOT(shoot(x, y)));
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

void MainWindow::on_actionstart_game_triggered()
{
    //...

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
    if (!(ui->tableWidget_myField->item(row,column)->flags() == Qt::ItemIsDragEnabled)
            && (ui->tableWidget_myField->item(row,column)->backgroundColor() == Qt::white))
        ui->tableWidget_myField->item(row, column)->setBackground(Qt::blue);
    else if (!(ui->tableWidget_myField->item(row,column)->flags() == Qt::ItemIsDragEnabled)
             && (ui->tableWidget_myField->item(row,column)->backgroundColor() == Qt::blue))
        ui->tableWidget_myField->item(row, column)->setBackground(Qt::white);
}

void MainWindow::on_tableWidget_enemyField_cellClicked(int row, int column)
{
    if (!(ui->tableWidget_enemyField->item(row,column)->flags() == Qt::ItemIsDragEnabled)){
        //если нет корабля:
        ui->tableWidget_enemyField->item(row, column)->setBackground(Qt::yellow);
        //если есть корабль:
        //ui->tableWidget_enemyField->item(row, column)->setBackground(Qt::red);
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
        doGame();
    }
}

void MainWindow::shoot(int x, int y)
{

}

void MainWindow::doGame()
{

}
