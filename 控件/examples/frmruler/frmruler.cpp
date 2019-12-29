#include "frmruler.h"
#include "ui_frmruler.h"

#include "frmrulerbar.h"
#include "frmrulerline.h"
#include "frmrulerslider.h"
#include "frmrulerdouble.h"
#include "frmrulertemp.h"
#include "frmrulerscale.h"
#include "frmrulerprogress.h"

frmRuler::frmRuler(QWidget *parent) : QWidget(parent), ui(new Ui::frmRuler)
{
    ui->setupUi(this);
    this->initForm();
}

frmRuler::~frmRuler()
{
    delete ui;
}

void frmRuler::initForm()
{
    ui->stackedWidget->addWidget(new frmRulerBar);
    ui->stackedWidget->addWidget(new frmRulerLine);
    ui->stackedWidget->addWidget(new frmRulerSlider);
    ui->stackedWidget->addWidget(new frmRulerDouble);
    ui->stackedWidget->addWidget(new frmRulerTemp);
    ui->stackedWidget->addWidget(new frmRulerScale);
    ui->stackedWidget->addWidget(new frmRulerProgress);
}

void frmRuler::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
