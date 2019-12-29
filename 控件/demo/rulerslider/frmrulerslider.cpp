#pragma execution_character_set("utf-8")

#include "frmrulerslider.h"
#include "ui_frmrulerslider.h"

frmRulerSlider::frmRulerSlider(QWidget *parent) : QWidget(parent), ui(new Ui::frmRulerSlider)
{
    ui->setupUi(this);
    this->initForm();
}

frmRulerSlider::~frmRulerSlider()
{
    delete ui;
}

void frmRulerSlider::initForm()
{
    ui->rulerSlider1->setValue(25);

    ui->rulerSlider2->setRange(-50, 50);
    ui->rulerSlider2->setValue(25);
    ui->rulerSlider2->setShortStep(2);
    ui->rulerSlider2->setSliderColorTop(QColor(255, 107, 107));

    ui->rulerSlider3->setRange(0, 200);
    ui->rulerSlider3->setValue(120);
    ui->rulerSlider3->setShortStep(5);
    ui->rulerSlider3->setLongStep(20);
    ui->rulerSlider3->setSliderColorTop(QColor(24, 188, 155));
}
