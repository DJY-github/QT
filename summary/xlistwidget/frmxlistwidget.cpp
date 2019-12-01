#pragma execution_character_set("utf-8")

#include "frmxlistwidget.h"
#include "ui_frmxlistwidget.h"
#include "iconfont.h"
#include "qdebug.h"

frmXListWidget::frmXListWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmXListWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmXListWidget::~frmXListWidget()
{
    delete ui;
}

void frmXListWidget::initForm()
{
#if 0
    //设置节点个数方式设置戒掉
    ui->listWidget->setItemCount(150);
#else
    //添加字符串形式设置节点
    QStringList items;
    for (int i = 1; i <= 20; i++) {
        items << QString("%1楼会议室").arg(i);
    }

    for (int i = 1; i <= 80; i++) {
        items << QString("3%1楼会议室").arg(i, 2, 10, QChar('0'));
    }

    ui->listWidget->setItemTexts(items.join(";"));
#endif

    //设置颜色
    QColor textColor("#F0F0F0");
    QColor selectTextColor("#00D2C2");
    QColor hoverTextColor("#47CAF6");
    ui->listWidget->setTextColor(textColor);
    ui->listWidget->setSelectTextColor(selectTextColor);
    ui->listWidget->setHoverTextColor(hoverTextColor);

    //设置节点图片,采用图形字体,海量的图形库
    QPixmap normalPixmap = IconFont::Instance()->getPixmap(textColor, 0xe6f1, 40, 45, 45);
    QPixmap selectPixmap = IconFont::Instance()->getPixmap(selectTextColor, 0xe6f1, 40, 45, 45);
    QPixmap hoverPixmap = IconFont::Instance()->getPixmap(hoverTextColor, 0xe6f1, 40, 45, 45);
    ui->listWidget->setNormalPixmap(normalPixmap);
    ui->listWidget->setSelectPixmap(selectPixmap);
    ui->listWidget->setHoverPixmap(hoverPixmap);

    //设置字体
    ui->listWidget->setFont(QFont("Microsoft Yahei", 9));
    //设置图标大小
    ui->listWidget->setIconSize(QSize(60, 60));
    //设置菜单启用禁用
    ui->listWidget->setEnableAdd(false);
    ui->listWidget->setEnableDelete(false);

    //绑定信号槽获取按下的节点以及菜单按下
    connect(ui->listWidget, SIGNAL(itemClicked(int, QString)), this, SLOT(itemClicked(int, QString)));
    connect(ui->listWidget, SIGNAL(menuClicked(QString)), this, SLOT(menuClicked(QString)));
}

void frmXListWidget::itemClicked(int index, const QString &text)
{
    qDebug() << "当前按下节点" << index << text;
}

void frmXListWidget::menuClicked(const QString &text)
{
    qDebug() << "当前按下菜单" << text;
}
