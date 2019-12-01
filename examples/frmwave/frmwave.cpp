#include "frmwave.h"
#include "ui_frmwave.h"

#include "frmwavebar.h"
#include "frmwavedouble.h"
#include "frmwaveline.h"
#include "frmwaveplot.h"
#include "frmwavechart.h"
#include "frmwavedata.h"

frmWave::frmWave(QWidget *parent) : QWidget(parent), ui(new Ui::frmWave)
{
    ui->setupUi(this);
    this->initForm();
}

frmWave::~frmWave()
{
    delete ui;
}

void frmWave::initForm()
{    
    ui->stackedWidget->addWidget(new frmWaveBar);
    ui->stackedWidget->addWidget(new frmWaveDouble);
    ui->stackedWidget->addWidget(new frmWaveLine);
    ui->stackedWidget->addWidget(new frmWavePlot);
    ui->stackedWidget->addWidget(new frmWaveChart);
    ui->stackedWidget->addWidget(new frmWaveData);
}

void frmWave::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
