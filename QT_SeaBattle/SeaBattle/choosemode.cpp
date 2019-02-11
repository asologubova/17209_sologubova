#include "choosemode.h"
#include "ui_choosemode.h"

ChooseMode::ChooseMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseMode)
{
    ui->setupUi(this);
}

ChooseMode::~ChooseMode()
{
    delete ui;
}
