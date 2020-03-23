#include "frmnavlistview.h"
#include "ui_frmnavlistview.h"
#include "navlistview.h"
#include "qdebug.h"

frmNavListView::frmNavListView(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmNavListView)
{
	ui->setupUi(this);
	this->initForm();
}

frmNavListView::~frmNavListView()
{
	delete ui;
}

void frmNavListView::initForm()
{
	ui->listView2->setIcoColorBg(false);
	ui->listView2->setColorLine(QColor(255, 255, 255));
	ui->listView2->setColorBg(QColor(238, 238, 238), QColor(255, 69, 0), QColor(255, 160, 122));
	ui->listView2->setColorText(QColor(10, 10, 10), QColor(254, 255, 239), QColor(10, 10, 10));

	ui->listView3->setIcoColorBg(false);
	ui->listView3->setColorLine(QColor(193, 193, 193));
	ui->listView3->setColorBg(QColor(255, 255, 255), QColor(232, 236, 245), QColor(242, 242, 242));
	ui->listView3->setColorText(QColor(19, 36, 62), QColor(19, 36, 62), QColor(19, 36, 62));

	ui->listView4->setIcoColorBg(false);
	ui->listView4->setColorLine(QColor(126, 127, 134));
	ui->listView4->setColorBg(QColor(42, 42, 42), QColor(42, 128, 185), QColor(117, 117, 117));
	ui->listView4->setColorText(QColor(126, 127, 134), QColor(211, 231, 240), QColor(255, 255, 255));

	ui->listView5->setIcoColorBg(false);
	ui->listView5->setColorLine(QColor(32, 53, 74));
	ui->listView5->setColorBg(QColor(52, 73, 94), QColor(24, 189, 155), QColor(24, 189, 155, 150));
	ui->listView5->setColorText(QColor(254, 255, 255), QColor(252, 252, 252), QColor(0, 0, 0));

    ui->listView1->setInfoVisible(false);
    ui->listView2->setInfoVisible(false);
    ui->listView3->setInfoVisible(false);
    ui->listView4->setInfoVisible(false);
    ui->listView5->setInfoVisible(false);

    ui->listView5->setLineVisible(false);
    ui->listView5->setIcoStyle(NavListView::IcoStyle_Triangle);

	ui->listView1->readData(":/image/config.xml");
	ui->listView2->readData(":/image/config.xml");
	ui->listView3->readData(":/image/config.xml");
	ui->listView4->readData(":/image/config.xml");
	ui->listView5->readData(":/image/config.xml");
}
