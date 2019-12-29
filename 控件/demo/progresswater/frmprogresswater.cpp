#pragma execution_character_set("utf-8")

#include "frmprogresswater.h"
#include "ui_frmprogresswater.h"
#include "progresswater.h"

frmProgressWater::frmProgressWater(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressWater)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressWater::~frmProgressWater()
{
    delete ui;
}

void frmProgressWater::initForm()
{
    ui->progressWater1->setUsedColor(QColor(255, 107, 107));
    ui->progressWater2->setUsedColor(QColor(24, 189, 155));

    connect(ui->sliderValue, SIGNAL(valueChanged(int)), ui->progressWater1, SLOT(setValue(int)));
    connect(ui->sliderValue, SIGNAL(valueChanged(int)), ui->progressWater2, SLOT(setValue(int)));

    ui->sliderValue->setValue(66);
    ui->sliderBorderWidth->setValue(10);
    ui->sliderWaterHeight->setValue(5);
    ui->sliderWaterDensity->setValue(2);
    ui->cboxPercentStyle->setCurrentIndex(1);
}

void frmProgressWater::on_sliderBorderWidth_valueChanged(int value)
{
    double v = (double)value;
    ui->progressWater1->setBorderWidth(v);
    ui->progressWater2->setBorderWidth(v);
}

void frmProgressWater::on_sliderWaterHeight_valueChanged(int value)
{
    double v = (double)value / 100;
    ui->progressWater1->setWaterHeight(v);
    ui->progressWater2->setWaterHeight(v);
}

void frmProgressWater::on_sliderWaterDensity_valueChanged(int value)
{
    double v = (double)value;
    ui->progressWater1->setWaterDensity(v);
    ui->progressWater2->setWaterDensity(v);
}

void frmProgressWater::on_ckReverse_stateChanged(int arg1)
{
    bool reverse = (arg1 != 0);
    ui->progressWater1->setReverse(reverse);
    ui->progressWater2->setReverse(reverse);
}

void frmProgressWater::on_cboxPercentStyle_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "矩形风格") {
        ui->progressWater1->setPercentStyle(ProgressWater::PercentStyle_Rect);
        ui->progressWater2->setPercentStyle(ProgressWater::PercentStyle_Rect);
    } else if (arg1 == "圆形风格") {
        ui->progressWater1->setPercentStyle(ProgressWater::PercentStyle_Circle);
        ui->progressWater2->setPercentStyle(ProgressWater::PercentStyle_Circle);
    } else if (arg1 == "椭圆风格") {
        ui->progressWater1->setPercentStyle(ProgressWater::PercentStyle_Ellipse);
        ui->progressWater2->setPercentStyle(ProgressWater::PercentStyle_Ellipse);
    } else if (arg1 == "圆柱风格") {
        ui->progressWater1->setPercentStyle(ProgressWater::PercentStyle_Cylinder);
        ui->progressWater2->setPercentStyle(ProgressWater::PercentStyle_Cylinder);
    }
}

void frmProgressWater::on_btnPause_clicked()
{
    if (ui->btnPause->text() == "暂停") {
        ui->progressWater1->stop();
        ui->progressWater2->stop();
        ui->btnPause->setText("启动");
    } else {
        ui->progressWater1->start();
        ui->progressWater2->start();
        ui->btnPause->setText("暂停");
    }
}
