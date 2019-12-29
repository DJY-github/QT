#pragma execution_character_set("utf-8")

#include "frmgaugenet.h"
#include "ui_frmgaugenet.h"

frmGaugeNet::frmGaugeNet(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeNet)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeNet::~frmGaugeNet()
{
    delete ui;
}

void frmGaugeNet::initForm()
{
    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/bg2.png);}");

    ui->gaugeNet->setArcColor(QColor(0, 255, 255));
    ui->gaugeNet->setScaleColor(QColor("#00E5EE"));
    ui->gaugeNet->setScaleNumColor(QColor(85, 255, 255));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeNet, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
