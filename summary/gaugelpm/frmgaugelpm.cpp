#pragma execution_character_set("utf-8")

#include "frmgaugelpm.h"
#include "ui_frmgaugelpm.h"

frmGaugeLpm::frmGaugeLpm(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeLpm)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeLpm::~frmGaugeLpm()
{
    delete ui;
}

void frmGaugeLpm::initForm()
{
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeLpm, SLOT(setValue(int)));
    ui->horizontalSlider->setRange(0, 100);
    ui->horizontalSlider->setValue(88);
}
