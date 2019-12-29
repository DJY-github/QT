#pragma execution_character_set("utf-8")

#include "frmgaugemini.h"
#include "ui_frmgaugemini.h"

frmGaugeMini::frmGaugeMini(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugeMini)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugeMini::~frmGaugeMini()
{
    delete ui;
}

void frmGaugeMini::initForm()
{
    ui->ckDouble->setChecked(true);
    ui->widget->setStyleSheet("QWidget#widget{background:#515151;}QLabel{color:#FFFFFF;}");

    gauges << ui->gaugeMini1 << ui->gaugeMini2 << ui->gaugeMini3 << ui->gaugeMini4 << ui->gaugeMini5 << ui->gaugeMini6;
    labs << ui->labValue1 << ui->labValue2 << ui->labValue3 << ui->labValue4 << ui->labValue5 << ui->labValue6;

    QList<QColor> colors;
    colors << "#47A4E9" << "#00B17D" << "#D64D54" << "#DEAF39" << "#A279C5" << "#009679";

    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setPercentColor(colors.at(i));
        labs.at(i)->setText("0.0");
        connect(gauges.at(i), SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));
        connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), gauges.at(i), SLOT(setValue(int)));
    }

    ui->horizontalSlider->setValue(88);
}

void frmGaugeMini::valueChanged(double value)
{
    GaugeMini *gauge = (GaugeMini *)sender();
    int index = gauges.indexOf(gauge);
    labs.at(index)->setText(QString::number(value, 'f', 1));
}

void frmGaugeMini::on_ckDouble_stateChanged(int arg1)
{
    bool check = (arg1 != 0);
    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setDoublePercent(check);
    }
}

void frmGaugeMini::on_cboxPointerStyle_currentIndexChanged(int index)
{
    GaugeMini::PointerStyle style = (GaugeMini::PointerStyle)index;
    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setPointerStyle(style);
    }
}
