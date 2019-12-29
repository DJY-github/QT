#pragma execution_character_set("utf-8")

#include "frmgaugeclock.h"
#include "ui_frmgaugeclock.h"

frmGaugeClock::frmGaugeClock(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeClock)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeClock::~frmGaugeClock()
{
    delete ui;
}

void frmGaugeClock::initForm()
{
    ui->gaugeClock2->setBackground(QColor(255, 107, 107));
    ui->gaugeClock2->setPointerHourColor(QColor(250, 250, 250));
    ui->gaugeClock2->setPointerMinColor(QColor(250, 250, 250));
    ui->gaugeClock2->setPointerSecColor(QColor(250, 250, 250));
    ui->gaugeClock2->setSecondStyle(GaugeClock::SecondStyle_Spring);
}
