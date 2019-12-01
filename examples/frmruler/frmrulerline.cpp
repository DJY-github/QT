#pragma execution_character_set("utf-8")

#include "frmrulerline.h"
#include "ui_frmrulerline.h"

frmRulerLine::frmRulerLine(QWidget *parent) : QWidget(parent), ui(new Ui::frmRulerLine)
{
    ui->setupUi(this);
    this->initForm();
}

frmRulerLine::~frmRulerLine()
{
    delete ui;
}

void frmRulerLine::initForm()
{
    ui->rulerLine2->setPointerWidth(5);
    ui->rulerLine2->setPointerColor(QColor(255, 107, 107));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->rulerLine1, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->rulerLine2, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
