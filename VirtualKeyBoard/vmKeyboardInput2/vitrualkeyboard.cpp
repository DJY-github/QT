#include "vitrualkeyboard.h"
#include "ui_vitrualkeyboard.h"
#include "testdialog.h"
#include "testdialog2.h"

vitrualkeyboard::vitrualkeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vitrualkeyboard)
{
    ui->setupUi(this);
}

vitrualkeyboard::~vitrualkeyboard()
{
    delete ui;
}

void vitrualkeyboard::on_pushButton_2_clicked()
{
    //testDialog *test = new testDialog;
    //test->show();
}

void vitrualkeyboard::on_pushButton_3_clicked()
{
    testDialog2 *test = new testDialog2;
    test->show();
}
