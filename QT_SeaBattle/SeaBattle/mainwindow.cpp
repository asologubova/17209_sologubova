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
        ui->tableWidget_myField->setColumnWidth(i, ui->tableWidget_myField->rowCount()/10);
        ui->tableWidget_myField->setRowHeight(i, ui->tableWidget_myField->rowCount()/10);
    }

    ui->tableWidget_enemyField->setColumnCount(10);
    ui->tableWidget_enemyField->setRowCount(10);
    ui->tableWidget_enemyField->setShowGrid(true);
    ui->tableWidget_enemyField->setSelectionMode(QAbstractItemView::SingleSelection);
    for (int i = 0; i < 10; i++){
        ui->tableWidget_enemyField->setColumnWidth(i, ui->tableWidget_enemyField->rowCount()/10);
        ui->tableWidget_enemyField->setRowHeight(i, ui->tableWidget_enemyField->rowCount()/10);
    }

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++){
            QTableWidgetItem *t = new QTableWidgetItem("");
            ui->tableWidget_myField->setItem(i,j,t);
        }

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++){
            QTableWidgetItem *t = new QTableWidgetItem("");
            ui->tableWidget_enemyField->setItem(i,j,t);
        }

    //режим расстановки кораблей:

    //запретить редактировать свое поле:
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++){
            ui->tableWidget_myField->item(i,j)->setFlags(Qt::ItemIsDragEnabled);
        }


    //играем:

}


MainWindow::~MainWindow()
{
    //удалить item'ы
    delete ui;

}

void MainWindow::on_actionstart_game_triggered()
{
    // Начать новую игру
    ui->statusBar->showMessage("Вы начали новую игру");
}

void MainWindow::on_actionsave_game_triggered()
{
    // Сохранить игру
    ui->statusBar->showMessage("Идет сохранение...");



    //ui->statusBar->showMessage("Игра сохранена");
}

void MainWindow::on_actionopen_saved_game_triggered()
{
    // Открыть сохраненную игру
    ui->statusBar->showMessage("Идет загрузка...");



    //ui->statusBar->showMessage("Сохраненная игра загружена");
}

void MainWindow::reprintField(QTableWidget & wid)
{
    // Перепечатать поля
    for (int i = 0; i < wid.rowCount(); i++){
        for (int j = 0; j < wid.columnCount(); j++){

        }
    }
}

void MainWindow::on_tableWidget_enemyField_cellClicked(int row, int column)
{
    //если нет корабля:
    ui->tableWidget_enemyField->item(row, column)->setBackground(Qt::yellow);
    //если есть корабль:
    //ui->tableWidget_enemyField->item(row, column)->setBackground(Qt::red);
}
