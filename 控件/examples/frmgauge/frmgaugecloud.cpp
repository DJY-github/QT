#pragma execution_character_set("utf-8")

#include "frmgaugecloud.h"
#include "ui_frmgaugecloud.h"
#include "gaugecloud.h"
#include "qdebug.h"

frmGaugeCloud::frmGaugeCloud(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeCloud)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeCloud::~frmGaugeCloud()
{
    delete ui;
}

void frmGaugeCloud::initForm()
{
    connect(ui->gaugeCloud1, SIGNAL(mousePressed(int)), this, SLOT(mousePressed(int)));
    connect(ui->gaugeCloud1, SIGNAL(mouseReleased(int)), this, SLOT(mouseReleased(int)));
    connect(ui->gaugeCloud2, SIGNAL(mousePressed(int)), this, SLOT(mousePressed(int)));
    connect(ui->gaugeCloud3, SIGNAL(mousePressed(int)), this, SLOT(mousePressed(int)));
    connect(ui->gaugeCloud4, SIGNAL(mousePressed(int)), this, SLOT(mousePressed(int)));

    ui->gaugeCloud2->setCloudStyle(GaugeCloud::CloudStyle_White);
    ui->gaugeCloud3->setCloudStyle(GaugeCloud::CloudStyle_Blue);
    ui->gaugeCloud4->setCloudStyle(GaugeCloud::CloudStyle_Purple);
}

void frmGaugeCloud::mousePressed(int position)
{
    GaugeCloud *gaugeClound = (GaugeCloud *)sender();
    if (gaugeClound == ui->gaugeCloud1) {
        ui->labPosition1->setText(QString("当前按下了: %1").arg(position));
    } else if (gaugeClound == ui->gaugeCloud2) {
        ui->labPosition2->setText(QString("当前按下了: %1").arg(position));
    } else if (gaugeClound == ui->gaugeCloud3) {
        ui->labPosition3->setText(QString("当前按下了: %1").arg(position));
    } else if (gaugeClound == ui->gaugeCloud4) {
        ui->labPosition4->setText(QString("当前按下了: %1").arg(position));
    }

    qDebug() << "mousePressed" << position;
}

void frmGaugeCloud::mouseReleased(int position)
{
    qDebug() << "mouseReleased" << position;
}
