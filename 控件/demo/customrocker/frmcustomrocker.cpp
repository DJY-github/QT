#pragma execution_character_set("utf-8")

#include "frmcustomrocker.h"
#include "ui_frmcustomrocker.h"

frmCustomRocker::frmCustomRocker(QWidget *parent) : QWidget(parent), ui(new Ui::frmCustomRocker)
{
    ui->setupUi(this);
    connect(ui->customRocker, SIGNAL(moveAngle(double)), this, SLOT(moveAngle(double)));
}

frmCustomRocker::~frmCustomRocker()
{
    delete ui;
}

void frmCustomRocker::moveAngle(double angle)
{
    ui->labAngle->setText(QString("当前角度: %1").arg(angle));
}

void frmCustomRocker::on_ckOnline_stateChanged(int arg1)
{
    ui->customRocker->setOnline(arg1 != 0);
}
