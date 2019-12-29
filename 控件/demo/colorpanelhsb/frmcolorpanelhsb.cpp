#include "frmcolorpanelhsb.h"
#include "ui_frmcolorpanelhsb.h"
#include "qdebug.h"

frmColorPanelHSB::frmColorPanelHSB(QWidget *parent) : QWidget(parent), ui(new Ui::frmColorPanelHSB)
{
    ui->setupUi(this);

    connect(ui->colorPanelHSB, SIGNAL(colorChanged(QColor, double, double)),
            this, SLOT(colorChangedHSB(QColor, double, double)));
    connect(ui->colorPanelBar, SIGNAL(colorChanged(QColor, double, double)),
            this, SLOT(colorChangedBar(QColor, double, double)));

    ui->colorPanelBar->setStaticMode(false);
    colorChangedBar(Qt::red, ui->colorPanelBar->getValue(), ui->colorPanelBar->getPercent());
}

frmColorPanelHSB::~frmColorPanelHSB()
{
    delete ui;
}

void frmColorPanelHSB::colorChangedHSB(const QColor &color, double hue, double sat)
{
    ui->colorPanelBar->setTopColor(color);
    ui->colorPanelBar->setBorderColor(color);
    colorChangedBar(ui->colorPanelBar->getColor(), ui->colorPanelBar->getValue(), ui->colorPanelBar->getPercent());
}

void frmColorPanelHSB::colorChangedBar(const QColor &color, double value, double percent)
{
    ui->colorPanelHSB->setPercent(percent);
    ui->labColor->setStyleSheet(QString("QLabel{background:%1;}").arg(color.name()));
}
