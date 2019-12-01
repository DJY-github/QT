#pragma execution_character_set("utf-8")

#include "tumblertime.h"
#include "qboxlayout.h"
#include "tumbler.h"
#include "qdebug.h"

TumblerTime::TumblerTime(QWidget *parent) : QWidget(parent)
{
    this->initForm();
}

void TumblerTime::initForm()
{
    //时钟选择器
    tumblerHour = new Tumbler(this);
    QStringList listHour;
    for (int i = 0; i <= 23; i++) {
        listHour << QString("%1").arg(i);
    }
    tumblerHour->setListValue(listHour);

    //分钟选择器
    tumblerMin = new Tumbler(this);
    QStringList listMin;
    for (int i = 0; i <= 59; i++) {
        listMin << QString("%1").arg(i);
    }
    tumblerMin->setListValue(listMin);

    //秒钟选择器
    tumblerSec = new Tumbler(this);
    QStringList listSec;
    for (int i = 0; i <= 59; i++) {
        listSec << QString("%1").arg(i);
    }
    tumblerSec->setListValue(listSec);

    //将选择器添加到布局
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(tumblerHour);
    layout->addWidget(tumblerMin);
    layout->addWidget(tumblerSec);
}

int TumblerTime::getHour() const
{
    return tumblerHour->getCurrentValue().toInt();
}

int TumblerTime::getMin() const
{
    return tumblerMin->getCurrentValue().toInt();
}

int TumblerTime::getSec() const
{
    return tumblerSec->getCurrentValue().toInt();
}

QTime TumblerTime::getTime() const
{
    QString strTime = QString("%1:%2:%3").arg(getHour()).arg(getMin()).arg(getSec());
    return QTime::fromString(strTime, "h:m:s");
}

void TumblerTime::setHour(int hour)
{
    tumblerHour->setCurrentValue(QString("%1").arg(hour));
}

void TumblerTime::setMin(int min)
{
    tumblerMin->setCurrentValue(QString("%1").arg(min));
}

void TumblerTime::setSec(int sec)
{
    tumblerSec->setCurrentValue(QString("%1").arg(sec));
}

void TumblerTime::setTime(int hour, int min, int sec)
{
    setHour(hour);
    setMin(min);
    setSec(sec);
}

