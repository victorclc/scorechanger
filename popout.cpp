#include "popout.h"
#include "ui_popout.h"
#include "scorechanger.h"
popout::popout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::popout)
{
    ui->setupUi(this);
}

popout::~popout()
{
    delete ui;
}

void popout::on_pushButton_clicked()
{
    newMap = ui->lineEdit->text();
}
