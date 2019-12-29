#pragma execution_character_set("utf-8")

#include "frmadswidget.h"
#include "ui_frmadswidget.h"

frmAdsWidget::frmAdsWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmAdsWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmAdsWidget::~frmAdsWidget()
{
    delete ui;
}

void frmAdsWidget::initForm()
{
    ui->adsWidget1->setFixedSize(QSize(564, 182));
    ui->adsWidget2->setFixedSize(QSize(564, 182));

    ui->adsWidget1->setInterval(1000);
    ui->adsWidget1->setBannerFixedSize(QSize(20, 10));
    ui->adsWidget1->setImageNames(":/image/ad1.png;:/image/ad2.png;:/image/ad3.png");
    ui->adsWidget1->setBannerStyle(AdsWidget::BannerStyle_Min);

    ui->adsWidget2->setImageNames(":/image/ad1.png;:/image/ad2.png;:/image/ad3.png");
}
