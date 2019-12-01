#pragma execution_character_set("utf-8")

#include "frmmagicfish.h"
#include "ui_frmmagicfish.h"

frmMagicFish::frmMagicFish(QWidget *parent) : QWidget(parent), ui(new Ui::frmMagicFish)
{
    ui->setupUi(this);
    this->initForm();
}

frmMagicFish::~frmMagicFish()
{
    delete ui;
}

void frmMagicFish::initForm()
{
    ui->magicFish->setBaseColor(QColor(15, 152, 160));
    ui->horizontalSlider->setRange(0, 360);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->magicFish, SLOT(setCurrentAngle(int)));
    connect(ui->comboBox, SIGNAL(colorChanged(QColor)), ui->magicFish, SLOT(setBaseColor(QColor)));
}
