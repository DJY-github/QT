#pragma execution_character_set("utf-8")

#include "frmsliderselect.h"
#include "ui_frmsliderselect.h"
#include "sliderselect.h"

frmSliderSelect::frmSliderSelect(QWidget *parent) : QWidget(parent), ui(new Ui::frmSliderSelect)
{
    ui->setupUi(this);
    this->initForm();
}

frmSliderSelect::~frmSliderSelect()
{
    delete ui;
}

void frmSliderSelect::initForm()
{
    ui->sliderSelect2->setUsedColor(QColor("#FF6B6B"));
    ui->sliderSelect3->setUsedColor(QColor("#3498DB"));

    sliders << ui->sliderSelect1 << ui->sliderSelect2 << ui->sliderSelect3;

    foreach (SliderSelect *slider, sliders) {
        connect(ui->sliderLeftValue, SIGNAL(valueChanged(int)), slider, SLOT(setLeftValue(int)));
        connect(ui->sliderRightValue, SIGNAL(valueChanged(int)), slider, SLOT(setRightValue(int)));
        connect(ui->sliderRangeValue, SIGNAL(valueChanged(int)), slider, SLOT(setRangeValue(int)));
        connect(slider, SIGNAL(valueChanged(int, int)), this, SLOT(valueChanged(int, int)));
        connect(slider, SIGNAL(rangeChanged(int)), this, SLOT(rangeChanged(int)));
    }

    ui->sliderLeftValue->setValue(-20);
    ui->sliderRightValue->setValue(20);
    ui->sliderRangeValue->setValue(40);
}

void frmSliderSelect::valueChanged(int leftValue, int rightValue)
{
    ui->labValueLeft->setText(QString::number(leftValue));
    ui->labValueRight->setText(QString::number(rightValue));
}

void frmSliderSelect::rangeChanged(int rangeValue)
{
    ui->labValueRange->setText(QString::number(rangeValue));
}
