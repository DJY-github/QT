#pragma execution_character_set("utf-8")

#include "frmrulerprogress.h"
#include "ui_frmrulerprogress.h"
#include "rulerprogress.h"

frmRulerProgress::frmRulerProgress(QWidget *parent) : QWidget(parent), ui(new Ui::frmRulerProgress)
{
    ui->setupUi(this);
    this->initForm();
}

frmRulerProgress::~frmRulerProgress()
{
    delete ui;
}

void frmRulerProgress::initForm()
{
    ui->rulerProgress2->setRulerTop(false);
    ui->rulerProgress4->setRulerTop(false);

    ui->rulerProgress3->setBgColor(Qt::transparent);
    ui->rulerProgress4->setBgColor(Qt::transparent);

    ui->rulerProgress3->setLineColor(Qt::black);
    ui->rulerProgress4->setLineColor(Qt::black);

    ui->rulerProgress2->setProgressColor(QColor(255, 107, 107, 200));
    ui->rulerProgress3->setProgressColor(QColor(34, 163, 169, 200));
    ui->rulerProgress4->setProgressColor(QColor(162, 121, 197, 200));
    ui->rulerProgress5->setProgressColor(QColor(34, 163, 169, 200));

    connect(ui->rulerProgress1, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));
    connect(ui->rulerProgress2, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));
    connect(ui->rulerProgress3, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));
    connect(ui->rulerProgress4, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));
    connect(ui->rulerProgress5, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->rulerProgress1, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->rulerProgress2, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->rulerProgress3, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->rulerProgress4, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->rulerProgress5, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}

void frmRulerProgress::valueChanged(double value)
{
    RulerProgress *ruler = (RulerProgress *)sender();
    if (ruler == ui->rulerProgress1) {
        ui->labValue1->setText(QString::number(value, 'f', 0));
    } else if (ruler == ui->rulerProgress2) {
        ui->labValue2->setText(QString::number(value, 'f', 0));
    } else if (ruler == ui->rulerProgress3) {
        ui->labValue3->setText(QString::number(value, 'f', 0));
    } else if (ruler == ui->rulerProgress4) {
        ui->labValue4->setText(QString::number(value, 'f', 0));
    } else if (ruler == ui->rulerProgress5) {
        ui->labValue5->setText(QString::number(value, 'f', 0));
    }
}
