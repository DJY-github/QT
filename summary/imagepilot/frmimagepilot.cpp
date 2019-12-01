#pragma execution_character_set("utf-8")

#include "frmimagepilot.h"
#include "ui_frmimagepilot.h"

frmImagePilot::frmImagePilot(QWidget *parent) : QWidget(parent), ui(new Ui::frmImagePilot)
{
    ui->setupUi(this);
    this->initForm();
}

frmImagePilot::~frmImagePilot()
{
    delete ui;
}

void frmImagePilot::initForm()
{
    ui->imagePilot1->setPilotStyle(ImagePilot::PilotStyle_Blue);
    ui->imagePilot2->setPilotStyle(ImagePilot::PilotStyle_Gray);
    ui->imagePilot3->setPilotStyle(ImagePilot::PilotStyle_Green);
    ui->imagePilot4->setPilotStyle(ImagePilot::PilotStyle_Red);
    ui->imagePilot5->setPilotStyle(ImagePilot::PilotStyle_Yellow);
    ui->imagePilot6->setPilotStyle(ImagePilot::PilotStyle_Blue);
}
