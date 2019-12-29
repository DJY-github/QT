#pragma execution_character_set("utf-8")

#include "frmcustompie.h"
#include "ui_frmcustompie.h"

frmCustomPie::frmCustomPie(QWidget *parent) : QWidget(parent), ui(new Ui::frmCustomPie)
{
    ui->setupUi(this);
    this->initForm();
}

frmCustomPie::~frmCustomPie()
{
    delete ui;
}

void frmCustomPie::initForm()
{
    ui->customPie1->appendPie("非常好", 5);
    ui->customPie1->appendPie("正常", 6);
    ui->customPie1->appendPie("不合格", 4);
    ui->customPie1->appendPie("很糟糕", 3);
    ui->customPie1->loadPercent();

    ui->customPie2->appendPie("", 5);
    ui->customPie2->appendPie("", 6);
    ui->customPie2->appendPie("", 4);
    ui->customPie2->loadPercent();

    QList<QColor> colors;
    colors << QColor(0, 176, 180) << QColor(0, 113, 193) << QColor(72, 103, 149) << QColor(214, 77, 84);
    ui->customPie3->setColors(colors);
    ui->customPie3->appendPie("非常好", 5);
    ui->customPie3->appendPie("正常", 6);
    ui->customPie3->appendPie("不合格", 4);
    ui->customPie3->appendPie("很糟糕", 3);
    ui->customPie3->loadPercent();

    ui->customPie4->appendPie("非常好", 5);
    ui->customPie4->appendPie("正常", 6);
    ui->customPie4->appendPie("不合格", 4);
}
