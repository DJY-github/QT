#pragma execution_character_set("utf-8")

#include "frmgaugecircle.h"
#include "ui_frmgaugecircle.h"

frmGaugeCircle::frmGaugeCircle(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeCircle)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeCircle::~frmGaugeCircle()
{
    delete ui;
}

void frmGaugeCircle::initForm()
{    
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeSimple, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
