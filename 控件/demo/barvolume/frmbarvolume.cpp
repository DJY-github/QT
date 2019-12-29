#pragma execution_character_set("utf-8")

#include "frmbarvolume.h"
#include "ui_frmbarvolume.h"
#include "qdatetime.h"
#include "qtimer.h"

frmBarVolume::frmBarVolume(QWidget *parent) : QWidget(parent), ui(new Ui::frmBarVolume)
{
    ui->setupUi(this);
    this->initForm();
}

frmBarVolume::~frmBarVolume()
{
    delete ui;
}

void frmBarVolume::initForm()
{
    ui->barVolume2->setBarColorStart(QColor(255, 64, 64));
    ui->barVolume2->setBarColorMid(QColor(255, 127, 36));
    ui->barVolume2->setBarColorEnd(QColor(238, 238, 0));

    ui->barVolume3->setBarColorStart(QColor(24, 189, 155));
    ui->barVolume3->setBarColorMid(QColor(140, 238, 237));
    ui->barVolume3->setBarColorEnd(QColor("#2E8B57"));

    ui->barVolume4->setBarColorStart(QColor("#8A2BE2"));
    ui->barVolume4->setBarColorMid(QColor("#836FFF"));
    ui->barVolume4->setBarColorEnd(QColor("#7B68EE"));

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmBarVolume::updateValue()
{
    ui->barVolume1->setValue(qrand() % 10);
    ui->barVolume2->setValue(qrand() % 10);
    ui->barVolume3->setValue(qrand() % 10);
    ui->barVolume4->setValue(qrand() % 10);
    ui->barVolume5->setValue(qrand() % 10);
}
