#include "frmgauge.h"
#include "ui_frmgauge.h"

#include "frmgaugecar.h"
#include "frmgaugearc.h"
#include "frmgaugepercent.h"
#include "frmgaugecircle.h"
#include "frmgaugeclock.h"
#include "frmgaugecompass.h"
#include "frmgaugecompasspan.h"
#include "frmgaugedial.h"
#include "frmgaugemini.h"
#include "frmgaugenet.h"
#include "frmgaugeplane.h"
#include "frmgaugeprogress.h"
#include "frmgaugerange.h"
#include "frmgaugeround.h"
#include "frmgaugesimple.h"
#include "frmgaugespeed.h"
#include "frmgaugewatch.h"
#include "frmgaugelpm.h"
#include "frmgaugecolor.h"
#include "frmgaugecloud.h"
#include "frmgaugeweather.h"
#include "frmgaugedecibel.h"
#include "frmgaugepanel.h"

frmGauge::frmGauge(QWidget *parent) : QWidget(parent), ui(new Ui::frmGauge)
{
    ui->setupUi(this);
    this->initForm();
}

frmGauge::~frmGauge()
{
    delete ui;
}

void frmGauge::initForm()
{
    ui->stackedWidget->addWidget(new frmGaugeCar);
    ui->stackedWidget->addWidget(new frmGaugeArc);
    ui->stackedWidget->addWidget(new frmGaugePercent);
    ui->stackedWidget->addWidget(new frmGaugeCircle);
    ui->stackedWidget->addWidget(new frmGaugeProgress);
    ui->stackedWidget->addWidget(new frmGaugeRange);
    ui->stackedWidget->addWidget(new frmGaugeSpeed);
    ui->stackedWidget->addWidget(new frmGaugeClock);
    ui->stackedWidget->addWidget(new frmGaugeNet);
    ui->stackedWidget->addWidget(new frmGaugeSimple);
    ui->stackedWidget->addWidget(new frmGaugeWatch);
    ui->stackedWidget->addWidget(new frmGaugeCompass);
    ui->stackedWidget->addWidget(new frmGaugeCompassPan);
    ui->stackedWidget->addWidget(new frmGaugeDial);
    ui->stackedWidget->addWidget(new frmGaugeMini);
    ui->stackedWidget->addWidget(new frmGaugeRound);
    ui->stackedWidget->addWidget(new frmGaugePlane);
    ui->stackedWidget->addWidget(new frmGaugeLpm);
    ui->stackedWidget->addWidget(new frmGaugeColor);
    ui->stackedWidget->addWidget(new frmGaugeCloud);
    ui->stackedWidget->addWidget(new frmGaugeWeather);
    ui->stackedWidget->addWidget(new frmGaugeDecibel);
    ui->stackedWidget->addWidget(new frmGaugePanel);
}

void frmGauge::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
