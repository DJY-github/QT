#pragma execution_character_set("utf-8")

#include "frmgaugerange.h"
#include "ui_frmgaugerange.h"

frmGaugeRange::frmGaugeRange(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeRange)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeRange::~frmGaugeRange()
{
    delete ui;
}

void frmGaugeRange::initForm()
{
    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/bg1.jpg);}");

    ui->gaugeRange1->setUsedColor(QColor(0, 255, 255));
    ui->gaugeRange1->setFreeColor(QColor(255, 255, 255));
    ui->gaugeRange1->setTextColor(QColor(0, 170, 127));
    ui->gaugeRange1->setRangeTextColor(QColor(0, 255, 255));

    ui->gaugeRange2->setUsedColor(QColor(255, 107, 107));
    ui->gaugeRange2->setFreeColor(QColor(255, 255, 255));
    ui->gaugeRange2->setTextColor(QColor(0, 255, 255));
    ui->gaugeRange2->setRangeTextColor(QColor(0, 255, 255));
    ui->gaugeRange2->setRangeStyle(GaugeRange::RangeStyle_Circle);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeRange1, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeRange2, SLOT(setValue(int)));
    connect(ui->horizontalSlider1, SIGNAL(valueChanged(int)), ui->gaugeRange1, SLOT(setLeftValue(int)));
    connect(ui->horizontalSlider1, SIGNAL(valueChanged(int)), ui->gaugeRange2, SLOT(setLeftValue(int)));
    connect(ui->horizontalSlider2, SIGNAL(valueChanged(int)), ui->gaugeRange1, SLOT(setRightValue(int)));
    connect(ui->horizontalSlider2, SIGNAL(valueChanged(int)), ui->gaugeRange2, SLOT(setRightValue(int)));

    ui->horizontalSlider->setRange(0, 100);
    ui->horizontalSlider1->setRange(0, 100);
    ui->horizontalSlider2->setRange(0, 100);

    ui->horizontalSlider->setValue(50);
    ui->horizontalSlider1->setValue(40);
    ui->horizontalSlider2->setValue(60);
}
