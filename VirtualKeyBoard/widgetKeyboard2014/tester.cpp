
#include "tester.h"
#include "ui_tester.h"
#include <QLabel>


Tester::Tester(QWidget *parent)
    : QWidget(parent), ui(new Ui::Tester), myKeyboard(NULL)
{
    ui->setupUi(this);    
    this->myKeyboard = new widgetKeyBoard(false);
    this->myKeyboard->setZoomFacility(true);
    this->myKeyboard->enableSwitchingEcho(false); // enable possibility to change echo through keyboard
    this->myKeyboard->createKeyboard(); // only create keyboard
    ui->verticalLayout->addWidget(new QLabel(tr("Focus that below without virtual keyboard TAB:")));
    ui->verticalLayout->addWidget(new exampleMyFocus(this->myKeyboard)); // example how-to voluntary focus (hand-focus or mouse-focus)
      ui->verticalLayout->addWidget(new exampleMyFocus(this->myKeyboard)); // example how-to voluntary focus (hand-focus or mouse-focus)
}

Tester::~Tester()
{
    delete ui;    
    delete (this->myKeyboard);
}

void Tester::on_pushButton_clicked()
{
    myKeyboard->show(this); // once created keyboard object, use this method to switch between windows
    this->myKeyboard->move(this->x(), this->y() + this->myKeyboard->height()); // to move keyboard
}

void Tester::on_pushButton_2_clicked()
{
    myKeyboard->hide(true);
}

/*
void Tester::on_Tester_destroyed()
{

}
*/

void Tester::closeEvent(QCloseEvent * event)
{
    myKeyboard->hide(true);
    QWidget::closeEvent(event);
}

void Tester::on_pushButton_3_clicked()
{
}
