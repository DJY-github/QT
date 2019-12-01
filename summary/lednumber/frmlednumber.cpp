#pragma execution_character_set("utf-8")

#include "frmlednumber.h"
#include "ui_frmlednumber.h"
#include "qdatetime.h"
#include "qtimer.h"

frmLedNumber::frmLedNumber(QWidget *parent) : QWidget(parent), ui(new Ui::frmLedNumber)
{
    ui->setupUi(this);
    this->initForm();
}

frmLedNumber::~frmLedNumber()
{
    delete ui;
}

void frmLedNumber::initForm()
{
    ui->ledNumber2->setNumberColorStart(QColor(255, 107, 107));
    ui->ledNumber2->setNumberColorEnd(QColor(255, 0, 0));

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmLedNumber::updateValue()
{
    ui->ledNumber1->setNumber(qrand() % 10);
    ui->ledNumber2->setNumber(qrand() % 10);
}
