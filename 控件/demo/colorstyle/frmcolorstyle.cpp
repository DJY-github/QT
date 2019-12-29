#include "frmcolorstyle.h"
#include "ui_frmcolorstyle.h"
#include "colorstyle.h"

frmColorStyle::frmColorStyle(QWidget *parent) : QWidget(parent), ui(new Ui::frmColorStyle)
{
    ui->setupUi(this);
    this->initForm();
}

frmColorStyle::~frmColorStyle()
{
    delete ui;
}

void frmColorStyle::initForm()
{
    QStringList colors;
    colors << "#26282C" << "#C62F2F" << "#FB79A5" << "#4BACF8" << "#159C77";
    colors << "#FF5C8A" << "#FF7A9E" << "#FE76C8" << "#717FF9" << "#39AFEA";
    colors << "#2BB669" << "#6ACC19" << "#E2AB12" << "#FD726D" << "#FD544E";

    widgets << ui->colorStyle1 << ui->colorStyle2 << ui->colorStyle3 << ui->colorStyle4 << ui->colorStyle5;
    widgets << ui->colorStyle6 << ui->colorStyle7 << ui->colorStyle8 << ui->colorStyle9 << ui->colorStyle10;
    widgets << ui->colorStyle11 << ui->colorStyle12 << ui->colorStyle13 << ui->colorStyle14 << ui->colorStyle15;

    for (int i = 0; i < widgets.count(); i++) {
        widgets.at(i)->setBgColor(colors.at(i));
        connect(widgets.at(i), SIGNAL(selected(QColor)), this, SLOT(selected(QColor)));
    }

    connect(ui->sliderRed, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
    connect(ui->sliderGreen, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
    connect(ui->sliderBlue, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));

    ui->colorStyle1->setChecked(true);
    ui->colorStyle0->setHovered(true);
}

void frmColorStyle::selected(const QColor &color)
{
    ColorStyle *w = (ColorStyle *)sender();

    foreach (ColorStyle *widget, widgets) {
        if (widget != w) {
            widget->setChecked(false);
        }
    }

    ui->sliderRed->setValue(color.red());
    ui->sliderGreen->setValue(color.green());
    ui->sliderBlue->setValue(color.blue());

    ui->labValue->setText(color.name().toUpper());
    ui->colorStyle0->setBgColor(color);
    ui->colorStyle0->setChecked(false);
    emit changeStyle(color.name());
}

void frmColorStyle::sliderReleased()
{
    foreach (ColorStyle *widget, widgets) {
        widget->setChecked(false);
    }

    int red = ui->sliderRed->value();
    int green = ui->sliderGreen->value();
    int blue = ui->sliderBlue->value();

    QColor color(red, green, blue);
    ui->labValue->setText(color.name().toUpper());
    ui->colorStyle0->setBgColor(color);
    ui->colorStyle0->setChecked(true);

    emit changeStyle(color.name());
}
