#include "frmgaugecompasspan.h"
#include "ui_frmgaugecompasspan.h"

frmGaugeCompassPan::frmGaugeCompassPan(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeCompassPan)
{
    ui->setupUi(this);
    ui->horizontalSlider->setValue(165);
}

frmGaugeCompassPan::~frmGaugeCompassPan()
{
    delete ui;
}

void frmGaugeCompassPan::on_horizontalSlider_valueChanged(int value)
{
    ui->gaugecompasspan->setValue(value);
}
