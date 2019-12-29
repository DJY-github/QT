#pragma execution_character_set("utf-8")

#include "frmgaugecar.h"
#include "ui_frmgaugecar.h"
#include "gaugecar.h"

frmGaugeCar::frmGaugeCar(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeCar)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeCar::~frmGaugeCar()
{
    delete ui;
}

void frmGaugeCar::initForm()
{
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeCar, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
    //ui->gaugeCar->setCircleWidth(30);
    ui->ckAnimation->setChecked(true);
}

void frmGaugeCar::on_cboxPieStyle_currentIndexChanged(int index)
{
    ui->gaugeCar->setPieStyle((GaugeCar::PieStyle)index);
}

void frmGaugeCar::on_cboxPointerStyle_currentIndexChanged(int index)
{
    ui->gaugeCar->setPointerStyle((GaugeCar::PointerStyle)index);
}

void frmGaugeCar::on_ckAnimation_stateChanged(int arg1)
{
    ui->gaugeCar->setAnimation(arg1 != 0);
}
