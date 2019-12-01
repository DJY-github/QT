#pragma execution_character_set("utf-8")

#include "frmprogressplay.h"
#include "ui_frmprogressplay.h"

frmProgressPlay::frmProgressPlay(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressPlay)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressPlay::~frmProgressPlay()
{
    delete ui;
}

void frmProgressPlay::initForm()
{
    ui->progressPlay2->setRadius(10);
    ui->progressPlay3->setAutoRadius(true);
    //ui->progressPlay2->setShowProgressRadius(true);
    ui->progressPlay3->setShowProgressRadius(true);

    ui->progressPlay4->setColorPlay(QColor(0, 150, 121));
    ui->progressPlay4->setColorLoad(QColor(162, 121, 197));
}

void frmProgressPlay::on_horizontalSlider1_valueChanged(int value)
{
    ui->progressPlay1->setValueAll(value);
    ui->progressPlay2->setValueAll(value);
    ui->progressPlay3->setValueAll(value);
    ui->progressPlay4->setValueAll(value);
    ui->labValueAll->setText(QString("总大小: %1").arg(value));
}

void frmProgressPlay::on_horizontalSlider2_valueChanged(int value)
{
    ui->progressPlay1->setValuePlay(value);
    ui->progressPlay2->setValuePlay(value);
    ui->progressPlay3->setValuePlay(value);
    ui->progressPlay4->setValuePlay(value);
    ui->labValuePlay->setText(QString("已播放: %1").arg(value));
}

void frmProgressPlay::on_horizontalSlider3_valueChanged(int value)
{
    ui->progressPlay1->setValueLoad(value);
    ui->progressPlay2->setValueLoad(value);
    ui->progressPlay3->setValueLoad(value);
    ui->progressPlay4->setValueLoad(value);
    ui->labValueLoad->setText(QString("已缓存: %1").arg(value));
}
