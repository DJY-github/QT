#pragma execution_character_set("utf-8")

#include "frmadswidget2.h"
#include "ui_frmadswidget2.h"

frmAdsWidget2::frmAdsWidget2(QWidget *parent) : QWidget(parent), ui(new Ui::frmAdsWidget2)
{
    ui->setupUi(this);
    this->initForm();
}

frmAdsWidget2::~frmAdsWidget2()
{
    delete ui;
}

void frmAdsWidget2::initForm()
{
    QString imageNames = ":/image/ad1.png;:/image/ad2.png;:/image/ad3.png";
    QString imageTips = "广告图片1;广告图片2;广告图片3";
    ui->adsWidget2->setImageNames(imageNames);
    ui->adsWidget2->setImageTips(imageTips);
}

void frmAdsWidget2::on_cboxNavPosition_currentIndexChanged(int index)
{
    ui->adsWidget2->setNavPosition((AdsWidget2::NavPosition)index);
}

void frmAdsWidget2::on_cboxNavStyle_currentIndexChanged(int index)
{
    ui->adsWidget2->setNavStyle((AdsWidget2::NavStyle)index);
}

void frmAdsWidget2::on_ckHoverStop_stateChanged(int arg1)
{
    ui->adsWidget2->setHoverStop(arg1 != 0);
}
