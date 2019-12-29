#pragma execution_character_set("utf-8")

#include "frmroundwidget.h"
#include "ui_frmroundwidget.h"

frmRoundWidget::frmRoundWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmRoundWidget)
{
	ui->setupUi(this);
}

frmRoundWidget::~frmRoundWidget()
{
	delete ui;
}
