#pragma execution_character_set("utf-8")

#include "xlistwidgetvt.h"
#include "qpainter.h"
#include "qevent.h"
#include "qscrollbar.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qlayout.h"
#include "qmimedata.h"
#include "qdebug.h"

XListWidgetBox::XListWidgetBox(QWidget *parent)
{
    //生成一个组合控件,上面是等待放入的按钮,下面是表示位置
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setMargin(0);

    btnName = new QPushButton;
    btnName->setStyleSheet("color:#474849;background:#10161B;");
    btnName->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    verticalLayout->addWidget(btnName);

    btnPosition = new QPushButton;
    btnPosition->setStyleSheet("color:#F3F9FB;background:#687078;");
    btnPosition->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    verticalLayout->addWidget(btnPosition);

    //设置支持拖曳
    this->setAcceptDrops(true);
}

void XListWidgetBox::dragEnterEvent(QDragEnterEvent *e)
{
    //设置激活背景颜色
    btnName->setStyleSheet("color:#E0E0E0;background:#41BDFB;");
    e->accept();
}

void XListWidgetBox::dragLeaveEvent(QDragLeaveEvent *e)
{
    //设置默认背景颜色
    btnName->setStyleSheet("color:#474849;background:#10161B;");
}

void XListWidgetBox::dropEvent(QDropEvent *e)
{
    //设置默认背景颜色+设置文本
    btnName->setStyleSheet("color:#474849;background:#10161B;");
    btnName->setText(e->mimeData()->text());
}

QString XListWidgetBox::getName() const
{
    return btnName->text();
}

QString XListWidgetBox::getPosition() const
{
    return btnPosition->text();
}

void XListWidgetBox::setName(const QString &name)
{
    btnName->setText(name);
}

void XListWidgetBox::setPosition(const QString &position)
{
    btnPosition->setText(position);
}


XListWidgetVT::XListWidgetVT(QWidget *parent) : QListWidget(parent)
{
    this->initForm();
    this->initTitle();
    this->initStyle();
    this->initItem();
}

void XListWidgetVT::resizeEvent(QResizeEvent *e)
{
    //重新设置第一个元素即标题的宽度
    this->item(0)->setSizeHint(QSize(this->width() - this->spacing() * 2 - scrollWidth, 40));
    this->initScroll();
    QListWidget::resizeEvent(e);
}

void XListWidgetVT::initForm()
{
    textColor = QColor("#F3F9FB");
    bgColor = QColor("#26323E");
    selectTextColor = QColor("#323E54");
    selectBgColor = QColor("#41BDFB");
    hoverTextColor = QColor("#323E54");
    hoverBgColor = QColor("#687078");

    title = "控制大厅";
    titleColor = QColor("#137DB1");
    itemTexts = "";
    itemColor = QColor("#687078");

    itemCount = 0;
    itemWidth = 100;
    itemHeight = 70;

    scrollWidth = 10;
    scrollLeft = false;
    scrollColor = QColor("#26323E");

    //设置为图标模式
    this->setViewMode(QListView::IconMode);
    //设置拉伸自动调整
    this->setResizeMode(QListView::Adjust);
    //设置文字编辑模式
    this->setTextElideMode(Qt::ElideRight);
    //设置图标大小尺寸
    this->setIconSize(QSize(50, 50));
    //设置节点间隔
    this->setSpacing(10);
    //设置禁止拖动
    this->setDragEnabled(false);
    //设置鼠标追踪
    //this->setMouseTracking(true);

    //设置悬浮滚动条
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollBar = new QScrollBar(Qt::Vertical, this);
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), scrollBar, SLOT(setValue(int)));
    connect(scrollBar, SIGNAL(valueChanged(int)), this->verticalScrollBar(), SLOT(setValue(int)));
    connect(this->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), scrollBar, SLOT(setRange(int, int)));
}

void XListWidgetVT::initTitle()
{
    //生成标题栏,左侧line+label+右侧line
    QWidget *widgetTitle = new QWidget(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout(widgetTitle);
    horizontalLayout->setMargin(0);

    QFrame *line1 = new QFrame(widgetTitle);
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    horizontalLayout->addWidget(line1);

    labTitle = new QLabel(widgetTitle);
    labTitle->setObjectName("labTitle");
    labTitle->setText(title);
    labTitle->setAlignment(Qt::AlignCenter);
    horizontalLayout->addWidget(labTitle);

    QFrame *line2 = new QFrame(widgetTitle);
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    horizontalLayout->addWidget(line2);

    this->addItem("");
    this->setItemWidget(this->item(0), widgetTitle);
}

void XListWidgetVT::initStyle()
{
    //构建样式表
    QStringList qss;
    //主背景颜色
    qss.append(QString("QListView{border:none;outline:0px;color:%1;background:%2;padding-left:%3px;}")
               .arg(textColor.name()).arg(bgColor.name()).arg(scrollLeft ? 10 : 0));
    //产生按下凹凸感
    qss.append(QString("QListView::item{margin-top:2px;}"));
    //节点正常颜色
    qss.append(QString("QPushButton{color:%1;background:%2;border:2px solid #283440;border-radius:2px;}")
               .arg(textColor.name()).arg(itemColor.name()));
    //节点鼠标经过
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}")
               .arg(hoverTextColor.name()).arg(hoverBgColor.name()));
    //节点鼠标选中
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}")
               .arg(selectTextColor.name()).arg(selectBgColor.name()));
    //滚动条样式
    qss.append(QString("QScrollBar:vertical{min-width:1px;max-width:%1px;background:%2;}")
               .arg(scrollWidth).arg(scrollColor.name()));
    //标题文本
    qss.append(QString("QLabel{font:15px;color:%1;}").arg(titleColor.name()));
    //分割线颜色
    qss.append(QString("QFrame{background:#415569;}"));

    this->setStyleSheet(qss.join(""));
}

void XListWidgetVT::initScroll()
{
    //动态改变悬浮滚动条位置
    if (scrollLeft) {
        scrollBar->setGeometry(0, 0, scrollWidth, this->height());
    } else {
        scrollBar->setGeometry(this->width() - scrollWidth, 0, scrollWidth, this->height());
    }
}

void XListWidgetVT::initItem()
{
    this->clear();
    this->initTitle();
    resizeEvent(NULL);
    QStringList list = itemTexts.split(";");
    for (int i = 0; i < list.count(); i++) {
        QString text = list.at(i);
        if (!text.isEmpty()) {
            XListWidgetBox *btn = new XListWidgetBox;
            //btn->setName("等待拖入");
            btn->setPosition(text);
            this->addItem("");
            this->item(i + 1)->setSizeHint(QSize(itemWidth, itemHeight));
            this->setItemWidget(this->item(i + 1), btn);
        }
    }
}

void XListWidgetVT::itemClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    QString text = btn->text();
    QStringList list = itemTexts.split(";");
    emit itemClicked(list.indexOf(text), text);
}

QColor XListWidgetVT::getTextColor() const
{
    return this->textColor;
}

QColor XListWidgetVT::getBgColor() const
{
    return this->bgColor;
}

QColor XListWidgetVT::getSelectTextColor() const
{
    return this->selectTextColor;
}

QColor XListWidgetVT::getSelectBgColor() const
{
    return this->selectBgColor;
}

QColor XListWidgetVT::getHoverTextColor() const
{
    return this->hoverTextColor;
}

QColor XListWidgetVT::getHoverBgColor() const
{
    return this->hoverBgColor;
}

QString XListWidgetVT::getTitle() const
{
    return this->title;
}

QColor XListWidgetVT::getTitleColor() const
{
    return this->titleColor;
}

QString XListWidgetVT::getItemTexts() const
{
    return this->itemTexts;
}

QColor XListWidgetVT::getItemColor() const
{
    return this->itemColor;
}

int XListWidgetVT::getItemCount() const
{
    return this->itemCount;
}

int XListWidgetVT::getItemWidth() const
{
    return this->itemWidth;
}

int XListWidgetVT::getItemHeight() const
{
    return this->itemHeight;
}

int XListWidgetVT::getScrollWidth() const
{
    return this->scrollWidth;
}

bool XListWidgetVT::getScrollLeft() const
{
    return this->scrollLeft;
}

QColor XListWidgetVT::getScrollColor() const
{
    return this->scrollColor;
}

QSize XListWidgetVT::sizeHint() const
{
    return QSize(300, 250);
}

QSize XListWidgetVT::minimumSizeHint() const
{
    return QSize(30, 25);
}

void XListWidgetVT::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->initStyle();
    }
}

void XListWidgetVT::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->initStyle();
    }
}

void XListWidgetVT::setSelectTextColor(const QColor &selectTextColor)
{
    if (this->selectTextColor != selectTextColor) {
        this->selectTextColor = selectTextColor;
        this->initStyle();
    }
}

void XListWidgetVT::setSelectBgColor(const QColor &selectBgColor)
{
    if (this->selectBgColor != selectBgColor) {
        this->selectBgColor = selectBgColor;
        this->initStyle();
    }
}

void XListWidgetVT::setHoverTextColor(const QColor &hoverTextColor)
{
    if (this->hoverTextColor != hoverTextColor) {
        this->hoverTextColor = hoverTextColor;
        this->initStyle();
    }
}

void XListWidgetVT::setHoverBgColor(const QColor &hoverBgColor)
{
    if (this->hoverBgColor != hoverBgColor) {
        this->hoverBgColor = hoverBgColor;
        this->initStyle();
    }
}

void XListWidgetVT::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        labTitle->setText(title);
    }
}

void XListWidgetVT::setTitleColor(const QColor &titleColor)
{
    if (this->titleColor != titleColor) {
        this->titleColor = titleColor;
        this->initStyle();
    }
}

void XListWidgetVT::setItemTexts(const QString &itemTexts)
{
    if (this->itemTexts != itemTexts) {
        this->itemTexts = itemTexts;
        this->initItem();
    }
}

void XListWidgetVT::setItemColor(const QColor &itemColor)
{
    if (this->itemColor != itemColor) {
        this->itemColor = itemColor;
        this->initStyle();
    }
}

void XListWidgetVT::setItemCount(int itemCount)
{
    if (this->itemCount != itemCount && itemCount > 0) {
        this->itemCount = itemCount;

        //根据设定的个数实例化节点
        QStringList items;
        for (int i = 0; i < itemCount; i++) {
            items << QString("保障席%1").arg(i, 2, 10, QChar('0'));
        }

        itemTexts = items.join(";");
        this->initItem();
    }
}

void XListWidgetVT::setItemWidth(int itemWidth)
{
    if (this->itemWidth != itemWidth) {
        this->itemWidth = itemWidth;
        for (int i = 1; i < this->count(); i++) {
            this->item(i)->setSizeHint(QSize(itemWidth, itemHeight));
        }
    }
}

void XListWidgetVT::setItemHeight(int itemHeight)
{
    if (this->itemHeight != itemHeight) {
        this->itemHeight = itemHeight;
        for (int i = 1; i < this->count(); i++) {
            this->item(i)->setSizeHint(QSize(itemWidth, itemHeight));
        }
    }
}

void XListWidgetVT::setScrollWidth(int scrollWidth)
{
    if (this->scrollWidth != scrollWidth) {
        this->scrollWidth = scrollWidth;
        this->initStyle();
        this->initScroll();
    }
}

void XListWidgetVT::setScrollLeft(bool scrollLeft)
{
    if (this->scrollLeft != scrollLeft) {
        this->scrollLeft = scrollLeft;
        this->initStyle();
        this->initScroll();
    }
}

void XListWidgetVT::setScrollColor(const QColor &scrollColor)
{
    if (this->scrollColor != scrollColor) {
        this->scrollColor = scrollColor;
        this->initStyle();
    }
}
