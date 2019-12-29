#include "frmgaugeweather.h"
#include "ui_frmgaugeweather.h"

frmGaugeWeather::frmGaugeWeather(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeWeather)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeWeather::~frmGaugeWeather()
{
    delete ui;
}

void frmGaugeWeather::initForm()
{
    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/bg1.jpg);}");
    ui->horizontalSlider1->setValue(65);
    ui->horizontalSlider2->setValue(28);
}

void frmGaugeWeather::on_horizontalSlider1_valueChanged(int value)
{
    ui->gaugeWeather->setOuterValue(value);
}

void frmGaugeWeather::on_horizontalSlider2_valueChanged(int value)
{
    ui->gaugeWeather->setInnerValue(value);
}

void frmGaugeWeather::on_comboBox_currentIndexChanged(int index)
{
    GaugeWeather::WeatherType type = (GaugeWeather::WeatherType)index;
    ui->gaugeWeather->setWeatherType(type);
}

void frmGaugeWeather::on_ckAnimation_stateChanged(int arg1)
{
    ui->gaugeWeather->setAnimation(arg1 != 0);
}
