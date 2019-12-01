#pragma execution_character_set("utf-8")

#include "frmgaugeplane.h"
#include "ui_frmgaugeplane.h"

frmGaugePlane::frmGaugePlane(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugePlane)
{
    ui->setupUi(this);
}

frmGaugePlane::~frmGaugePlane()
{
    delete ui;
}


void frmGaugePlane::on_horizontalSlider_valueChanged(int value)
{
    ui->gaugePlane->setDegValue(value);
}

void frmGaugePlane::on_verticalSlider_valueChanged(int value)
{
    ui->gaugePlane->setRollValue(value);
}
