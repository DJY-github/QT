#pragma execution_character_set("utf-8")

#include "frmrulerscale.h"
#include "ui_frmrulerscale.h"
#include "qdatetime.h"
#include "qtimer.h"

frmRulerScale::frmRulerScale(QWidget *parent) : QWidget(parent), ui(new Ui::frmRulerScale)
{
    ui->setupUi(this);
    this->initForm();
}

frmRulerScale::~frmRulerScale()
{
    delete ui;
}

void frmRulerScale::initForm()
{
connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->rulerScale,SLOT(setValue(int)));
}
