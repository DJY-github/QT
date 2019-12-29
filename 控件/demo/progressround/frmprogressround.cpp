#pragma execution_character_set("utf-8")

#include "frmprogressround.h"
#include "ui_frmprogressround.h"
#include "progressround.h"

frmProgressRound::frmProgressRound(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressRound)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressRound::~frmProgressRound()
{
    delete ui;
}

void frmProgressRound::initForm()
{
    //默认样式+值格式+圆环颜色
    ui->progressRound1->setBgColor(QColor(0, 85, 127));
    ui->progressRound1->setTextColor(QColor(24, 189, 155));
    ui->progressRound1->setBaseColor(QColor(250, 250, 250));
    ui->progressRound1->setInnerBgColor(QColor(255, 255, 255));
    ui->progressRound1->setBorderColor(QColor(24, 189, 155));

    ui->progressRound1->setFormat("%v");
    ui->progressRound1->setPrecision(0);
    ui->progressRound1->setNullPosition(0);
    connectToSlider(ui->progressRound1);

    //饼状图+背景色+起始位置
    ui->progressRound2->setBgColor(QColor(0, 85, 127));
    ui->progressRound2->setTextColor(QColor(250, 250, 250));
    ui->progressRound2->setBaseColor(QColor(97, 117, 118));
    ui->progressRound2->setProgressColor(QColor(255, 107, 107));
    ui->progressRound2->setBorderColor(QColor(255, 107, 107));

    ui->progressRound2->setNullPosition(0);
    ui->progressRound2->setBarStyle(ProgressRound::BarStyle_Pie);
    connectToSlider(ui->progressRound2);

    //线状图+线颜色
    ui->progressRound3->setBgColor(QColor(0, 85, 127));
    ui->progressRound3->setTextColor(QColor(250, 250, 250));
    ui->progressRound3->setBaseColor(QColor(255, 255, 255));
    ui->progressRound3->setProgressColor(QColor(100, 184, 255));

    ui->progressRound3->setBarStyle(ProgressRound::BarStyle_Line);
    ui->progressRound3->setOutlinePenWidth(5);
    ui->progressRound3->setDataPenWidth(5);
    connectToSlider(ui->progressRound3);

    //默认样式+自定义颜色组合
    ui->progressRound4->setBgColor(QColor(0, 85, 127));
    ui->progressRound4->setTextColor(QColor(255, 255, 255));
    ui->progressRound4->setBaseColor(QColor(250, 250, 250));
    ui->progressRound4->setInnerBgColor(QColor(180, 180, 180));
    ui->progressRound4->setProgressColor(QColor(255, 107, 107));
    ui->progressRound4->setBorderColor(QColor(255, 107, 107));

    ui->progressRound4->setNullPosition(180);
    ui->progressRound4->setPrecision(0);

    QGradientStops gradientPoints4;
    gradientPoints4 << QGradientStop(0, QColor(254, 64, 64)) << QGradientStop(0.5, QColor(255, 127, 36)) << QGradientStop(1, QColor(238, 238, 0));
    ui->progressRound4->setGradientData(gradientPoints4);
    connectToSlider(ui->progressRound4);

    //饼图样式+自定义颜色组合
    ui->progressRound5->setBgColor(QColor(0, 85, 127));
    ui->progressRound5->setTextColor(QColor(255, 255, 255));
    ui->progressRound5->setBaseColor(QColor(255, 107, 107));
    ui->progressRound5->setInnerBgColor(QColor(180, 180, 180));
    ui->progressRound5->setProgressColor(QColor(24, 189, 155));
    ui->progressRound5->setBorderColor(QColor(24, 189, 155));

    ui->progressRound5->setNullPosition(180);
    ui->progressRound5->setBarStyle(ProgressRound::BarStyle_Pie);
    connectToSlider(ui->progressRound5);

    //线状样式+自定义边框宽度
    ui->progressRound6->setBgColor(QColor(0, 85, 127));
    ui->progressRound6->setTextColor(QColor(250, 250, 250));
    ui->progressRound6->setBaseColor(QColor(255, 255, 255));
    ui->progressRound6->setProgressColor(QColor(100, 184, 255));

    ui->progressRound6->setPrecision(2);
    ui->progressRound6->setBarStyle(ProgressRound::BarStyle_Line);
    ui->progressRound6->setOutlinePenWidth(18);
    ui->progressRound6->setDataPenWidth(10);
    ui->progressRound6->setClockWise(false);
    connectToSlider(ui->progressRound6);
}

void frmProgressRound::connectToSlider(ProgressRound *bar)
{
    bar->setRange(ui->slider->minimum(), ui->slider->maximum());
    bar->setValue(ui->slider->value());
    connect(ui->slider, SIGNAL(valueChanged(int)), bar, SLOT(setValue(int)));
}
