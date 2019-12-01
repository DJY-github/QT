#pragma execution_character_set("utf-8")

#include "frmcustomring.h"
#include "ui_frmcustomring.h"
#include "customring.h"

frmCustomRing::frmCustomRing(QWidget *parent) : QWidget(parent), ui(new Ui::frmCustomRing)
{
    ui->setupUi(this);
    this->initForm();
}

frmCustomRing::~frmCustomRing()
{
    delete ui;
}

void frmCustomRing::initForm()
{
#if 0
    //设置外圆数据
    {
        CustomRing::RingData data1;
        data1.color = QColor("#4CD0DD");
        data1.text = "直接访问";
        data1.percent = 60;

        CustomRing::RingData data2;
        data2.color = QColor("#DF86F0");
        data2.text = "邮件营销";
        data2.percent = 30;

        CustomRing::RingData data3;
        data3.color = QColor("#F5A7C1");
        data3.text = "联盟广告";
        data3.percent = 10;

        ui->customRing->appendOutPie(data1);
        ui->customRing->appendOutPie(data2);
        ui->customRing->appendOutPie(data3);
    }

    //设置内圆数据
    {
        CustomRing::RingData data1;
        data1.color = QColor("#F9D858");
        data1.text = "视频广告";
        data1.percent = 40;

        CustomRing::RingData data2;
        data2.color = QColor("#56A1D5");
        data2.text = "搜索引擎";
        data2.percent = 30;

        CustomRing::RingData data3;
        data3.color = QColor("#978BDF");
        data3.text = "其他广告";
        data3.percent = 30;

        ui->customRing->appendInPie(data1);
        ui->customRing->appendInPie(data2);
        ui->customRing->appendInPie(data3);
    }
#else
    //需要先设置颜色,也可以不设置直接用默认的颜色集合
    QList<QColor> outPieColors, inPieColors;
    outPieColors << QColor("#4CD0DD") << QColor("#DF86F0") << QColor("#F5A7C1");
    inPieColors << QColor("#F9D858") << QColor("#56A1D5") << QColor("#978BDF");
    ui->customRing->setOutPieColors(outPieColors);
    ui->customRing->setInPieColors(inPieColors);

    QString outPieInfos = "直接访问,60|邮件营销,30|联盟广告,10";
    QString inPieInfos = "视频广告,40|搜索引擎,30|其他广告,30";
    ui->customRing->setOutPieInfos(outPieInfos);
    ui->customRing->setInPieInfos(inPieInfos);
#endif

    //可以设置样式表来控制背景颜色+边框+圆角等
    QString qss = "CustomRing{background:#FF0000;border:5px solid #00FF00;border-radius:5px;}";
    //ui->customRing->setStyleSheet(qss);
    ui->customRing->setTitle("广告占比图");
}
