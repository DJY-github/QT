#pragma execution_character_set("utf-8")

#include "frmgaugecolor.h"
#include "ui_frmgaugecolor.h"
#include "gaugecolor.h"

frmGaugeColor::frmGaugeColor(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeColor)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeColor::~frmGaugeColor()
{
    delete ui;
}

void frmGaugeColor::initForm()
{
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeColor, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
    ui->ckAnimation->setChecked(true);
}

void frmGaugeColor::on_cboxPointerStyle_currentIndexChanged(int index)
{
    ui->gaugeColor->setPointerStyle((GaugeColor::PointerStyle)index);
}

void frmGaugeColor::on_ckAnimation_stateChanged(int arg1)
{
    ui->gaugeColor->setAnimation(arg1 != 0);
}
