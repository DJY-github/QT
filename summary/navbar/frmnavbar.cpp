#pragma execution_character_set("utf-8")

#include "frmnavbar.h"
#include "ui_frmnavbar.h"
#include "navbar.h"
#include "qtimer.h"
#include "qdebug.h"

frmNavBar::frmNavBar(QWidget *parent) : QWidget(parent), ui(new Ui::frmNavBar)
{
    ui->setupUi(this);
    this->initForm();    
}

frmNavBar::~frmNavBar()
{
    delete ui;
}

void frmNavBar::showEvent(QShowEvent *)
{
    QTimer::singleShot(100, this, SLOT(setIndex()));
}

void frmNavBar::initForm()
{
    QString item = "系统设置;教师管理;学生管理;数据查询;关于";

    ui->navBar1->setBgRadius(5);
    ui->navBar2->setBgRadius(5);

    ui->navBar1->setBarRadius(5);
    ui->navBar2->setBarRadius(5);

    ui->navBar2->setBarColorStart(QColor(24, 189, 155));
    ui->navBar2->setBarColorEnd(QColor(26, 188, 156));

    ui->navBar4->setBarColorStart(QColor(24, 189, 155));
    ui->navBar4->setBarColorEnd(QColor(26, 188, 156));

    ui->navBar3->setLineWidth(3);
    ui->navBar3->setBarStyle(NavBar::BarStyle_Line_Top);

    ui->navBar4->setLineWidth(3);
    ui->navBar4->setBarStyle(NavBar::BarStyle_Line_Top);

    ui->navBar5->setLineWidth(4);
    ui->navBar5->setLineColor(QColor(24, 189, 155));
    ui->navBar5->setBarStyle(NavBar::BarStyle_Line_Bottom);

    ui->navBar6->setLineWidth(4);
    ui->navBar6->setLineColor(QColor(24, 189, 155));
    ui->navBar6->setBgColorStart(Qt::transparent);
    ui->navBar6->setBgColorEnd(Qt::transparent);
    ui->navBar6->setBarColorStart(Qt::transparent);
    ui->navBar6->setBarColorEnd(Qt::transparent);
    ui->navBar6->setTextNormalColor(QColor(50, 50, 50));
    ui->navBar6->setTextSelectColor(QColor(255, 107, 107));
    ui->navBar6->setBarStyle(NavBar::BarStyle_Line_Bottom);

    ui->navBar1->setItems(item);
    ui->navBar2->setItems(item);
    ui->navBar3->setItems(item);
    ui->navBar4->setItems(item);
    ui->navBar5->setItems(item);
    ui->navBar6->setItems(item);
    ui->navBarLeft->setItems(item);

    ui->navBarLeft->setSpace(15);
    ui->navBarLeft->setKeyMove(true);
    ui->navBarLeft->setHorizontal(false);
    ui->navBarLeft->setBarStyle(NavBar::BarStyle_Line_Left);

    ui->navBarLeft->setBarColorStart(QColor(13, 138, 166));
    ui->navBarLeft->setBarColorEnd(QColor(13, 138, 166));

    ui->navBarLeft->setBgColorStart(QColor(9, 52, 69));
    ui->navBarLeft->setBgColorEnd(QColor(9, 52, 69));

    ui->navBarLeft->setTextNormalColor(QColor(73, 138, 174));
    ui->navBarLeft->setTextSelectColor(QColor(223, 252, 253));

    ui->navBarLeft->setLineColor(QColor(223, 252, 253));
}

void frmNavBar::setIndex()
{
    ui->navBar1->setCurrentIndex(3);
    ui->navBar2->setCurrentIndex(0);
    ui->navBar3->setCurrentIndex(1);
    ui->navBar4->setCurrentIndex(4);
    ui->navBar5->setCurrentIndex(2);
    ui->navBar6->setCurrentIndex(0);
    ui->navBarLeft->setCurrentIndex(1);
}
