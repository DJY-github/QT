#include "frmcolorpanelbtn.h"
#include "ui_frmcolorpanelbtn.h"

frmColorPanelBtn::frmColorPanelBtn(QWidget *parent) : QWidget(parent), ui(new Ui::frmColorPanelBtn)
{
    ui->setupUi(this);
    connect(ui->colorPanelBtn, SIGNAL(colorChanged(QColor)), this, SLOT(colorChanged(QColor)));
    colorChanged(Qt::red);
}

frmColorPanelBtn::~frmColorPanelBtn()
{
    delete ui;
}

void frmColorPanelBtn::colorChanged(const QColor &color)
{
    ui->labColor->setStyleSheet(QString("QLabel{background:%1;}").arg(color.name()));
}
