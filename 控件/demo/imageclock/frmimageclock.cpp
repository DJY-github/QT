#pragma execution_character_set("utf-8")

#include "frmimageclock.h"
#include "ui_frmimageclock.h"

frmImageClock::frmImageClock(QWidget *parent) : QWidget(parent), ui(new Ui::frmImageClock)
{
    ui->setupUi(this);
    this->initForm();
}

frmImageClock::~frmImageClock()
{
    delete ui;
}

void frmImageClock::initForm()
{
    ui->imageClock1->setClockStyle(ImageClock::ClockStyle_Trad);
    ui->imageClock2->setClockStyle(ImageClock::ClockStyle_System);
    ui->imageClock3->setClockStyle(ImageClock::ClockStyle_Modern);
    ui->imageClock4->setClockStyle(ImageClock::ClockStyle_Flower);

    ui->imageClock2->setSecondStyle(ImageClock::SecondStyle_Spring);
    ui->imageClock3->setSecondStyle(ImageClock::SecondStyle_Continue);
}
