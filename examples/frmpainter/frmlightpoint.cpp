#include "frmlightpoint.h"
#include "ui_frmlightpoint.h"

frmLightPoint::frmLightPoint(QWidget *parent) : QWidget(parent), ui(new Ui::frmLightPoint)
{
    ui->setupUi(this);
    this->initForm();
}

frmLightPoint::~frmLightPoint()
{
    delete ui;
}

void frmLightPoint::initForm()
{
    ui->widget->setStyleSheet("QWidget#widget{background:url(:/image/bg1.jpg);}");
    widgets << ui->lightPoint1 << ui->lightPoint2 << ui->lightPoint3 << ui->lightPoint4 << ui->lightPoint5 << ui->lightPoint6;

    QList<QColor> colors;
    colors << "#47A4E9" << "#00B17D" << "#D64D54" << "#DEAF39" << "#A279C5" << "#009679";

    int count = widgets.count();
    for (int i = 0; i < count; i++) {
        //widgets.at(i)->setVisible(false);
        widgets.at(i)->setBgColor(colors.at(i));
    }

    //ui->lightPoint1->setVisible(true);
}
