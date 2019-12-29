#pragma execution_character_set("utf-8")

#include "frmvideoplayback.h"
#include "ui_frmvideoplayback.h"
#include "videoplayback.h"

frmVideoPlayback::frmVideoPlayback(QWidget *parent) : QWidget(parent), ui(new Ui::frmVideoPlayback)
{
    ui->setupUi(this);
    this->initForm();
}

frmVideoPlayback::~frmVideoPlayback()
{
    delete ui;
}

void frmVideoPlayback::initForm()
{
    VideoCh::VideoData data1, data2, data3, data4;

    data1.startX = 30;
    data1.length = 150;
    data2.startX = 200;
    data2.length = 50;
    data3.startX = 280;
    data3.length = 100;
    ui->videoPlayback1->setDatas1(QList<VideoCh::VideoData>() << data1 << data2 << data3);

    data4.startX = 30;
    data4.length = 380;
    ui->videoPlayback1->setDatas2(QList<VideoCh::VideoData>() << data4);
    ui->videoPlayback1->setDatas3(QList<VideoCh::VideoData>() << data4);
    ui->videoPlayback1->setDatas4(QList<VideoCh::VideoData>() << data4);
}
