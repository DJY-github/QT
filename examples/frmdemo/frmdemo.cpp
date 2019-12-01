#pragma execution_character_set("utf-8")

#include "frmdemo.h"
#include "ui_frmdemo.h"

#include "xform.h"
#include "composition.h"
#include "gradients.h"
#include "pathdeform.h"
#include "pathstroke.h"

frmDemo::frmDemo(QWidget *parent) : QWidget(parent), ui(new Ui::frmDemo)
{
    ui->setupUi(this);
    this->initForm();
}

frmDemo::~frmDemo()
{
    delete ui;
}

void frmDemo::initForm()
{
    ui->stackedWidget->addWidget(new XFormWidget);
    ui->stackedWidget->addWidget(new CompositionWidget);
    ui->stackedWidget->addWidget(new GradientWidget);
    ui->stackedWidget->addWidget(new PathDeformWidget);
    ui->stackedWidget->addWidget(new PathStrokeWidget);
}

void frmDemo::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
