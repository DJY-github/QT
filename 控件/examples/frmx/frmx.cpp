#include "frmx.h"
#include "ui_frmx.h"

#include "frmxslider.h"
#include "frmxlistwidget.h"
#include "frmxlistwidgetvs.h"
#include "frmxlistwidgetvt.h"
#include "frmxprogressbar.h"

frmX::frmX(QWidget *parent) : QWidget(parent), ui(new Ui::frmX)
{
    ui->setupUi(this);
    this->initForm();
}

frmX::~frmX()
{
    delete ui;
}

void frmX::initForm()
{
    ui->stackedWidget->addWidget(new frmXSlider);
    ui->stackedWidget->addWidget(new frmXListWidget);
    ui->stackedWidget->addWidget(new frmXListWidgetVS);
    ui->stackedWidget->addWidget(new frmXListWidgetVT);
    ui->stackedWidget->addWidget(new frmXProgressBar);
}

void frmX::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
