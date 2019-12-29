#pragma execution_character_set("utf-8")

#include "frmbottomwidget.h"
#include "ui_frmbottomwidget.h"

frmBottomWidget::frmBottomWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmBottomWidget)
{
	ui->setupUi(this);
	ui->widget->start();
	this->showMaximized();
}

frmBottomWidget::~frmBottomWidget()
{
	delete ui;
}
