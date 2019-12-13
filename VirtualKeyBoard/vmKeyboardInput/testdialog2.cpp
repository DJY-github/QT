#include "testdialog2.h"
#include "ui_testdialog2.h"

testDialog2::testDialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testDialog2)
{
    ui->setupUi(this);
}

testDialog2::~testDialog2()
{
    delete ui;
}
