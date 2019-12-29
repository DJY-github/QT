#pragma execution_character_set("utf-8")

#include "frmlcdnumber.h"
#include "ui_frmlcdnumber.h"
#include "qdatetime.h"
#include "qtimer.h"

frmLcdNumber::frmLcdNumber(QWidget *parent) : QWidget(parent), ui(new Ui::frmLcdNumber)
{
    ui->setupUi(this);
    this->initForm();
}

frmLcdNumber::~frmLcdNumber()
{
    delete ui;
}

void frmLcdNumber::initForm()
{
    ui->lcdNumber2->setNumberColorStart(QColor(255, 107, 107));
    ui->lcdNumber2->setNumberColorEnd(QColor(255, 0, 0));

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmLcdNumber::updateValue()
{
    ui->lcdNumber1->setNumber(qrand() % 10);
    ui->lcdNumber2->setNumber(qrand() % 10);
}
