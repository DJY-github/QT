#pragma execution_character_set("utf-8")

#include "frmcombobox.h"
#include "ui_frmcombobox.h"

frmComboBox::frmComboBox(QWidget *parent) : QWidget(parent), ui(new Ui::frmComboBox)
{
    ui->setupUi(this);
    this->initForm();
}

frmComboBox::~frmComboBox()
{
    delete ui;
}

void frmComboBox::initForm()
{
    QStringList items;
    items << "1hello" << "2hello123456" << "3helloabcdefghijklmnopqrstuvw";

    //指定宽度,不自动计算元素宽度
    ui->cbox1->setAutoWidth(false);
    ui->cbox1->setItemWidth(300);
    ui->cbox1->addItems(items);

    //指定高度,自动计算元素宽度
    ui->cbox2->setAutoWidth(true);
    ui->cbox2->setItemHeight(30);
    ui->cbox2->addItems(items);

    ui->cbox3->setIconSize(QSize(100, 16));
    ui->cbox3->setShowColorName(false);
    ui->cbox3->initItems();
    ui->cbox4->initItems();
}
