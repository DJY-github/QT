#pragma execution_character_set("utf-8")

#include "frmwavedouble.h"
#include "ui_frmwavedouble.h"
#include "qdatetime.h"
#include "qtimer.h"

frmWaveDouble::frmWaveDouble(QWidget *parent) : QWidget(parent), ui(new Ui::frmWaveDouble)
{
	ui->setupUi(this);
	this->initForm();
}

frmWaveDouble::~frmWaveDouble()
{
	delete ui;
}

void frmWaveDouble::initForm()
{
    ui->waveDouble1->setSpace(2);
    ui->waveDouble2->setSpace(2);
    ui->waveDouble3->setSpace(2);
    ui->waveDouble4->setSpace(2);
    ui->waveDouble5->setSpace(2);
    ui->waveDouble6->setSpace(2);
    ui->waveDouble7->setSpace(2);
    ui->waveDouble8->setSpace(2);
    ui->waveDouble9->setSpace(2);
    ui->waveDouble10->setSpace(2);

    ui->waveDouble2->setBarColor(QColor(255, 107, 107));
    ui->waveDouble3->setBarColor(QColor(24, 189, 155));
    ui->waveDouble4->setBarColor(QColor(154, 254, 155));
    ui->waveDouble5->setBarColor(QColor(0, 139, 138));

    ui->waveDouble7->setBarColor(QColor(255, 107, 107));
    ui->waveDouble8->setBarColor(QColor(24, 189, 155));
    ui->waveDouble9->setBarColor(QColor(154, 254, 155));
    ui->waveDouble10->setBarColor(QColor(0, 139, 138));

	//初始化随机数种子
	QTime t = QTime::currentTime();
	qsrand(t.msec() + t.second() * 1000);

	QTimer *timer = new QTimer(this);
	timer->setInterval(2000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
	timer->start();
	updateValue();
}

void frmWaveDouble::updateValue()
{
    ui->waveDouble1->setValue(qrand() % 100);
    ui->waveDouble2->setValue(qrand() % 100);
    ui->waveDouble3->setValue(qrand() % 100);
    ui->waveDouble4->setValue(qrand() % 100);
    ui->waveDouble5->setValue(qrand() % 100);

    ui->waveDouble6->setValue(qrand() % 100);
    ui->waveDouble7->setValue(qrand() % 100);
    ui->waveDouble8->setValue(qrand() % 100);
    ui->waveDouble9->setValue(qrand() % 100);
    ui->waveDouble10->setValue(qrand() % 100);
}
