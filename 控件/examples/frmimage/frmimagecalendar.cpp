#pragma execution_character_set("utf-8")

#include "frmimagecalendar.h"
#include "ui_frmimagecalendar.h"

frmImageCalendar::frmImageCalendar(QWidget *parent) : QWidget(parent), ui(new Ui::frmImageCalendar)
{
    ui->setupUi(this);
    this->initForm();
}

frmImageCalendar::~frmImageCalendar()
{
    delete ui;
}

void frmImageCalendar::initForm()
{
    ui->imageCalendar1->setCalendarStyle(ImageCalendar::CalendarStyle_Yellow);
    ui->imageCalendar2->setCalendarStyle(ImageCalendar::CalendarStyle_Blue);
    ui->imageCalendar3->setCalendarStyle(ImageCalendar::CalendarStyle_Brown);
    ui->imageCalendar4->setCalendarStyle(ImageCalendar::CalendarStyle_Gray);
    ui->imageCalendar5->setCalendarStyle(ImageCalendar::CalendarStyle_Purple);
    ui->imageCalendar6->setCalendarStyle(ImageCalendar::CalendarStyle_Red);
}
