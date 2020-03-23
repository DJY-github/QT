#include "mywidget.h"
#include <QApplication>
#include <QPushButton>
#include <QFont>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200,120);
    setMaximumSize(200,120);

    QPushButton *quit=new QPushButton("Quit",this);
    quit->setGeometry(62,40,75,30);
    quit->setFont(QFont("Times",18,QFont::Bold));

    connect(quit,SIGNAL(clicked()),qApp,SLOT(quit()));
}

MyWidget::~MyWidget()
{

}
