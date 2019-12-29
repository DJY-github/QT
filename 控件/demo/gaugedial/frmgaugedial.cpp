#pragma execution_character_set("utf-8")

#include "frmgaugedial.h"
#include "ui_frmgaugedial.h"
#include "gaugedial.h"

frmGaugeDial::frmGaugeDial(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeDial)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeDial::~frmGaugeDial()
{
    delete ui;
}

void frmGaugeDial::initForm()
{
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeDial, SLOT(setValue(int)));
    connect(ui->gaugeDial, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
    ui->ckShowValue->setChecked(true);
}

void frmGaugeDial::on_cboxPointerStyle_currentIndexChanged(int index)
{
    ui->gaugeDial->setPointerStyle((GaugeDial::PointerStyle)index);
}

void frmGaugeDial::on_ckShowValue_stateChanged(int arg1)
{
    ui->gaugeDial->setShowValue(arg1 != 0);
}
