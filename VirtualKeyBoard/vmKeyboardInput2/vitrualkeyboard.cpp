#include "vitrualkeyboard.h"
#include "ui_vitrualkeyboard.h"
#include <QDebug>
#include <QMouseEvent>
#include <QEvent>

vitrualkeyboard::vitrualkeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vitrualkeyboard)
{
    ui->setupUi(this);
    test = new testDialog;
}

vitrualkeyboard::~vitrualkeyboard()
{
    delete ui;
}

void vitrualkeyboard::on_pushButton_2_clicked()
{
    test->show();
}

void vitrualkeyboard::on_pushButton_3_clicked()
{
    testDialog2 *test = new testDialog2;

    test->show();
}
