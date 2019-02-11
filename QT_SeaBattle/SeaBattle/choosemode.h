#ifndef CHOOSEMODE_H
#define CHOOSEMODE_H

#include <QWidget>

namespace Ui {
class ChooseMode;
}

class ChooseMode : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseMode(QWidget *parent = nullptr);
    ~ChooseMode();

private:
    Ui::ChooseMode *ui;
};

#endif // CHOOSEMODE_H
