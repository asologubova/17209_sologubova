#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMessageBox>
//#include <QPixmap>

#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionnew_game_triggered();
    void on_actionsave_game_triggered();
    void on_actionopen_saved_game_triggered();

    void reprintField(QTableWidget & wid);

    void on_tableWidget_myField_cellClicked(int row, int column);
    void on_tableWidget_enemyField_cellClicked(int row, int column);

    void checkPlacing();
    const std::array<Cell, 100> & getFieldInstace(const std::string & key) const;
    void doGame();

private:
    Ui::MainWindow *ui;

    Game *seaBattle;
    Field myField, enemyField;
    int enemyShips, myShips;

    QIcon img_point, img_cross;
};

#endif // MAINWINDOW_H
