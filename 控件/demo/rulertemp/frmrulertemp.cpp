#pragma execution_character_set("utf-8")

#include "frmrulertemp.h"
#include "ui_frmrulertemp.h"
#include "rulertemp.h"
#include "qdatetime.h"
#include "qtimer.h"

frmRulerTemp::frmRulerTemp(QWidget *parent) : QWidget(parent), ui(new Ui::frmRulerTemp)
{
    ui->setupUi(this);
    this->initForm();
}

frmRulerTemp::~frmRulerTemp()
{
    delete ui;
}

void frmRulerTemp::initForm()
{
    ui->rulerTemp1->setTickPosition(RulerTemp::TickPosition_Left);
    ui->rulerTemp1->setBarPosition(RulerTemp::BarPosition_Right);
    ui->rulerTemp2->setTickPosition(RulerTemp::TickPosition_Left);
    ui->rulerTemp4->setTickPosition(RulerTemp::TickPosition_Right);
    ui->rulerTemp5->setTickPosition(RulerTemp::TickPosition_Right);
    ui->rulerTemp5->setBarPosition(RulerTemp::BarPosition_Left);

    ui->rulerTemp3->setAnimation(true);

    ui->rulerTemp2->setBarColor(QColor(24, 189, 155));
    ui->rulerTemp3->setBarColor(QColor(255, 107, 107));
    ui->rulerTemp4->setBarColor(QColor("#DEAF39"));
    ui->rulerTemp5->setBarColor(QColor("#A279C5"));

    ui->rulerTemp3->setAnimation(true);

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmRulerTemp::updateValue()
{
    ui->rulerTemp1->setValue(qrand() % 100);
    ui->rulerTemp2->setValue(qrand() % 100);
    ui->rulerTemp3->setValue(qrand() % 100);
    ui->rulerTemp4->setValue(qrand() % 100);
    ui->rulerTemp5->setValue(qrand() % 100);
}
