#include "frmgaugedecibel.h"
#include "ui_frmgaugedecibel.h"

frmGaugeDecibel::frmGaugeDecibel(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeDecibel)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeDecibel::~frmGaugeDecibel()
{
    delete ui;
}

void frmGaugeDecibel::initForm()
{
    ui->horizontalSlider->setValue(65);
}

void frmGaugeDecibel::on_horizontalSlider_valueChanged(int value)
{
    ui->gaugeDecibel->setValue(value);
}
