#pragma execution_character_set("utf-8")

#include "frmroundlogo.h"
#include "ui_frmroundlogo.h"

frmRoundLogo::frmRoundLogo(QWidget *parent) : QWidget(parent), ui(new Ui::frmRoundLogo)
{
    ui->setupUi(this);
    this->initForm();
}

frmRoundLogo::~frmRoundLogo()
{
    delete ui;
}

void frmRoundLogo::initForm()
{

}
