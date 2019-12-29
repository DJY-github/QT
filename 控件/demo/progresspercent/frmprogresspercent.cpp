#pragma execution_character_set("utf-8")

#include "frmprogresspercent.h"
#include "ui_frmprogresspercent.h"
#include "progresspercent.h"

frmProgressPercent::frmProgressPercent(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressPercent)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressPercent::~frmProgressPercent()
{
    delete ui;
}

void frmProgressPercent::initForm()
{
    bars << ui->progressPercent1 << ui->progressPercent2 << ui->progressPercent3
         << ui->progressPercent4 << ui->progressPercent5 << ui->progressPercent6;

    ui->progressPercent2->setUsedColor(QColor(255, 107, 107));
    ui->progressPercent3->setUsedColor(QColor(24, 189, 155));
    ui->progressPercent5->setUsedColor(QColor(255, 107, 107));
    ui->progressPercent6->setUsedColor(QColor(24, 189, 155));

    ui->progressPercent4->setShowPercent(false);
    ui->progressPercent5->setShowPercent(false);
    ui->progressPercent6->setShowPercent(false);

    connect(ui->rbtnArc, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));
    connect(ui->rbtnPolo, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));
    connect(ui->rbtnWave, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));
    connect(ui->rbtnArcPolo, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));
    connect(ui->rbtnArcWave, SIGNAL(clicked(bool)), this, SLOT(rbtnClick()));

    QColor circleColor(70, 70, 70, 100);
    foreach (ProgressPercent *bar, bars) {
        bar->setCircleColor(circleColor);
        connect(ui->horizontalSlider1, SIGNAL(valueChanged(int)), bar, SLOT(setValue(int)));
        connect(ui->horizontalSlider2, SIGNAL(valueChanged(int)), bar, SLOT(setNullPosition(int)));
    }

    ui->rbtnArcWave->click();
    ui->horizontalSlider1->setValue(88);
}

void frmProgressPercent::rbtnClick()
{
    QRadioButton *rbtn = (QRadioButton *)sender();
    QString text = rbtn->text();

    if (text == "圆弧") {
        foreach (ProgressPercent *bar, bars) {
            bar->setPercentStyle(ProgressPercent::PercentStyle_Arc);
        }
    } else if (text == "水池") {
        foreach (ProgressPercent *bar, bars) {
            bar->setPercentStyle(ProgressPercent::PercentStyle_Polo);
        }
    } else if (text == "波纹") {
        foreach (ProgressPercent *bar, bars) {
            bar->setPercentStyle(ProgressPercent::PercentStyle_Wave);
        }
    } else if (text == "圆弧水池") {
        foreach (ProgressPercent *bar, bars) {
            bar->setPercentStyle(ProgressPercent::PercentStyle_Arc_Polo);
        }
    } else if (text == "圆弧波纹") {
        foreach (ProgressPercent *bar, bars) {
            bar->setPercentStyle(ProgressPercent::PercentStyle_Arc_Wave);
        }
    }
}

void frmProgressPercent::on_ckClockWise_stateChanged(int arg1)
{
    bool ok = (arg1 != 0);
    foreach (ProgressPercent *bar, bars) {
        bar->setClockWise(ok);
    }
}

void frmProgressPercent::on_ckBorderOut_stateChanged(int arg1)
{
    bool ok = (arg1 != 0);
    foreach (ProgressPercent *bar, bars) {
        bar->setBorderOut(ok);
    }
}
