#pragma execution_character_set("utf-8")

#include "frmwavechart.h"
#include "ui_frmwavechart.h"
#include "qdatetime.h"
#include "qtimer.h"

frmWaveChart::frmWaveChart(QWidget *parent) : QWidget(parent), ui(new Ui::frmWaveChart)
{
    ui->setupUi(this);
    this->initForm();
}

frmWaveChart::~frmWaveChart()
{
    delete ui;
}

void frmWaveChart::initForm()
{
    ui->waveChart1->setMaxValue(150);
    ui->waveChart1->setXStep(30);
    ui->waveChart1->setTitle("简单曲线图示例 1");

    ui->waveChart2->setPointColor(QColor(255, 107, 107));
    ui->waveChart2->setTitle("简单曲线图示例 2");

    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    timer = new QTimer(this);
    timer->setInterval(200);
    connect(timer, SIGNAL(timeout()), this, SLOT(addData()));
}

void frmWaveChart::addData()
{
    int value1 = qrand() % 130;
    value1 = (value1 < 20 ? 20 : value1);
    ui->waveChart1->addData(value1);

    int value2 = qrand() % 80;
    value2 = (value2 < 20 ? 20 : value2);
    ui->waveChart2->addData(value2);
}

void frmWaveChart::on_ckSmooth_stateChanged(int arg1)
{
    bool show = (arg1 != 0);
    ui->waveChart1->setSmooth(show);
    ui->waveChart2->setSmooth(show);
}

void frmWaveChart::on_ckShowHLine_stateChanged(int arg1)
{
    bool show = (arg1 != 0);
    ui->waveChart1->setShowHLine(show);
    ui->waveChart2->setShowHLine(show);
}

void frmWaveChart::on_ckShowPoint_stateChanged(int arg1)
{
    bool show = (arg1 != 0);
    ui->waveChart1->setShowPoint(show);
    ui->waveChart2->setShowPoint(show);
}

void frmWaveChart::on_ckShowPointBg_stateChanged(int arg1)
{
    bool show = (arg1 != 0);
    ui->waveChart1->setShowPointBg(show);
    ui->waveChart2->setShowPointBg(show);
}

void frmWaveChart::on_btnSetData_clicked()
{
    if (ui->btnAddData->text() == "停止模拟") {
        on_btnAddData_clicked();
    }

    on_btnClearData_clicked();

    QVector<double> data;
    for (int i = 0; i < 100; i++) {
        int value = qrand() % 80;
        value = (value < 20 ? 20 : value);
        data.push_front(value);
    }

    ui->waveChart1->setData(data);
    ui->waveChart2->setData(data);
}

void frmWaveChart::on_btnAddData_clicked()
{
    if (ui->btnAddData->text() == "模拟数据") {
        timer->start();
        ui->btnAddData->setText("停止模拟");
    } else {
        timer->stop();
        ui->btnAddData->setText("模拟数据");
    }
}

void frmWaveChart::on_btnClearData_clicked()
{
    ui->waveChart1->clearData();
    ui->waveChart2->clearData();
}
