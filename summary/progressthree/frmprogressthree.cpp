#pragma execution_character_set("utf-8")

#include "frmprogressthree.h"
#include "ui_frmprogressthree.h"

frmProgressThree::frmProgressThree(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressThree)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressThree::~frmProgressThree()
{
    delete ui;
}

void frmProgressThree::initForm()
{
    ui->progressThree2->setRadius(10);
    ui->progressThree3->setAutoRadius(true);

    ui->progressThree4->setColor1(QColor(0, 150, 121));
    ui->progressThree4->setColor2(QColor(71, 164, 233));
    ui->progressThree4->setColor3(QColor(162, 121, 197));
}

void frmProgressThree::on_horizontalSlider1_valueChanged(int value)
{
    ui->progressThree1->setValue1(value);
    ui->progressThree2->setValue1(value);
    ui->progressThree3->setValue1(value);
    ui->progressThree4->setValue1(value);
    ui->labValue1->setText(QString("进度1: %1").arg(value));
}

void frmProgressThree::on_horizontalSlider2_valueChanged(int value)
{
    ui->progressThree1->setValue2(value);
    ui->progressThree2->setValue2(value);
    ui->progressThree3->setValue2(value);
    ui->progressThree4->setValue2(value);
    ui->labValue2->setText(QString("进度2: %1").arg(value));
}

void frmProgressThree::on_horizontalSlider3_valueChanged(int value)
{
    ui->progressThree1->setValue3(value);
    ui->progressThree2->setValue3(value);
    ui->progressThree3->setValue3(value);
    ui->progressThree4->setValue3(value);
    ui->labValue3->setText(QString("进度3: %1").arg(value));
}

void frmProgressThree::on_ckShowValue_stateChanged(int arg1)
{
    bool ok = (arg1 != 0);
    ui->progressThree1->setShowValue(ok);
    ui->progressThree2->setShowValue(ok);
    ui->progressThree3->setShowValue(ok);
    ui->progressThree4->setShowValue(ok);
}

void frmProgressThree::on_ckShowPercent_stateChanged(int arg1)
{
    bool ok = (arg1 != 0);
    ui->progressThree1->setShowPercent(ok);
    ui->progressThree2->setShowPercent(ok);
    ui->progressThree3->setShowPercent(ok);
    ui->progressThree4->setShowPercent(ok);
}

void frmProgressThree::on_ckAutoFont_stateChanged(int arg1)
{
    bool ok = (arg1 != 0);
    ui->progressThree1->setAutoFont(ok);
    ui->progressThree2->setAutoFont(ok);
    ui->progressThree3->setAutoFont(ok);
    ui->progressThree4->setAutoFont(ok);
}
