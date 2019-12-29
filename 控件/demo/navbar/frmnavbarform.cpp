#pragma execution_character_set("utf-8")

#include "frmnavbarform.h"
#include "ui_frmnavbarform.h"
#include "qtimer.h"
#include "qdebug.h"

frmNavBarForm::frmNavBarForm(QWidget *parent) : QWidget(parent), ui(new Ui::frmNavBarForm)
{
    ui->setupUi(this);
    this->initForm();
}

frmNavBarForm::~frmNavBarForm()
{
    delete ui;
}

void frmNavBarForm::showEvent(QShowEvent *)
{
    QTimer::singleShot(100, this, SLOT(setIndex()));
}

void frmNavBarForm::initForm()
{
    //设置圆角
    //ui->navBar->setBgRadius(5);
    //ui->navBar->setBarRadius(5);

    //设置间距,即元素高度
    ui->navBar->setSpace(18);
    ui->navBar->setBarColorStart(QColor(24, 189, 155));
    ui->navBar->setBarColorEnd(QColor(24, 189, 155));
    ui->navBar->setItems("主界面;系统设置;防区管理;警情查询;视频预览");
    connect(ui->navBar, SIGNAL(currentItemChanged(int, QString)), this, SLOT(currentItemChanged(int, QString)));
}

void frmNavBarForm::currentItemChanged(int index, const QString &item)
{
    ui->stackedWidget->setCurrentIndex(index);
    qDebug() << "index" << index << "item" << item;
}

void frmNavBarForm::setIndex()
{
    ui->navBar->setCurrentIndex(2);
}
