#pragma execution_character_set("utf-8")

#include "frmgaugeround.h"
#include "ui_frmgaugeround.h"

frmGaugeRound::frmGaugeRound(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeRound)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeRound::~frmGaugeRound()
{
    delete ui;
}

void frmGaugeRound::initForm()
{    
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeRound, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
