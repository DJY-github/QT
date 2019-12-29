#include "frmcolorpanelfader.h"
#include "ui_frmcolorpanelfader.h"

frmColorPanelFader::frmColorPanelFader(QWidget *parent) : QWidget(parent), ui(new Ui::frmColorPanelFader)
{
    ui->setupUi(this);

    connect(ui->colorPanelFader, SIGNAL(colorChanged(QColor, double, double, double)),
            this, SLOT(colorChanged(QColor, double, double, double)));
    colorChanged(Qt::red, 0, 100, 100);
}

frmColorPanelFader::~frmColorPanelFader()
{
    delete ui;
}

void frmColorPanelFader::colorChanged(const QColor &color, double hue, double sat, double bright)
{
    ui->labColor->setStyleSheet(QString("QLabel{background:%1;}").arg(color.name()));
}
