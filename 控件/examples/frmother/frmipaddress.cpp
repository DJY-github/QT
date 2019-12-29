#pragma execution_character_set("utf-8")

#include "frmipaddress.h"
#include "ui_frmipaddress.h"
#include "qdatetime.h"
#include "qprocess.h"
#include "qdebug.h"

frmIPAddress::frmIPAddress(QWidget *parent) : QWidget(parent), ui(new Ui::frmIPAddress)
{
    ui->setupUi(this);
    this->initForm();
}

frmIPAddress::~frmIPAddress()
{
    delete ui;
}

void frmIPAddress::setSystemDateTime(const QString &year, const QString &month, const QString &day,
                                     const QString &hour, const QString &min, const QString &sec)
{
#ifdef Q_OS_WIN
    QProcess p(0);
    p.start("cmd");
    p.waitForStarted();
    p.write(QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();
    p.start("cmd");
    p.waitForStarted();
    p.write(QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();
#else
    QString cmd = QString("date %1%2%3%4%5.%6").arg(month).arg(day).arg(hour).arg(min).arg(year).arg(sec);
    system(cmd.toLatin1());
    system("hwclock -w");
#endif
}

void frmIPAddress::initForm()
{
    QStringList items;
    items << "测试元素1" << "测试元素2" << "测试元素3";

    //指定高度,自动计算元素宽度
    ui->cbox->setAutoWidth(false);
    ui->cbox->setItemHeight(30);
    ui->cbox->addItems(items);

    QDate date = QDate::currentDate();
    ui->widgetDate->setYear(date.year());
    ui->widgetDate->setMonth(date.month());
    ui->widgetDate->setDay(date.day());

    QTime time = QTime::currentTime();
    ui->widgetTime->setHour(time.hour());
    ui->widgetTime->setMin(time.minute());
    ui->widgetTime->setSec(time.second());

    ui->widgetDateTime->setYear(date.year());
    ui->widgetDateTime->setMonth(date.month());
    ui->widgetDateTime->setDay(date.day());
    ui->widgetDateTime->setHour(time.hour());
    ui->widgetDateTime->setMin(time.minute());
    ui->widgetDateTime->setSec(time.second());
}

void frmIPAddress::on_btnSetIP_clicked()
{
    ui->widgetIP->setIP("192.168.1.56");
}

void frmIPAddress::on_btnGetIP_clicked()
{
    qDebug() << ui->widgetIP->getIP();
}

void frmIPAddress::on_btnClear_clicked()
{
    ui->widgetIP->clear();
}

void frmIPAddress::on_btnSetDate_clicked()
{
    qDebug() << ui->widgetDate->getDate().toString("yyyy-MM-dd");
}

void frmIPAddress::on_btnSetTime_clicked()
{
    qDebug() << ui->widgetTime->getTime().toString("hh:mm:ss");
}

void frmIPAddress::on_btnSetDateTime_clicked()
{
    QString year = QString::number(ui->widgetDateTime->getYear());
    year = QString("%1").arg(year.left(4));

    QString month = QString::number(ui->widgetDateTime->getMonth());
    month = QString("%1").arg(month.left(2).toInt(), 2, 10, QChar('0'));

    QString day = QString::number(ui->widgetDateTime->getDay());
    day = QString("%1").arg(day.left(2).toInt(), 2, 10, QChar('0'));

    QString hour = QString::number(ui->widgetDateTime->getHour());
    hour = QString("%1").arg(hour.left(2).toInt(), 2, 10, QChar('0'));

    QString min = QString::number(ui->widgetDateTime->getMin());
    min = QString("%1").arg(min.left(2).toInt(), 2, 10, QChar('0'));

    QString sec = QString::number(ui->widgetDateTime->getSec());
    sec = QString("%1").arg(sec.left(2).toInt(), 2, 10, QChar('0'));

    qDebug() << year << month << day << hour << min << sec;
    setSystemDateTime(year, month, day, hour, min, sec);
}
