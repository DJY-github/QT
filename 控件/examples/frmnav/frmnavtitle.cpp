#pragma execution_character_set("utf-8")

#include "frmnavtitle.h"
#include "ui_frmnavtitle.h"
#include "navtitle.h"
#include "iconhelper.h"
#include "qdebug.h"

frmNavTitle::frmNavTitle(QWidget *parent) : QWidget(parent), ui(new Ui::frmNavTitle)
{
    ui->setupUi(this);
    this->initForm();
}

frmNavTitle::~frmNavTitle()
{
    delete ui;
}

void frmNavTitle::initForm()
{
    ui->navTitle1->setText("设备列表");
    ui->navTitle1->setRightIcon1(0xf067);
    ui->navTitle1->setRightIcon2(0xf068);
    ui->navTitle1->setRightIcon3(0xf0c7);
    ui->navTitle1->setRightIcon4(0xf013);
    connect(ui->navTitle1, SIGNAL(mousePressed(int)), this, SLOT(mousePressed(int)));
    connect(ui->navTitle1, SIGNAL(mouseReleased(int)), this, SLOT(mouseReleased(int)));
}

void frmNavTitle::mousePressed(int index)
{
    qDebug() << "mousePressed" << index;
}

void frmNavTitle::mouseReleased(int index)
{
    qDebug() << "mouseReleased" << index;
}
