#pragma execution_character_set("utf-8")

#include "frmgaugespeed.h"
#include "ui_frmgaugespeed.h"

frmGaugeSpeed::frmGaugeSpeed(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeSpeed)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeSpeed::~frmGaugeSpeed()
{
    delete ui;
}

void frmGaugeSpeed::initForm()
{
    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/bg1.jpg);}");

    ui->gaugeSpeed->setAnimation(true);
    ui->gaugeSpeed->setTextColor(QColor(0, 255, 255));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeSpeed, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
