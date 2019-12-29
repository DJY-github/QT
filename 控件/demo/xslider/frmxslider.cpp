#pragma execution_character_set("utf-8")

#include "frmxslider.h"
#include "ui_frmxslider.h"

frmXSlider::frmXSlider(QWidget *parent) : QWidget(parent), ui(new Ui::frmXSlider)
{
    ui->setupUi(this);
    this->initForm();
}

frmXSlider::~frmXSlider()
{
    delete ui;
}

void frmXSlider::initForm()
{
    ui->horizontalSlider->setValue(56);
    ui->verticalSlider->setValue(88);

    ui->horizontalSlider->setSliderHeight(20);
    ui->horizontalSlider->setNormalColor("#B3B3C6");
    ui->horizontalSlider->setGrooveColor("#7C7C96");
    ui->horizontalSlider->setHandleBorderColor("#65657A");
    ui->horizontalSlider->setHandleColor("#FFCC33");
    ui->horizontalSlider->setTextColor("#000000");
}
