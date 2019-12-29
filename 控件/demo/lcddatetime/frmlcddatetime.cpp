#pragma execution_character_set("utf-8")

#include "frmlcddatetime.h"
#include "ui_frmlcddatetime.h"

frmLcdDateTime::frmLcdDateTime(QWidget *parent) : QWidget(parent), ui(new Ui::frmLcdDateTime)
{
    ui->setupUi(this);
    this->initForm();
}

frmLcdDateTime::~frmLcdDateTime()
{
    delete ui;
}

void frmLcdDateTime::initForm()
{

}
