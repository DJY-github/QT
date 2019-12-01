#pragma execution_character_set("utf-8")

#include "frmimagepower.h"
#include "ui_frmimagepower.h"

frmImagePower::frmImagePower(QWidget *parent) : QWidget(parent), ui(new Ui::frmImagePower)
{
    ui->setupUi(this);
    this->initForm();
}

frmImagePower::~frmImagePower()
{
    delete ui;
}

void frmImagePower::initForm()
{
    ui->imagePower1->setValue(0);
    ui->imagePower2->setValue(1);
    ui->imagePower3->setValue(2);
    ui->imagePower4->setValue(3);
    ui->imagePower5->setValue(4);
    ui->imagePower6->setValue(5);
}
