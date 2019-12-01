#pragma execution_character_set("utf-8")

#include "frmledtext.h"
#include "ui_frmledtext.h"

frmLedText::frmLedText(QWidget *parent) : QWidget(parent), ui(new Ui::frmLedText)
{
    ui->setupUi(this);
    this->initForm();
}

frmLedText::~frmLedText()
{
    delete ui;
}

void frmLedText::initForm()
{
    ui->ledText1->setText("123456789");
    ui->ledText2->setText("ABCDEFG");
    ui->ledText3->setText("飞扬青云-游龙");

    ui->ledText2->setForeground(QColor(255, 107, 107));
    ui->ledText3->setForeground(QColor(0, 255, 255));
}
