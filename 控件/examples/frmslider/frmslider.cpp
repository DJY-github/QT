#include "frmslider.h"
#include "ui_frmslider.h"

#include "frmsliderselect.h"
#include "frmsliderrange.h"
#include "frmslidertip.h"

frmSlider::frmSlider(QWidget *parent) : QWidget(parent), ui(new Ui::frmSlider)
{
    ui->setupUi(this);
    this->initForm();
}

frmSlider::~frmSlider()
{
    delete ui;
}

void frmSlider::initForm()
{
    ui->stackedWidget->addWidget(new frmSliderSelect);
    ui->stackedWidget->addWidget(new frmSliderRange);
    ui->stackedWidget->addWidget(new frmSliderTip);
}

void frmSlider::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
