#pragma execution_character_set("utf-8")

#include "frmwaveplot.h"
#include "ui_frmwaveplot.h"

frmWavePlot::frmWavePlot(QWidget *parent) : QWidget(parent), ui(new Ui::frmWavePlot)
{
    ui->setupUi(this);
    this->initForm();
}

frmWavePlot::~frmWavePlot()
{
    delete ui;
}

void frmWavePlot::initForm()
{
    ui->horizontalSlider1->setValue(100);
    ui->horizontalSlider2->setValue(5);
    ui->horizontalSlider3->setValue(5);

    ui->widgetPlot->setLineColor(QColor(255, 107, 107));
    ui->widgetPlot->start();
}

void frmWavePlot::on_horizontalSlider1_valueChanged(int value)
{
    ui->widgetPlot->setInterval(value);
}

void frmWavePlot::on_horizontalSlider2_valueChanged(int value)
{
    ui->widgetPlot->setWaterHeight((double)value / 100);
}

void frmWavePlot::on_horizontalSlider3_valueChanged(int value)
{
    ui->widgetPlot->setWaterDensity(value);
}
