#pragma execution_character_set("utf-8")

#include "frmnavlabel.h"
#include "ui_frmnavlabel.h"

frmNavLabel::frmNavLabel(QWidget *parent) : QWidget(parent), ui(new Ui::frmNavLabel)
{
    ui->setupUi(this);
    this->initForm();
}

frmNavLabel::~frmNavLabel()
{
    delete ui;
}

void frmNavLabel::initForm()
{
    ui->navLabel11->setArrowPosition(NavLabel::ArrowPosition_Left);
    ui->navLabel12->setArrowPosition(NavLabel::ArrowPosition_Left);
    ui->navLabel13->setArrowPosition(NavLabel::ArrowPosition_Left);

    ui->navLabel21->setArrowPosition(NavLabel::ArrowPosition_Right);
    ui->navLabel22->setArrowPosition(NavLabel::ArrowPosition_Right);
    ui->navLabel23->setArrowPosition(NavLabel::ArrowPosition_Right);

    ui->navLabel31->setArrowPosition(NavLabel::ArrowPosition_Top);
    ui->navLabel32->setArrowPosition(NavLabel::ArrowPosition_Top);
    ui->navLabel33->setArrowPosition(NavLabel::ArrowPosition_Top);

    ui->navLabel41->setArrowPosition(NavLabel::ArrowPosition_Bottom);
    ui->navLabel42->setArrowPosition(NavLabel::ArrowPosition_Bottom);
    ui->navLabel43->setArrowPosition(NavLabel::ArrowPosition_Bottom);

    ui->navLabel12->setBackground(QColor(255, 107, 107));
    ui->navLabel13->setBackground(QColor(24, 189, 155));
    ui->navLabel21->setBackground(QColor(225, 102, 255));
    ui->navLabel22->setBackground(QColor(45, 62, 80));
    ui->navLabel23->setBackground(QColor(210, 84, 0));

    ui->navLabel32->setBackground(QColor(255, 107, 107));
    ui->navLabel33->setBackground(QColor(24, 189, 155));
    ui->navLabel41->setBackground(QColor(225, 102, 255));
    ui->navLabel42->setBackground(QColor(45, 62, 80));
    ui->navLabel43->setBackground(QColor(210, 84, 0));

    ui->navLabel51->setBorderRadius(0);
    ui->navLabel52->setBorderRadius(0);
    ui->navLabel53->setBorderRadius(0);
    ui->navLabel51->setBackground(QColor(80,80,80));
    ui->navLabel52->setBackground(QColor(80,80,80));
    ui->navLabel53->setBackground(QColor(80,80,80));
    ui->navLabel52->setShowTriangle(true);
    ui->navLabel53->setShowTriangle(true);
    ui->navLabel53->setShowArrow(false);

}
