#pragma execution_character_set("utf-8")

#include "frmnavprogress.h"
#include "ui_frmnavprogress.h"
#include "navprogress.h"
#include "qtimer.h"

frmNavProgress::frmNavProgress(QWidget *parent) : QWidget(parent), ui(new Ui::frmNavProgress)
{
	ui->setupUi(this);
    QTimer::singleShot(0, this, SLOT(initForm()));
}

frmNavProgress::~frmNavProgress()
{
	delete ui;
}

void frmNavProgress::initForm()
{
	QStringList topInfo;
	QStringList bottomInfo;

	topInfo.clear();
    topInfo << "创建订单" << "审核订单" << "生产" << "配送" << "签收";

    ui->navProgress1->setTopInfo(topInfo);
    ui->navProgress1->setMaxStep(5);
    ui->navProgress1->setCurrentStep(3);

    ui->navProgress2->setTopInfo(topInfo);
    ui->navProgress2->setMaxStep(5);
    ui->navProgress2->setCurrentStep(5);
    ui->navProgress2->setCurrentBackground(QColor(24,189,155));

	topInfo.clear();
	topInfo << "拍下商品" << "付款到支付宝" << "卖家发货" << "确认收货" << "评价";

	bottomInfo.clear();
	bottomInfo << "2016-11-24 20:58:59" << "2016-11-24 21:25:26" << "2016-11-25 10:25:26" << "2016-11-25 15:26:58" << "2016-11-25 20:36:39";

    ui->navProgress3->setTopInfo(topInfo);
    ui->navProgress3->setBottomInfo(bottomInfo);
    ui->navProgress3->setMaxStep(5);
    ui->navProgress3->setCurrentStep(3);
    ui->navProgress3->setNavStyle(NavProgress::NavStyle_TB);

    ui->navProgress4->setTopInfo(topInfo);
    ui->navProgress4->setBottomInfo(bottomInfo);
    ui->navProgress4->setMaxStep(5);
    ui->navProgress4->setCurrentStep(5);
    ui->navProgress4->setCurrentBackground(QColor(24,189,155));
    ui->navProgress4->setNavStyle(NavProgress::NavStyle_TB);

	topInfo.clear();
	topInfo << "已发货" << "运输中" << "派件中" << "已签收" << "已评价";

	bottomInfo.clear();
	bottomInfo << "深圳市" << "上海市";

    ui->navProgress5->setTopInfo(topInfo);
    ui->navProgress5->setBottomInfo(bottomInfo);
    ui->navProgress5->setMaxStep(5);
    ui->navProgress5->setCurrentStep(3);
    ui->navProgress5->setNavStyle(NavProgress::NavStyle_ZFB);

    ui->navProgress6->setTopInfo(topInfo);
    ui->navProgress6->setBottomInfo(bottomInfo);
    ui->navProgress6->setMaxStep(5);
    ui->navProgress6->setCurrentStep(5);
    ui->navProgress6->setCurrentBackground(QColor(24,189,155));
    ui->navProgress6->setNavStyle(NavProgress::NavStyle_ZFB);
}
