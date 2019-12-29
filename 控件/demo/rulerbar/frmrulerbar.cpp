#pragma execution_character_set("utf-8")

#include "frmrulerbar.h"
#include "ui_frmrulerbar.h"
#include "qdatetime.h"
#include "qtimer.h"

frmRulerBar::frmRulerBar(QWidget *parent) : QWidget(parent), ui(new Ui::frmRulerBar)
{
    ui->setupUi(this);
    this->initForm();
}

frmRulerBar::~frmRulerBar()
{
    delete ui;
}

void frmRulerBar::initForm()
{
    ui->rulerBar1->setShortStep(2);
    ui->rulerBar2->setShortStep(2);
    ui->rulerBar3->setShortStep(2);
    ui->rulerBar4->setShortStep(2);

    ui->rulerBar3->setAnimation(true);
    ui->rulerBar4->setAnimation(true);
    ui->rulerBar3->setAnimationStep(1);
    ui->rulerBar4->setAnimationStep(2);

    ui->rulerBar2->setBarColor(QColor(255, 107, 107));
    ui->rulerBar3->setBarColor(QColor(24, 189, 155));
    ui->rulerBar4->setBarColor(QColor(0, 255, 255));

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmRulerBar::updateValue()
{
    ui->rulerBar1->setValue(qrand() % 100);
    ui->rulerBar2->setValue(qrand() % 100);
    ui->rulerBar3->setValue(qrand() % 100);
    ui->rulerBar4->setValue(qrand() % 100);
}
