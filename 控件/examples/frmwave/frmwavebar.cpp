#pragma execution_character_set("utf-8")

#include "frmwavebar.h"
#include "ui_frmwavebar.h"
#include "qdatetime.h"
#include "qtimer.h"

frmWaveBar::frmWaveBar(QWidget *parent) : QWidget(parent), ui(new Ui::frmWaveBar)
{
    ui->setupUi(this);
    this->initForm();
}

frmWaveBar::~frmWaveBar()
{
    delete ui;
}

void frmWaveBar::resizeEvent(QResizeEvent *)
{
    if (height() <= 300) {
        return;
    }

    double step = height() / 100;
    ui->waveBar1->setStep(step);
    ui->waveBar2->setStep(step);
    ui->waveBar3->setStep(step);
    ui->waveBar4->setStep(step);
    ui->waveBar5->setStep(step);
    ui->waveBar6->setStep(step);
    ui->waveBar7->setStep(step);
}

void frmWaveBar::initForm()
{
    ui->waveBar2->setBarColor(QColor(255, 107, 107));
    ui->waveBar3->setBarColor(QColor(24, 189, 155));
    ui->waveBar4->setBarColor(QColor(255, 85, 255));
    ui->waveBar5->setBarColor(QColor(255, 0, 127));
    ui->waveBar6->setBarColor(QColor(0, 255, 255));
    ui->waveBar7->setBarColor(QColor(255, 255, 0));

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmWaveBar::updateValue()
{
    ui->waveBar1->setValue(qrand() % 100);
    ui->waveBar2->setValue(qrand() % 100);
    ui->waveBar3->setValue(qrand() % 100);
    ui->waveBar4->setValue(qrand() % 100);
    ui->waveBar5->setValue(qrand() % 100);
    ui->waveBar6->setValue(qrand() % 100);
    ui->waveBar7->setValue(qrand() % 100);
}
