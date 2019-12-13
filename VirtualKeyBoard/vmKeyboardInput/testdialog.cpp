#include "testdialog.h"
#include "ui_testdialog.h"

testDialog::testDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::testDialog)
{
    ui->setupUi(this);
}

testDialog::~testDialog()
{
    delete ui;
}
