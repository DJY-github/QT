#pragma execution_character_set("utf-8")

#include "xlistwidget.h"
#include "qscrollbar.h"
#include "qaction.h"
#include "qdebug.h"

XListWidget::XListWidget(QWidget *parent) : QListWidget(parent)
{
    this->initForm();
    this->initAction();
    this->initStyle();
    this->initItem();
}

void XListWidget::resizeEvent(QResizeEvent *e)
{
    this->initScroll();
    QListWidget::resizeEvent(e);
}

void XListWidget::leaveEvent(QEvent *)
{
    //鼠标从当前控件离开时候要恢复最后一个节点的图标
    if (hoverItem != 0) {
        QIcon icon;
        icon.addPixmap(normalPixmap, QIcon::Normal);
        icon.addPixmap(selectPixmap, QIcon::Selected);
        hoverItem->setIcon(icon);
    }
}

void XListWidget::initForm()
{
    textColor = QColor("#9A9C9F");
    bgColor = QColor("#26323E");
    selectTextColor = QColor("#1296DB");
    selectBgColor = QColor("#26323E");
    hoverTextColor = QColor("#D4237A");
    hoverBgColor = QColor("#26323E");

    itemTexts = "";
    normalPixmap = QPixmap(":/image/xlistwidget_normal.png");
    selectPixmap = QPixmap(":/image/xlistwidget_select.png");
    hoverPixmap = QPixmap(":/image/xlistwidget_hover.png");

    itemCount = 0;
    itemWidth = 80;
    itemHeight = 80;    

    scrollWidth = 10;
    scrollLeft = true;
    scrollColor = QColor("#26323E");

    enableEdit = true;
    enableAdd = true;
    enableDelete = true;

    hoverItem = 0;

    //设置为图标模式
    this->setViewMode(QListView::IconMode);
    //设置拉伸自动调整
    this->setResizeMode(QListView::Adjust);
    //设置文字编辑模式
    this->setTextElideMode(Qt::ElideRight);
    //设置图标大小尺寸
    this->setIconSize(QSize(50, 50));
    //设置节点间隔
    this->setSpacing(2);
    //设置禁止拖动
    this->setDragEnabled(false);
    //设置鼠标追踪
    this->setMouseTracking(true);

    //绑定按下事件+鼠标进入事件
    connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClicked(QListWidgetItem *)));
    connect(this, SIGNAL(itemEntered(QListWidgetItem *)), this, SLOT(itemEntered(QListWidgetItem *)));

    //设置悬浮滚动条
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollBar = new QScrollBar(Qt::Vertical, this);
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), scrollBar, SLOT(setValue(int)));
    connect(scrollBar, SIGNAL(valueChanged(int)), this->verticalScrollBar(), SLOT(setValue(int)));
    connect(this->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), scrollBar, SLOT(setRange(int, int)));
}

void XListWidget::initAction()
{
    //添加右键菜单
    actionEdit = new QAction("编辑", this);
    actionAdd = new QAction("添加", this);
    actionDelete = new QAction("删除", this);

    connect(actionEdit, SIGNAL(triggered(bool)), this, SLOT(menuClicked()));
    connect(actionAdd, SIGNAL(triggered(bool)), this, SLOT(menuClicked()));
    connect(actionDelete, SIGNAL(triggered(bool)), this, SLOT(menuClicked()));

    this->addAction(actionEdit);
    this->addAction(actionAdd);
    this->addAction(actionDelete);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void XListWidget::initStyle()
{
    //构建样式表
    QStringList qss;
    //主背景颜色
    qss.append(QString("QListView{padding:5px %1px 0px %2px;border:none;outline:0px;color:%3;background:%4;}")
               .arg(scrollLeft ? 0 : scrollWidth).arg(scrollLeft ? scrollWidth : 0).arg(textColor.name()).arg(bgColor.name()));
    //产生按下凹凸感
    qss.append(QString("QListView::item{margin-top:2px;}"));    
    //节点鼠标经过
    qss.append(QString("QListView::item:hover{color:%1;background:%2;}")
               .arg(hoverTextColor.name()).arg(hoverBgColor.name()));
    //节点鼠标选中
    qss.append(QString("QListView::item:selected{color:%1;background:%2;}")
               .arg(selectTextColor.name()).arg(selectBgColor.name()));
    //滚动条样式
    qss.append(QString("QScrollBar:vertical{min-width:1px;max-width:%1px;background:%2;}")
               .arg(scrollWidth).arg(scrollColor.name()));

    this->setStyleSheet(qss.join(""));
}

void XListWidget::initScroll()
{
    //动态改变悬浮滚动条位置
    if (scrollLeft) {
        scrollBar->setGeometry(0, 0, scrollWidth, this->height());
    } else {
        scrollBar->setGeometry(this->width() - scrollWidth, 0, scrollWidth, this->height());
    }
}

void XListWidget::initPixmap()
{
    QIcon icon;
    icon.addPixmap(normalPixmap, QIcon::Normal);
    icon.addPixmap(selectPixmap, QIcon::Selected);
    icon.addPixmap(hoverPixmap, QIcon::Active);

    for (int i = 0; i < this->count(); i++) {
        this->item(i)->setIcon(icon);
    }
}

void XListWidget::initItem()
{
    this->clear();
    QStringList list = itemTexts.split(";");
    for (int i=0;i<list.count();i++){
        QString text=list.at(i);
        if (!text.isEmpty()) {
            QListWidgetItem *item = new QListWidgetItem(this);
            //item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsDragEnabled);
            item->setText(text);
            item->setSizeHint(QSize(itemWidth, itemHeight));
            this->addItem(item);
        }
    }

    this->initPixmap();
}

void XListWidget::itemClicked(QListWidgetItem *item)
{
    QString text = item->text();
    QStringList list = itemTexts.split(";");
    emit itemClicked(list.indexOf(text), text);
}

void XListWidget::itemEntered(QListWidgetItem *item)
{
    //记住上一个悬停过的item,要恢复
    if (hoverItem != 0 && hoverItem != item) {
        QIcon icon;
        icon.addPixmap(normalPixmap, QIcon::Normal);
        icon.addPixmap(selectPixmap, QIcon::Selected);
        hoverItem->setIcon(icon);
    }

    QIcon icon;
    icon.addPixmap(hoverPixmap, QIcon::Normal);
    icon.addPixmap(selectPixmap, QIcon::Selected);
    item->setIcon(icon);
    hoverItem = item;
}

void XListWidget::menuClicked()
{
    QAction *action = (QAction *)sender();
    emit menuClicked(action->text());
}

QColor XListWidget::getTextColor() const
{
    return this->textColor;
}

QColor XListWidget::getBgColor() const
{
    return this->bgColor;
}

QColor XListWidget::getSelectTextColor() const
{
    return this->selectTextColor;
}

QColor XListWidget::getSelectBgColor() const
{
    return this->selectBgColor;
}

QColor XListWidget::getHoverTextColor() const
{
    return this->hoverTextColor;
}

QColor XListWidget::getHoverBgColor() const
{
    return this->hoverBgColor;
}

QString XListWidget::getItemTexts() const
{
    return this->itemTexts;
}

QPixmap XListWidget::getNormalPixmap() const
{
    return this->normalPixmap;
}

QPixmap XListWidget::getSelectPixmap() const
{
    return this->selectPixmap;
}

QPixmap XListWidget::getHoverPixmap() const
{
    return this->hoverPixmap;
}

int XListWidget::getItemCount() const
{
    return this->itemCount;
}

int XListWidget::getItemWidth() const
{
    return this->itemWidth;
}

int XListWidget::getItemHeight() const
{
    return this->itemHeight;
}

int XListWidget::getScrollWidth() const
{
    return this->scrollWidth;
}

bool XListWidget::getScrollLeft() const
{
    return this->scrollLeft;
}

QColor XListWidget::getScrollColor() const
{
    return this->scrollColor;
}

bool XListWidget::getEnableEdit() const
{
    return this->enableEdit;
}

bool XListWidget::getEnableAdd() const
{
    return this->enableAdd;
}

bool XListWidget::getEnableDelete() const
{
    return this->enableDelete;
}

QSize XListWidget::sizeHint() const
{
    return QSize(300, 250);
}

QSize XListWidget::minimumSizeHint() const
{
    return QSize(30, 25);
}

void XListWidget::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->initStyle();
    }
}

void XListWidget::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->initStyle();
    }
}

void XListWidget::setSelectTextColor(const QColor &selectTextColor)
{
    if (this->selectTextColor != selectTextColor) {
        this->selectTextColor = selectTextColor;
        this->initStyle();
    }
}

void XListWidget::setSelectBgColor(const QColor &selectBgColor)
{
    if (this->selectBgColor != selectBgColor) {
        this->selectBgColor = selectBgColor;
        this->initStyle();
    }
}

void XListWidget::setHoverTextColor(const QColor &hoverTextColor)
{
    if (this->hoverTextColor != hoverTextColor) {
        this->hoverTextColor = hoverTextColor;
        this->initStyle();
    }
}

void XListWidget::setHoverBgColor(const QColor &hoverBgColor)
{
    if (this->hoverBgColor != hoverBgColor) {
        this->hoverBgColor = hoverBgColor;
        this->initStyle();
    }
}

void XListWidget::setItemTexts(const QString &itemTexts)
{
    if (this->itemTexts != itemTexts) {
        this->itemTexts = itemTexts;
        this->initItem();
    }
}

void XListWidget::setNormalPixmap(const QPixmap &normalPixmap)
{
    this->normalPixmap = normalPixmap;
    this->initPixmap();
}

void XListWidget::setSelectPixmap(const QPixmap &selectPixmap)
{
    this->selectPixmap = selectPixmap;
    this->initPixmap();
}

void XListWidget::setHoverPixmap(const QPixmap &hoverPixmap)
{
    this->hoverPixmap = hoverPixmap;
    this->initPixmap();
}

void XListWidget::setItemCount(int itemCount)
{
    if (this->itemCount != itemCount && itemCount > 0) {
        this->itemCount = itemCount;

        //根据设定的个数实例化节点
        QStringList items;
        for (int i = 0; i < itemCount; i++) {
            items << QString("3%1楼会议室").arg(i, 2, 10, QChar('0'));
        }

        itemTexts = items.join(";");
        this->initItem();
    }
}

void XListWidget::setItemWidth(int itemWidth)
{
    if (this->itemWidth != itemWidth) {
        this->itemWidth = itemWidth;
        for (int i = 0; i < this->count(); i++) {
            this->item(i)->setSizeHint(QSize(itemWidth, itemHeight));
        }
    }
}

void XListWidget::setItemHeight(int itemHeight)
{
    if (this->itemHeight != itemHeight) {
        this->itemHeight = itemHeight;
        for (int i = 0; i < this->count(); i++) {
            this->item(i)->setSizeHint(QSize(itemWidth, itemHeight));
        }
    }
}

void XListWidget::setScrollWidth(int scrollWidth)
{
    if (this->scrollWidth != scrollWidth) {
        this->scrollWidth = scrollWidth;
        this->initStyle();
        this->initScroll();
    }
}

void XListWidget::setScrollLeft(bool scrollLeft)
{
    if (this->scrollLeft != scrollLeft) {
        this->scrollLeft = scrollLeft;
        this->initStyle();
        this->initScroll();
    }
}

void XListWidget::setScrollColor(const QColor &scrollColor)
{
    if (this->scrollColor != scrollColor) {
        this->scrollColor = scrollColor;
        this->initStyle();
    }
}

void XListWidget::setEnableEdit(bool enableEdit)
{
    if (this->enableEdit != enableEdit) {
        this->enableEdit = enableEdit;
        actionEdit->setEnabled(enableEdit);
    }
}

void XListWidget::setEnableAdd(bool enableAdd)
{
    if (this->enableAdd != enableAdd) {
        this->enableAdd = enableAdd;
        actionAdd->setEnabled(enableAdd);
    }
}

void XListWidget::setEnableDelete(bool enableDelete)
{
    if (this->enableDelete != enableDelete) {
        this->enableDelete = enableDelete;
        actionDelete->setEnabled(enableDelete);
    }
}
