#pragma execution_character_set("utf-8")

#include "frmprogressring.h"
#include "ui_frmprogressring.h"

frmProgressRing::frmProgressRing(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressRing)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressRing::~frmProgressRing()
{
    delete ui;
}

void frmProgressRing::initForm()
{
    ui->progressRing2->setRingColor(QColor(71, 164, 233));
    ui->progressRing2->setShowPercent(true);
    ui->progressRing2->setRingPadding(8);
    ui->progressRing2->setRingWidth(30);

    ui->progressRing3->setRingColor(QColor(214, 77, 84));
    ui->progressRing3->setShowPercent(true);
    ui->progressRing3->setRingPadding(0);
    ui->progressRing3->setRingWidth(5);

    ui->progressRing4->setAlarmMode(1);
    ui->progressRing4->setStartAngle(90);

    ui->progressRing5->setBgColor(QColor(255, 255, 255));
    ui->progressRing5->setRingColor(QColor(77, 206, 247));
    ui->progressRing5->setRingBgColor(QColor(214, 77, 84));
    ui->progressRing5->setShowPercent(true);
    ui->progressRing5->setRingPadding(8);
    ui->progressRing5->setRingWidth(30);

    ui->progressRing6->setCircleColor(QColor(0, 0, 0, 0));
    ui->progressRing6->setShowPercent(true);
    ui->progressRing6->setRingPadding(0);
    ui->progressRing6->setRingWidth(5);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressRing1, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressRing2, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressRing3, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressRing4, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressRing5, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->progressRing6, SLOT(setValue(int)));

    ui->horizontalSlider->setValue(65);
    ui->cboxStartAngle->setCurrentIndex(2);
}

void frmProgressRing::on_ckClockWise_stateChanged(int arg1)
{
    bool ok = (arg1 != 0);
    ui->progressRing1->setClockWise(ok);
    ui->progressRing2->setClockWise(ok);
    ui->progressRing3->setClockWise(ok);
    ui->progressRing4->setClockWise(ok);
    ui->progressRing5->setClockWise(ok);
    ui->progressRing6->setClockWise(ok);
}

void frmProgressRing::on_cboxStartAngle_currentIndexChanged(const QString &arg1)
{
    int startAngle = arg1.toInt();
    ui->progressRing1->setStartAngle(startAngle);
    ui->progressRing2->setStartAngle(startAngle);
    ui->progressRing3->setStartAngle(startAngle);
    ui->progressRing4->setStartAngle(startAngle);
    ui->progressRing5->setStartAngle(startAngle);
    ui->progressRing6->setStartAngle(startAngle);
}
