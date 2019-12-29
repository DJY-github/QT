#pragma execution_character_set("utf-8")

#include "frmgaugesimple.h"
#include "ui_frmgaugesimple.h"
#include "gaugesimple.h"

frmGaugeSimple::frmGaugeSimple(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeSimple)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeSimple::~frmGaugeSimple()
{
    delete ui;
}

void frmGaugeSimple::initForm()
{
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeSimple, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
    ui->gaugeSimple->setAnimation(false);
}

void frmGaugeSimple::on_cboxPointerStyle_currentIndexChanged(int index)
{
    ui->gaugeSimple->setPointerStyle((GaugeSimple::PointerStyle)index);
}

void frmGaugeSimple::on_ckAnimation_stateChanged(int arg1)
{
    ui->gaugeSimple->setAnimation(arg1 != 0);
}
