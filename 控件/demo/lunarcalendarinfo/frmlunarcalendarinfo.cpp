#pragma execution_character_set("utf-8")

#include "frmlunarcalendarinfo.h"
#include "ui_frmlunarcalendarinfo.h"
#include "lunarcalendarinfo.h"

frmLunarCalendarInfo::frmLunarCalendarInfo(QWidget *parent) : QWidget(parent), ui(new Ui::frmLunarCalendarInfo)
{
    ui->setupUi(this);
    on_calendarWidget_clicked(QDate::currentDate());
}

frmLunarCalendarInfo::~frmLunarCalendarInfo()
{
    delete ui;
}

void frmLunarCalendarInfo::on_calendarWidget_clicked(const QDate &date)
{
    QString strHoliday, strSolarTerms, strLunarFestival, strLunarYear, strLunarMonth, strLunarDay;

    LunarCalendarInfo::Instance()->getLunarCalendarInfo(date.year(), date.month(), date.day(),
            strHoliday, strSolarTerms, strLunarFestival,
            strLunarYear, strLunarMonth, strLunarDay);

    QString str = QString("节日名称: %1\n节气名称: %2\n农历节气: %3\n农历年份: %4\n农历月份: %5\n农历日期: %6")
                  .arg(strHoliday).arg(strSolarTerms).arg(strLunarFestival).arg(strLunarYear).arg(strLunarMonth).arg(strLunarDay);
    ui->textEdit->setText(str);
}
