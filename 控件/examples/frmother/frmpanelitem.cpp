#pragma execution_character_set("utf-8")

#include "frmpanelitem.h"
#include "ui_frmpanelitem.h"
#include "panelitem.h"

frmPanelItem::frmPanelItem(QWidget *parent) : QWidget(parent), ui(new Ui::frmPanelItem)
{
    ui->setupUi(this);
    this->initForm();
}

frmPanelItem::~frmPanelItem()
{
    delete ui;
}

void frmPanelItem::initForm()
{
    items << ui->panelItem1 << ui->panelItem2 << ui->panelItem3 << ui->panelItem4;
    ui->cboxAlignment->setCurrentIndex(1);

    for (int i = 0; i < items.count(); i++) {
        items.at(i)->setTitleText(QString("标题%1").arg(i + 1));
    }
}

void frmPanelItem::on_btnDisable_clicked()
{
    foreach (PanelItem *item, items) {
        item->setEnable(false);
    }
}

void frmPanelItem::on_btnEnable_clicked()
{
    foreach (PanelItem *item, items) {
        item->setEnable(true);
    }
}

void frmPanelItem::on_btnAlarm_clicked()
{
    foreach (PanelItem *item, items) {
        item->setAlarm(true);
    }
}

void frmPanelItem::on_btnNormal_clicked()
{
    foreach (PanelItem *item, items) {
        item->setAlarm(false);
    }
}

void frmPanelItem::on_cboxAlignment_activated(int index)
{
    foreach (PanelItem *item, items) {
        item->setTitleAlignment((PanelItem::Alignment)index);
    }
}

void frmPanelItem::on_cboxColor_activated(int index)
{
    QList<QColor> colors;
    colors << QColor("#16A085") << QColor("#2980B9") << QColor("#8E44AD") << QColor("#2C3E50");
    foreach (PanelItem *item, items) {
        item->setBorderColor(colors.at(index));
    }
}
