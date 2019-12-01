#pragma execution_character_set("utf-8")

#include "frmrulerdouble.h"
#include "ui_frmrulerdouble.h"

frmRulerDouble::frmRulerDouble(QWidget *parent) : QWidget(parent), ui(new Ui::frmRulerDouble)
{
    ui->setupUi(this);
    this->initForm();
}

frmRulerDouble::~frmRulerDouble()
{
    delete ui;
}

void frmRulerDouble::initForm()
{
    ui->rulerDouble1->setMaxValue(800);
    ui->rulerDouble1->setLongStep(100);
    ui->rulerDouble1->setShortStep(20);
    ui->rulerDouble1->setMaxValueRight(800);

    ui->rulerDouble2->setMaxValue(800);
    ui->rulerDouble2->setLongStep(100);
    ui->rulerDouble2->setShortStep(20);
    ui->rulerDouble2->setLongStepRight(20);
    ui->rulerDouble2->setShortStepRight(5);
    ui->rulerDouble2->setScaleStyle(RulerDouble::ScaleStyle_Double);

    ui->verticalSlider1->setRange(0, 800);
    connect(ui->verticalSlider1, SIGNAL(valueChanged(int)), ui->rulerDouble1, SLOT(setValue(int)));
    connect(ui->verticalSlider1, SIGNAL(valueChanged(int)), ui->rulerDouble2, SLOT(setValue(int)));

    ui->verticalSlider2->setRange(0, 100);
    connect(ui->verticalSlider2, SIGNAL(valueChanged(int)), ui->rulerDouble2, SLOT(setValueRight(int)));

    connect(ui->verticalSlider3, SIGNAL(valueChanged(int)), ui->rulerDouble3, SLOT(setValue(int)));
    connect(ui->verticalSlider3, SIGNAL(valueChanged(int)), ui->rulerDouble3, SLOT(setValueRight(int)));

    ui->verticalSlider1->setValue(300);
    ui->verticalSlider2->setValue(90);
    ui->verticalSlider3->setValue(50);
}
