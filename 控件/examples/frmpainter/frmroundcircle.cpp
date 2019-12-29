#pragma execution_character_set("utf-8")

#include "frmroundcircle.h"
#include "ui_frmroundcircle.h"

frmRoundCircle::frmRoundCircle(QWidget *parent) : QWidget(parent), ui(new Ui::frmRoundCircle)
{
    ui->setupUi(this);
    this->initForm();
}

frmRoundCircle::~frmRoundCircle()
{
    delete ui;
}

void frmRoundCircle::initForm()
{
    ui->roundCircle2->setBgColorStart(QColor(31, 31, 31));
    ui->roundCircle2->setBgColorEnd(QColor(91, 91, 91));
    ui->roundCircle2->setPieColor1Start(QColor(34, 139, 34));
    ui->roundCircle2->setPieColor1End(QColor(46, 138, 87));
    ui->roundCircle2->setPieColor2Start(QColor(240, 255, 255));
    ui->roundCircle2->setPieColor2End(QColor(248, 249, 254));

    ui->roundCircle3->setClockWise(false);
    ui->roundCircle3->setPieColor1Start(QColor(254, 48, 48));
    ui->roundCircle3->setPieColor1End(QColor(255, 69, 0));

    ui->roundCircle4->setClockWise(false);
    ui->roundCircle4->setPieColor1Start(QColor(67, 110, 238));
    ui->roundCircle4->setPieColor1End(QColor(72, 118, 255));
}
