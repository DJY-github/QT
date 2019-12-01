#pragma execution_character_set("utf-8")

#include "frmgaugeprogress.h"
#include "ui_frmgaugeprogress.h"

frmGaugeProgress::frmGaugeProgress(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeProgress)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeProgress::~frmGaugeProgress()
{
    delete ui;
}

void frmGaugeProgress::initForm()
{
    ui->ckShowPointer->setChecked(true);
    gauges << ui->gaugeProgress1 << ui->gaugeProgress2 << ui->gaugeProgress3 << ui->gaugeProgress4 << ui->gaugeProgress5 << ui->gaugeProgress6;

    QList<QColor> colors;
    colors << "#47A4E9" << "#00B17D" << "#D64D54" << "#DEAF39" << "#A279C5" << "#009679";

    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setProgressColor(colors.at(i));
        connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), gauges.at(i), SLOT(setValue(int)));
    }

    ui->horizontalSlider->setValue(88);
}

void frmGaugeProgress::on_ckShowPointer_stateChanged(int arg1)
{
    bool check = (arg1 != 0);
    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setShowPointer(check);
    }
}

void frmGaugeProgress::on_ckShowValue_stateChanged(int arg1)
{
    bool check = (arg1 != 0);
    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setShowValue(check);
    }
}

void frmGaugeProgress::on_cboxPointerStyle_currentIndexChanged(int index)
{
    GaugeProgress::PointerStyle style = (GaugeProgress::PointerStyle)index;
    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setPointerStyle(style);
    }
}
