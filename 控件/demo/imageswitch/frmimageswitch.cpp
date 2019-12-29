﻿#pragma execution_character_set("utf-8")

#include "frmimageswitch.h"
#include "ui_frmimageswitch.h"

frmImageSwitch::frmImageSwitch(QWidget *parent) : QWidget(parent), ui(new Ui::frmImageSwitch)
{
    ui->setupUi(this);
    this->initForm();
}

frmImageSwitch::~frmImageSwitch()
{
    delete ui;
}

void frmImageSwitch::initForm()
{
    ui->imageSwitch1->setChecked(true);
    ui->imageSwitch2->setChecked(true);
    ui->imageSwitch3->setChecked(true);
    ui->imageSwitch1->setFixedSize(87, 28);
    ui->imageSwitch2->setFixedSize(87, 28);
    ui->imageSwitch3->setFixedSize(87, 28);
    ui->imageSwitch1->setButtonStyle(ImageSwitch::ButtonStyle_1);
    ui->imageSwitch2->setButtonStyle(ImageSwitch::ButtonStyle_2);
    ui->imageSwitch3->setButtonStyle(ImageSwitch::ButtonStyle_3);
}
