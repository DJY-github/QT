#pragma execution_character_set("utf-8")

#include "frmxprogressbar.h"
#include "ui_frmxprogressbar.h"

frmXProgressBar::frmXProgressBar(QWidget *parent) : QWidget(parent), ui(new Ui::frmXProgressBar)
{
    ui->setupUi(this);
    this->initForm();
}

frmXProgressBar::~frmXProgressBar()
{
    delete ui;
}

void frmXProgressBar::initForm()
{    
    ui->progressPlay3->setAutoRadius(true);
    ui->progressPlay4->setAutoRadius(true);
    ui->progressPlay5->setAutoRadius(true);
    ui->progressPlay6->setAutoRadius(true);
    ui->progressPlay5->setShowProgressRadius(true);
    ui->progressPlay6->setShowProgressRadius(true);

    ui->progressPlay2->setValueColor(QColor(214, 77, 84));
    ui->progressPlay3->setValueColor(QColor(0, 150, 121));
    ui->progressPlay5->setValueColor(QColor(162, 121, 197));
    ui->progressPlay6->setValueColor(QColor(67, 206, 244));

    //设置画刷产生线性渐变
    QLinearGradient lineGradient(0, 0, ui->progressPlay4->width(), ui->progressPlay4->height());
    lineGradient.setColorAt(0.0, QColor("#F1B45B"));
    lineGradient.setColorAt(0.5, QColor("#F2765C"));
    lineGradient.setColorAt(1.0, QColor("#6D59EF"));
    ui->progressPlay4->setValueBrush(lineGradient);

    ui->horizontalSlider->setValue(65);
}

void frmXProgressBar::on_horizontalSlider_valueChanged(int value)
{
    ui->progressPlay1->setValue(value);
    ui->progressPlay2->setValue(value);
    ui->progressPlay3->setValue(value);
    ui->progressPlay4->setValue(value);
    ui->progressPlay5->setValue(value);
    ui->progressPlay6->setValue(value);
    ui->labValue->setText(QString("当前进度: %1").arg(value));
}
