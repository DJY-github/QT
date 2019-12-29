#pragma execution_character_set("utf-8")

#include "xlistwidgetvs.h"
#include "qpainter.h"
#include "qevent.h"
#include "qscrollbar.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qlayout.h"
#include "qmimedata.h"
#include "qdrag.h"
#include "qapplication.h"
#include "qtimer.h"
#include "qdebug.h"

XListWidgetVS::XListWidgetVS(QWidget *parent) : QListWidget(parent)
{
    this->initForm();
    this->initTitle();
    this->initStyle();
    this->initItem();
}

void XListWidgetVS::resizeEvent(QResizeEvent *e)
{
    //重新设置第一个元素即标题的宽度
    this->item(0)->setSizeHint(QSize(this->width() - this->spacing() * 2 - scrollWidth, 40));
    this->initScroll();
    QListWidget::resizeEvent(e);
}

bool XListWidgetVS::eventFilter(QObject *watched, QEvent *event)
{
    static bool pressed = false;
    static QPoint lastPoint = QPoint(0, 0);
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (mouseEvent->type() == QEvent::MouseButtonPress) {
        pressed = true;
        lastPoint = mouseEvent->pos();        
    } else if (mouseEvent->type() == QEvent::MouseMove) {
        if (pressed) {
            //当拖动距离大于一个推荐抖动距离时,表示同意已经拖动操作了
            int distance = (mouseEvent->pos() - lastPoint).manhattanLength();
            if(distance >= QApplication::startDragDistance()) {
                QPushButton *btn = (QPushButton *)watched;
                btn->click();
                QMimeData *mineData = new QMimeData;
                mineData->setText(btn->text());
                QDrag *drag = new QDrag(this);
                drag->setMimeData(mineData);
                drag->setPixmap(pixCursor);
                drag->exec(Qt::MoveAction);

                //完成后模拟鼠标点击取消选中状态
                QPoint pos(1, 1);
                QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                QApplication::sendEvent(btn, &event0);
                QMouseEvent event1(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                QApplication::sendEvent(btn, &event1);
            }
        }
    } else if (mouseEvent->type() == QEvent::MouseButtonRelease) {
        pressed = false;
    }

    return QListWidget::eventFilter(watched, event);
}

void XListWidgetVS::initForm()
{
    textColor = QColor("#F3F9FB");
    bgColor = QColor("#26323E");
    selectTextColor = QColor("#323E54");
    selectBgColor = QColor("#41BDFB");
    hoverTextColor = QColor("#323E54");
    hoverBgColor = QColor("#687078");

    title = "指挥大厅";
    titleColor = QColor("#137DB1");
    itemTexts = "";
    itemColor = QColor("#687078");

    itemCount = 0;
    itemWidth = 100;
    itemHeight = 40;

    scrollWidth = 10;
    scrollLeft = true;
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

void XListWidgetVS::initTitle()
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

void XListWidgetVS::initStyle()
{
    //构建样式表
    QStringList qss;
    //主背景颜色
    qss.append(QString("QListView{border:none;outline:0px;color:%1;background:%2;padding-left:%3px;}")
               .arg(textColor.name()).arg(bgColor.name()).arg(scrollLeft ? 10 : 0));
    //产生按下凹凸感
    qss.append(QString("QListView::item{margin-top:2px;}"));
    //节点正常颜色
    qss.append(QString("QPushButton{color:%1;background:%2;border:2px solid #283440;border-radius:5px;}")
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

    //动态生成鼠标形状,默认取鼠标按下颜色绘制,可自行更改为指定图片等
    //pixCursor = QPixmap(":/image/cursor.png");
    pixCursor = QPixmap(itemWidth - 10, itemHeight - 8);
    pixCursor.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pixCursor);
    painter.setPen(Qt::NoPen);
    painter.setBrush(selectBgColor);
    painter.drawRoundedRect(pixCursor.rect(), 5, 5);
    painter.end();
}

void XListWidgetVS::initScroll()
{
    //动态改变悬浮滚动条位置
    if (scrollLeft) {
        scrollBar->setGeometry(0, 0, scrollWidth, this->height());
    } else {
        scrollBar->setGeometry(this->width() - scrollWidth, 0, scrollWidth, this->height());
    }
}

void XListWidgetVS::initItem()
{
    this->clear();
    this->initTitle();
    resizeEvent(NULL);
    QStringList list = itemTexts.split(";");
    for (int i = 0; i < list.count(); i++) {
        QString text = list.at(i);
        if (!text.isEmpty()) {
            QPushButton *btn = new QPushButton;
            connect(btn, SIGNAL(clicked(bool)), this, SLOT(itemClicked()));
            btn->installEventFilter(this);
            btn->setText(text);
            this->addItem("");
            this->item(i + 1)->setSizeHint(QSize(itemWidth, itemHeight));
            this->setItemWidget(this->item(i + 1), btn);
        }
    }
}

void XListWidgetVS::itemClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    QString text = btn->text();
    QStringList list = itemTexts.split(";");
    emit itemClicked(list.indexOf(text), text);
}

QColor XListWidgetVS::getTextColor() const
{
    return this->textColor;
}

QColor XListWidgetVS::getBgColor() const
{
    return this->bgColor;
}

QColor XListWidgetVS::getSelectTextColor() const
{
    return this->selectTextColor;
}

QColor XListWidgetVS::getSelectBgColor() const
{
    return this->selectBgColor;
}

QColor XListWidgetVS::getHoverTextColor() const
{
    return this->hoverTextColor;
}

QColor XListWidgetVS::getHoverBgColor() const
{
    return this->hoverBgColor;
}

QString XListWidgetVS::getTitle() const
{
    return this->title;
}

QColor XListWidgetVS::getTitleColor() const
{
    return this->titleColor;
}

QString XListWidgetVS::getItemTexts() const
{
    return this->itemTexts;
}

QColor XListWidgetVS::getItemColor() const
{
    return this->itemColor;
}

int XListWidgetVS::getItemCount() const
{
    return this->itemCount;
}

int XListWidgetVS::getItemWidth() const
{
    return this->itemWidth;
}

int XListWidgetVS::getItemHeight() const
{
    return this->itemHeight;
}

int XListWidgetVS::getScrollWidth() const
{
    return this->scrollWidth;
}

bool XListWidgetVS::getScrollLeft() const
{
    return this->scrollLeft;
}

QColor XListWidgetVS::getScrollColor() const
{
    return this->scrollColor;
}

QSize XListWidgetVS::sizeHint() const
{
    return QSize(300, 250);
}

QSize XListWidgetVS::minimumSizeHint() const
{
    return QSize(30, 25);
}

void XListWidgetVS::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->initStyle();
    }
}

void XListWidgetVS::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->initStyle();
    }
}

void XListWidgetVS::setSelectTextColor(const QColor &selectTextColor)
{
    if (this->selectTextColor != selectTextColor) {
        this->selectTextColor = selectTextColor;
        this->initStyle();
    }
}

void XListWidgetVS::setSelectBgColor(const QColor &selectBgColor)
{
    if (this->selectBgColor != selectBgColor) {
        this->selectBgColor = selectBgColor;
        this->initStyle();
    }
}

void XListWidgetVS::setHoverTextColor(const QColor &hoverTextColor)
{
    if (this->hoverTextColor != hoverTextColor) {
        this->hoverTextColor = hoverTextColor;
        this->initStyle();
    }
}

void XListWidgetVS::setHoverBgColor(const QColor &hoverBgColor)
{
    if (this->hoverBgColor != hoverBgColor) {
        this->hoverBgColor = hoverBgColor;
        this->initStyle();
    }
}

void XListWidgetVS::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        labTitle->setText(title);
    }
}

void XListWidgetVS::setTitleColor(const QColor &titleColor)
{
    if (this->titleColor != titleColor) {
        this->titleColor = titleColor;
        this->initStyle();
    }
}

void XListWidgetVS::setItemTexts(const QString &itemTexts)
{
    if (this->itemTexts != itemTexts) {
        this->itemTexts = itemTexts;
        this->initItem();
    }
}

void XListWidgetVS::setItemColor(const QColor &itemColor)
{
    if (this->itemColor != itemColor) {
        this->itemColor = itemColor;
        this->initStyle();
    }
}

void XListWidgetVS::setItemCount(int itemCount)
{
    if (this->itemCount != itemCount && itemCount > 0) {
        this->itemCount = itemCount;

        //根据设定的个数实例化节点
        QStringList items;
        for (int i = 0; i < itemCount; i++) {
            items << QString("移动摄像机%1").arg(i, 2, 10, QChar('0'));
        }

        itemTexts = items.join(";");
        this->initItem();
    }
}

void XListWidgetVS::setItemWidth(int itemWidth)
{
    if (this->itemWidth != itemWidth) {
        this->itemWidth = itemWidth;
        for (int i = 1; i < this->count(); i++) {
            this->item(i)->setSizeHint(QSize(itemWidth, itemHeight));
        }
    }
}

void XListWidgetVS::setItemHeight(int itemHeight)
{
    if (this->itemHeight != itemHeight) {
        this->itemHeight = itemHeight;
        for (int i = 1; i < this->count(); i++) {
            this->item(i)->setSizeHint(QSize(itemWidth, itemHeight));
        }
    }
}

void XListWidgetVS::setScrollWidth(int scrollWidth)
{
    if (this->scrollWidth != scrollWidth) {
        this->scrollWidth = scrollWidth;
        this->initStyle();
        this->initScroll();
    }
}

void XListWidgetVS::setScrollLeft(bool scrollLeft)
{
    if (this->scrollLeft != scrollLeft) {
        this->scrollLeft = scrollLeft;
        this->initStyle();
        this->initScroll();
    }
}

void XListWidgetVS::setScrollColor(const QColor &scrollColor)
{
    if (this->scrollColor != scrollColor) {
        this->scrollColor = scrollColor;
        this->initStyle();
    }
}
