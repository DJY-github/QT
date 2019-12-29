#pragma execution_character_set("utf-8")

#include "frmwaveline.h"
#include "ui_frmwaveline.h"
#include "qdatetime.h"
#include "qtimer.h"

frmWaveLine::frmWaveLine(QWidget *parent) : QWidget(parent), ui(new Ui::frmWaveLine)
{
    ui->setupUi(this);
    this->initForm();
}

frmWaveLine::~frmWaveLine()
{
    delete ui;
}

void frmWaveLine::initForm()
{
    QColor bgColor(30, 30, 30);
    ui->waveLine1->setBgColorStart(bgColor);
    ui->waveLine1->setBgColorEnd(bgColor);
    ui->waveLine2->setBgColorStart(bgColor);
    ui->waveLine2->setBgColorEnd(bgColor);
    ui->waveLine3->setBgColorStart(bgColor);
    ui->waveLine3->setBgColorEnd(bgColor);

    ui->waveLine2->setLineColor(QColor(255, 107, 107));
    ui->waveLine3->setLineColor(QColor(24, 189, 155));

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmWaveLine::updateValue()
{
    QVector<int> data;
    int maxValue = 100;

    for (int i = 0; i < 50; i++) {
        int rand = qrand() % maxValue;
        data.append(rand);
    }

    ui->waveLine1->setMaxValue(maxValue);
    ui->waveLine1->setData(data);

    data.clear();
    maxValue = 50;

    for (int i = 0; i < 100; i++) {
        int rand = qrand() % maxValue;
        data.append(rand);
    }

    ui->waveLine2->setMaxValue(maxValue);
    ui->waveLine2->setData(data);

    data.clear();
    maxValue = 100;

    for (int i = 0; i < 100; i++) {
        int rand = qrand() % maxValue;
        data.append(rand);
    }

    ui->waveLine3->setMaxValue(maxValue);
    ui->waveLine3->setData(data);
}
