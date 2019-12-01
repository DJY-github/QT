#pragma execution_character_set("utf-8")

#include "frmselectwidget.h"
#include "ui_frmselectwidget.h"
#include "selectwidget.h"
#include "qpushbutton.h"
#include "qdial.h"

frmSelectWidget::frmSelectWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmSelectWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmSelectWidget::~frmSelectWidget()
{
    delete ui;
}

void frmSelectWidget::initForm()
{
    QPushButton *btn = new QPushButton(this);
    btn->setGeometry(10, 10, 100, 100);
    SelectWidget *selectBtn = new SelectWidget(this);
    connect(selectBtn, SIGNAL(widgetPressed(QWidget *)), this, SLOT(widgetPressed(QWidget *)));
    connect(selectBtn, SIGNAL(widgetRelease(QWidget *)), this, SLOT(widgetRelease(QWidget *)));
    selectBtn->setWidget(btn);
    selectWidgets.append(selectBtn);

    QDial *dial = new QDial(this);
    dial->setGeometry(120, 10, 100, 100);
    SelectWidget *selectDial = new SelectWidget(this);
    connect(selectDial, SIGNAL(widgetPressed(QWidget *)), this, SLOT(widgetPressed(QWidget *)));
    connect(selectDial, SIGNAL(widgetRelease(QWidget *)), this, SLOT(widgetRelease(QWidget *)));
    selectDial->setWidget(dial);
    selectDial->setPointSize(20);
    selectDial->setPointStyle(SelectWidget::PointStyle_Circle);
    selectDial->setPointColor(QColor(214, 77, 84));
    selectWidgets.append(selectDial);

    //立即执行获取焦点以及设置属性
    widgetPressed(btn);
}

void frmSelectWidget::clearFocus()
{
    //将原有焦点窗体全部设置成无焦点
    foreach (SelectWidget *widget, selectWidgets) {
        widget->setDrawPoint(false);
    }
}

void frmSelectWidget::widgetPressed(QWidget *widget)
{
    //清空所有控件的焦点
    clearFocus();

    //设置当前按下的控件有焦点
    foreach (SelectWidget *w, selectWidgets) {
        if (w->getWidget() == widget) {
            w->setDrawPoint(true);
            break;
        }
    }
}

void frmSelectWidget::widgetRelease(QWidget *widget)
{

}
