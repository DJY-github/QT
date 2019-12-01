#pragma execution_character_set("utf-8")

#include "frmnavlistview.h"
#include "ui_frmnavlistview.h"
#include "qtimer.h"

frmNavListView::frmNavListView(QWidget *parent) : QWidget(parent), ui(new Ui::frmNavListView)
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
    //设置节点数据,格式 标题|父节点标题(父节点为空)|是否展开|提示信息|左侧图标
    QStringList items;
    items.append("主界面||0|正常|");
    items.append("地图监控|主界面|||0xf03e");
    items.append("视频监控|主界面|||0xf03d");
    items.append("设备监控|主界面|||0xf108");

    items.append("系统设置||0||");
    items.append("防区信息|系统设置|||0xf0e8");
    items.append("位置调整|系统设置|||0xf060");
    items.append("地图编辑|系统设置|||0xf03e");

    items.append("警情查询||0|120|");
    items.append("记录查询|警情查询|||0xf073");
    items.append("图像查询|警情查询|||0xf03e");
    items.append("视频查询|警情查询|||0xf03d");
    items.append("数据回放|警情查询|||0xf080");

    items.append("帮助文档||1|1024|");

    ui->navListView1->setItems(items.join(","));
    ui->navListView2->setItems(items.join(","));
    ui->navListView3->setItems(items.join(","));
    ui->navListView4->setItems(items.join(","));

    ui->navListView1->setTipVisible(true);
    ui->navListView2->setTipVisible(false);
    ui->navListView3->setTipVisible(false);
    ui->navListView4->setTipVisible(false);

    ui->navListView2->setSeparateColor(QColor(255, 255, 255));
    ui->navListView2->setChildBgNormalColor(QColor(238, 238, 238));
    ui->navListView2->setChildBgSelectedColor(QColor(255, 69, 0));
    ui->navListView2->setChildBgHoverColor(QColor(255, 160, 122));
    ui->navListView2->setChildTextNormalColor(QColor(10, 10, 10));
    ui->navListView2->setChildTextSelectedColor(QColor(250, 250, 250));
    ui->navListView2->setChildTextHoverColor(QColor(10, 10, 10));
    ui->navListView2->setParentBgNormalColor(QColor(238, 238, 238));
    ui->navListView2->setParentBgSelectedColor(QColor(255, 69, 0));
    ui->navListView2->setParentBgHoverColor(QColor(255, 160, 122));
    ui->navListView2->setParentTextNormalColor(QColor(10, 10, 10));
    ui->navListView2->setParentTextSelectedColor(QColor(250, 250, 250));
    ui->navListView2->setParentTextHoverColor(QColor(10, 10, 10));

    ui->navListView3->setSeparateColor(QColor(193, 193, 193));
    ui->navListView3->setChildBgNormalColor(QColor(255, 255, 255));
    ui->navListView3->setChildBgSelectedColor(QColor(230, 230, 230));
    ui->navListView3->setChildBgHoverColor(QColor(240, 240, 240));
    ui->navListView3->setChildTextNormalColor(QColor(19, 36, 62));
    ui->navListView3->setChildTextSelectedColor(QColor(19, 36, 62));
    ui->navListView3->setChildTextHoverColor(QColor(19, 36, 62));
    ui->navListView3->setParentBgNormalColor(QColor(255, 255, 255));
    ui->navListView3->setParentBgSelectedColor(QColor(230, 230, 230));
    ui->navListView3->setParentBgHoverColor(QColor(240, 240, 240));
    ui->navListView3->setParentTextNormalColor(QColor(19, 36, 62));
    ui->navListView3->setParentTextSelectedColor(QColor(19, 36, 62));
    ui->navListView3->setParentTextHoverColor(QColor(19, 36, 62));

    ui->navListView4->setSeparateColor(QColor(32, 53, 74));
    ui->navListView4->setChildBgNormalColor(QColor(52, 73, 94));
    ui->navListView4->setChildBgSelectedColor(QColor(24, 189, 155));
    ui->navListView4->setChildBgHoverColor(QColor(24, 189, 155));
    ui->navListView4->setChildTextNormalColor(QColor(250, 250, 250));
    ui->navListView4->setChildTextSelectedColor(QColor(230, 230, 230));
    ui->navListView4->setChildTextHoverColor(QColor(10, 10, 10));
    ui->navListView4->setParentBgNormalColor(QColor(52, 73, 94));
    ui->navListView4->setParentBgSelectedColor(QColor(24, 189, 155));
    ui->navListView4->setParentBgHoverColor(QColor(24, 189, 155));
    ui->navListView4->setParentTextNormalColor(QColor(250, 250, 250));
    ui->navListView4->setParentTextSelectedColor(QColor(230, 230, 230));
    ui->navListView4->setParentTextHoverColor(QColor(10, 10, 10));

    ui->navListView1->setExpendMode(NavListView::ExpendMode_SingleClick);
    ui->navListView2->setExpendMode(NavListView::ExpendMode_DoubleClick);
    ui->navListView3->setExpendMode(NavListView::ExpendMode_SingleClick);
    ui->navListView4->setExpendMode(NavListView::ExpendMode_DoubleClick);
}
