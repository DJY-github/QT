#pragma execution_character_set("utf-8")

#include "tumblerdatetime.h"
#include "qboxlayout.h"
#include "tumbler.h"
#include "qdebug.h"

TumblerDateTime::TumblerDateTime(QWidget *parent) : QWidget(parent)
{
    this->initForm();
}

void TumblerDateTime::initForm()
{
    //年份选择器
    tumblerYear = new Tumbler(this);
    QStringList listYear;
    for (int i = 2015; i <= 2030; i++) {
        listYear << QString("%1").arg(i);
    }
    tumblerYear->setListValue(listYear);

    //月份选择器
    tumblerMonth = new Tumbler(this);
    QStringList listMonth;
    for (int i = 1; i <= 12; i++) {
        listMonth << QString("%1 月").arg(i);
    }
    tumblerMonth->setListValue(listMonth);

    //日期选择器
    tumblerDay = new Tumbler(this);
    QStringList listDay;
    for (int i = 1; i <= 31; i++) {
        listDay << QString("%1").arg(i);
    }
    tumblerDay->setListValue(listDay);

    //年月日联动
    connect(tumblerYear, SIGNAL(currentValueChanged(QString)), this, SLOT(currentValueChanged(QString)));
    connect(tumblerMonth, SIGNAL(currentValueChanged(QString)), this, SLOT(currentValueChanged(QString)));

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
    layout->addWidget(tumblerYear);
    layout->addWidget(tumblerMonth);
    layout->addWidget(tumblerDay);
    layout->addWidget(tumblerHour);
    layout->addWidget(tumblerMin);
    layout->addWidget(tumblerSec);
}

void TumblerDateTime::currentValueChanged(const QString &)
{
    int month = tumblerMonth->getCurrentValue().left(2).toInt();

    //记住之前的日期
    int day = tumblerDay->getCurrentValue().left(2).toInt();

    //计算该月最大日期
    int maxDay = 30;
    if (month == 2) {
        //平年28天 闰年29天
        int year = tumblerYear->getCurrentValue().left(4).toInt();
        bool isLoopYear = (((0 == (year % 4)) && (0 != (year % 100))) || (0 == (year % 400)));
        if (isLoopYear) {
            maxDay = 29;
        } else {
            maxDay = 28;
        }
    } else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        maxDay = 31;
    }

    QStringList listDay;
    for (int i = 1; i <= maxDay; i++) {
        listDay << QString("%1").arg(i);
    }

    tumblerDay->setListValue(listDay);

    //如果上次的日期大于最大的日期则设置为最大的日期
    if (day > maxDay) {
        tumblerDay->setCurrentIndex(maxDay - 1);
    } else {
        tumblerDay->setCurrentIndex(day - 1);
    }
}

int TumblerDateTime::getYear() const
{
    return tumblerYear->getCurrentValue().toInt();
}

int TumblerDateTime::getMonth() const
{
    return tumblerMonth->getCurrentValue().left(2).toInt();
}

int TumblerDateTime::getDay() const
{
    return tumblerDay->getCurrentValue().toInt();
}

int TumblerDateTime::getHour() const
{
    return tumblerHour->getCurrentValue().toInt();
}

int TumblerDateTime::getMin() const
{
    return tumblerMin->getCurrentValue().toInt();
}

int TumblerDateTime::getSec() const
{
    return tumblerSec->getCurrentValue().toInt();
}

void TumblerDateTime::setYear(int year)
{
    tumblerYear->setCurrentValue(QString("%1").arg(year));
}

void TumblerDateTime::setMonth(int month)
{
    tumblerMonth->setCurrentValue(QString("%1 月").arg(month));
}

void TumblerDateTime::setDay(int day)
{
    tumblerDay->setCurrentValue(QString("%1").arg(day));
}

void TumblerDateTime::setHour(int hour)
{
    tumblerHour->setCurrentValue(QString("%1").arg(hour));
}

void TumblerDateTime::setMin(int min)
{
    tumblerMin->setCurrentValue(QString("%1").arg(min));
}

void TumblerDateTime::setSec(int sec)
{
    tumblerSec->setCurrentValue(QString("%1").arg(sec));
}

void TumblerDateTime::setDateTime(int year, int month, int day, int hour, int min, int sec)
{
    setYear(year);
    setMonth(month);
    setDay(day);
    setHour(hour);
    setMin(min);
    setSec(sec);
}
