#pragma execution_character_set("utf-8")

#include "frmgaugewatch.h"
#include "ui_frmgaugewatch.h"

frmGaugeWatch::frmGaugeWatch(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeWatch)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeWatch::~frmGaugeWatch()
{
    delete ui;
}

void frmGaugeWatch::initForm()
{    
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeWatch, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
