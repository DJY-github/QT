#include "frmbar.h"
#include "ui_frmbar.h"

#include "frmbarvolume.h"
#include "frmbarvumeter.h"

frmBar::frmBar(QWidget *parent) : QWidget(parent), ui(new Ui::frmBar)
{
    ui->setupUi(this);
    this->initForm();
}

frmBar::~frmBar()
{
    delete ui;
}

void frmBar::initForm()
{
    ui->stackedWidget->addWidget(new frmBarVolume);
    ui->stackedWidget->addWidget(new frmBarVUMeter);
}

void frmBar::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
