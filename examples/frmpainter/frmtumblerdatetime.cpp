#include "frmtumblerdatetime.h"
#include "ui_frmtumblerdatetime.h"

frmTumblerDateTime::frmTumblerDateTime(QWidget *parent) : QWidget(parent), ui(new Ui::frmTumblerDateTime)
{
    ui->setupUi(this);
    this->initForm();
}

frmTumblerDateTime::~frmTumblerDateTime()
{
    delete ui;
}

void frmTumblerDateTime::initForm()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    ui->tumblerDateTime1->setYear(date.year());
    ui->tumblerDateTime1->setMonth(date.month());
    ui->tumblerDateTime1->setDay(date.day());
    ui->tumblerDateTime1->setHour(time.hour());
    ui->tumblerDateTime1->setMin(time.minute());
    ui->tumblerDateTime1->setSec(time.second());

    ui->tumblerDateTime2->setYear(date.year());
    ui->tumblerDateTime2->setMonth(date.month());
    ui->tumblerDateTime2->setDay(date.day());
    ui->tumblerDateTime2->setHour(time.hour());
    ui->tumblerDateTime2->setMin(time.minute());
    ui->tumblerDateTime2->setSec(time.second());
}
