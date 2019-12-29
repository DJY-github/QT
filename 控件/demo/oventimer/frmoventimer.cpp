#pragma execution_character_set("utf-8")

#include "frmoventimer.h"
#include "ui_frmoventimer.h"

frmOvenTimer::frmOvenTimer(QWidget *parent) : QWidget(parent), ui(new Ui::frmOvenTimer)
{
    ui->setupUi(this);
    this->initForm();
}

frmOvenTimer::~frmOvenTimer()
{
    delete ui;
}

void frmOvenTimer::initForm()
{
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->ovenTimer, SLOT(setDuration(int)));
    ui->horizontalSlider->setValue(30);
}
