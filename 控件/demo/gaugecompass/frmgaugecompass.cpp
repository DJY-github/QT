#pragma execution_character_set("utf-8")

#include "frmgaugecompass.h"
#include "ui_frmgaugecompass.h"

frmGaugeCompass::frmGaugeCompass(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeCompass)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeCompass::~frmGaugeCompass()
{
    delete ui;
}

void frmGaugeCompass::initForm()
{    
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeCompass, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
