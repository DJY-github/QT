#include "frmbarvumeter.h"
#include "ui_frmbarvumeter.h"
#include "qdatetime.h"
#include "qtimer.h"

frmBarVUMeter::frmBarVUMeter(QWidget *parent) : QWidget(parent), ui(new Ui::frmBarVUMeter)
{
    ui->setupUi(this);
    this->initForm();
}

frmBarVUMeter::~frmBarVUMeter()
{
    delete ui;
}

void frmBarVUMeter::initForm()
{
    ui->barVUMeter2->setColorLow(QColor(24, 189, 155));
    ui->barVUMeter3->setColorLow(QColor(255, 107, 107));
    ui->barVUMeter4->setColorLow(QColor(21, 156, 119));
    ui->barVUMeter5->setColorLow(QColor(1, 206, 209));

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmBarVUMeter::updateValue()
{
    ui->barVUMeter1->setLeftValue(qrand() % 100);
    ui->barVUMeter1->setRightValue(qrand() % 100);

    ui->barVUMeter2->setLeftValue(qrand() % 100);
    ui->barVUMeter2->setRightValue(qrand() % 100);

    ui->barVUMeter3->setLeftValue(qrand() % 100);
    ui->barVUMeter3->setRightValue(qrand() % 100);

    ui->barVUMeter4->setLeftValue(qrand() % 100);
    ui->barVUMeter4->setRightValue(qrand() % 100);

    ui->barVUMeter5->setLeftValue(qrand() % 100);
    ui->barVUMeter5->setRightValue(qrand() % 100);

    ui->barVUMeter6->setLeftValue(qrand() % 100);
    ui->barVUMeter6->setRightValue(qrand() % 100);
}
