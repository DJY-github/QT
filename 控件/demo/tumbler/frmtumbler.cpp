#pragma execution_character_set("utf-8")

#include "frmtumbler.h"
#include "ui_frmtumbler.h"

frmTumbler::frmTumbler(QWidget *parent) : QWidget(parent), ui(new Ui::frmTumbler)
{
	ui->setupUi(this);
	this->initForm();
}

frmTumbler::~frmTumbler()
{
    delete ui;
}

void frmTumbler::initForm()
{
    ui->tumbler1->setTextColor(QColor(100, 184, 255));
    ui->tumbler2->setTextColor(QColor(255, 107, 107));
    ui->tumbler3->setTextColor(QColor(24, 189, 155));
    ui->tumbler4->setTextColor(QColor(100, 184, 255));
    ui->tumbler5->setTextColor(QColor(255, 107, 107));
    ui->tumbler6->setTextColor(QColor(24, 189, 155));

	QStringList listValue;

	for (int i = 0; i <= 100; i++) {
		listValue.append(QString::number(i));
	}

    ui->tumbler2->setListValue(listValue);
    ui->tumbler3->setListValue(listValue);

    ui->tumbler1->setCurrentIndex(5);
    ui->tumbler2->setCurrentIndex(30);
    ui->tumbler3->setCurrentValue("50");

    ui->tumbler4->setHorizontal(false);
    ui->tumbler5->setHorizontal(false);
    ui->tumbler6->setHorizontal(false);

    ui->tumbler5->setListValue(listValue);
    ui->tumbler5->setCurrentIndex(10);

	listValue.clear();

	for (int i = 2010; i <= 2030; i++) {
		listValue.append(QString::number(i));
	}

    ui->tumbler6->setListValue(listValue);
    ui->tumbler6->setCurrentValue("2016");

	listValue.clear();
	listValue << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

    ui->tumbler4->setListValue(listValue);
    ui->tumbler4->setCurrentValue("Nov");
}
