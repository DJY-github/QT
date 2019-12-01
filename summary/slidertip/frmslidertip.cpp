#pragma execution_character_set("utf-8")

#include "frmslidertip.h"
#include "ui_frmslidertip.h"
#include "flatui.h"

frmSliderTip::frmSliderTip(QWidget *parent) : QWidget(parent), ui(new Ui::frmSliderTip)
{
    ui->setupUi(this);
    this->initForm();
}

frmSliderTip::~frmSliderTip()
{
    delete ui;
}

void frmSliderTip::initForm()
{
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider1, 8, "#505050", "#1ABC9C", "#1ABC9C");
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider2, 8, "#505050", "#C0392B", "#C0392B");
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider3, 16, "#505050", "#2C3E50", "#2C3E50");
    FlatUI::Instance()->setSliderQss(ui->horizontalSlider4, 16, "#505050", "#8E44AD", "#8E44AD");
    FlatUI::Instance()->setSliderQss(ui->verticalSlider1, 8, "#505050", "#1ABC9C", "#1ABC9C");
    FlatUI::Instance()->setSliderQss(ui->verticalSlider2, 8, "#505050", "#8E44AD", "#8E44AD");

    ui->horizontalSlider1->setBackground("#1ABC9C");
    ui->horizontalSlider2->setBackground("#C0392B");
    ui->horizontalSlider3->setBackground("#2C3E50");
    ui->horizontalSlider4->setBackground("#8E44AD");
    ui->verticalSlider1->setBackground("#1ABC9C");
    ui->verticalSlider2->setBackground("#1ABC9C");

    ui->horizontalSlider1->setArrowStyle(SliderTip::ArrowStyle_Bottom);
    ui->horizontalSlider2->setArrowStyle(SliderTip::ArrowStyle_Top);
    ui->horizontalSlider3->setArrowStyle(SliderTip::ArrowStyle_Bottom);
    ui->horizontalSlider4->setArrowStyle(SliderTip::ArrowStyle_Top);
    ui->verticalSlider1->setArrowStyle(SliderTip::ArrowStyle_Right);
    ui->verticalSlider2->setArrowStyle(SliderTip::ArrowStyle_Left);

    QFont font;
    font.setPixelSize(20);
    ui->horizontalSlider3->setLabTipFont(font);
    ui->horizontalSlider4->setLabTipFont(font);
    ui->horizontalSlider3->setUnit("毫秒");
    ui->horizontalSlider4->setUnit(" cm");

    ui->horizontalSlider3->setFixedHeight(30);
    ui->horizontalSlider4->setFixedHeight(30);
    ui->horizontalSlider3->setLabTipWidth(100);
    ui->horizontalSlider4->setLabTipWidth(100);
    ui->horizontalSlider3->setLabTipHeight(45);
    ui->horizontalSlider4->setLabTipHeight(45);
    ui->verticalSlider1->setLabTipWidth(40);
    ui->verticalSlider2->setLabTipWidth(40);

    ui->horizontalSlider1->setValue(20);
    ui->horizontalSlider2->setValue(50);
    ui->horizontalSlider3->setValue(40);
    ui->horizontalSlider4->setValue(70);
    ui->verticalSlider1->setValue(20);
    ui->verticalSlider2->setValue(50);

    ui->horizontalSlider3->setRange(0, 150);
}
