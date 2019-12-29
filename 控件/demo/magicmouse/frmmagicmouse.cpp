#pragma execution_character_set("utf-8")

#include "frmmagicmouse.h"
#include "ui_frmmagicmouse.h"

frmMagicMouse::frmMagicMouse(QWidget *parent) : QWidget(parent), ui(new Ui::frmMagicMouse)
{
    ui->setupUi(this);
    this->initForm();
}

frmMagicMouse::~frmMagicMouse()
{
    delete ui;
}

void frmMagicMouse::initForm()
{
    ui->horizontalSlider->setRange(0, 360);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->magicMouse, SLOT(setAngle(int)));
}
