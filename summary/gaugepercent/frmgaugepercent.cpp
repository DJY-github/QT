#pragma execution_character_set("utf-8")

#include "frmgaugepercent.h"
#include "ui_frmgaugepercent.h"

frmGaugePercent::frmGaugePercent(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugePercent)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugePercent::~frmGaugePercent()
{
    delete ui;
}

void frmGaugePercent::initForm()
{
    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/image/bg1.jpg);}");

    QColor color = QColor(0, 255, 255);
    ui->gaugePercent->setBaseColor(color);
    ui->gaugePercent->setTitle("销售完成额");

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugePercent, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
