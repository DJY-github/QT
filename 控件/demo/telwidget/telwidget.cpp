#pragma execution_character_set("utf-8")

#include "telwidget.h"
#include "zhtopy.h"
#include "qpainter.h"
#include "qevent.h"
#include "qapplication.h"
#include "qpropertyanimation.h"
#include "qscrollarea.h"
#include "qscrollbar.h"
#include "qstyle.h"
#include "qstyleoption.h"
#include "qlayout.h"
#include "qlabel.h"
#include "qtimer.h"
#include "qdebug.h"

TelHigh::TelHigh(QWidget *parent) : QWidget(parent)
{
    fontSize = 30;
    bgImage = QPixmap();
    bgColor = Qt::transparent;
    text = "A";
    textColor = QColor(255, 255, 255);
}

void TelHigh::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height) / 2 - 1;

    //设置平滑绘制
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //设置字体大小
    QFont font;
    font.setPixelSize(fontSize);
    painter.setFont(font);

    //优先绘制背景图片,居中绘制
    QRectF textRect;
    if (!bgImage.isNull()) {
        QPixmap pix = bgImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int pixX = rect().center().x() - pix.width() / 2;
        int pixY = rect().center().y() - pix.height() / 2;
        QPoint point(pixX, pixY);
        painter.drawPixmap(point, pix);
        textRect = QRectF(0, 0, width - 40, height - 5);
    } else {
        painter.setPen(Qt::NoPen);
        painter.setBrush(bgColor);
        painter.drawEllipse(rect().center(), side, side);
        textRect = this->rect();
    }

    //绘制文字
    painter.setPen(textColor);
    painter.drawText(textRect, Qt::AlignCenter, text);
}

int TelHigh::getFontSize() const
{
    return this->fontSize;
}

QPixmap TelHigh::getBgImage() const
{
    return this->bgImage;
}

QColor TelHigh::getBgColor() const
{
    return this->bgColor;
}

QString TelHigh::getText() const
{
    return this->text;
}

QColor TelHigh::getTextColor() const
{
    return this->textColor;
}

void TelHigh::setFontSize(int fontSize)
{
    if (this->fontSize != fontSize) {
        this->fontSize = fontSize;
        update();
    }
}

void TelHigh::setBgImage(const QPixmap &bgImage)
{
    this->bgImage = bgImage;
    update();
}

void TelHigh::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void TelHigh::setText(const QString &text)
{
    if (this->text != text) {
        this->text = text;
        update();
    }
}

void TelHigh::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}


TelBanner::TelBanner(QWidget *parent) : QWidget(parent)
{
    line = false;
    padding = 15;
    fontSize = 15;
    text = "A";

    textColor = QColor(50, 50, 50);
    bgColor = QColor(0, 0, 0, 30);
    lineColor = QColor(0, 0, 0, 180);
}

void TelBanner::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();

    //设置平滑绘制
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //可选绘制顶部线条还是背景颜色
    if (line) {
        QPen pen;
        pen.setWidth(2);
        pen.setColor(lineColor);
        painter.setPen(pen);
        painter.drawLine(QPointF(0, 0), QPointF(width, 0));
    } else {
        painter.setPen(Qt::NoPen);
        painter.setBrush(bgColor);
        painter.drawRect(0, 0, width, height);
    }

    //设置字体
    QFont font;
    font.setPixelSize(fontSize);
    painter.setFont(font);

    //绘制文字
    QRectF textRect(padding, 0, width - padding, height);
    painter.setPen(textColor);
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
}

bool TelBanner::getLine() const
{
    return this->line;
}

int TelBanner::getPadding() const
{
    return this->padding;
}

int TelBanner::getFontSize() const
{
    return this->fontSize;
}

QString TelBanner::getText() const
{
    return this->text;
}

QColor TelBanner::getTextColor() const
{
    return this->textColor;
}

QColor TelBanner::getBgColor() const
{
    return this->bgColor;
}

QColor TelBanner::getLineColor() const
{
    return this->lineColor;
}

QSize TelBanner::sizeHint() const
{
    return QSize(100, 35);
}

QSize TelBanner::minimumSizeHint() const
{
    return QSize(30, 30);
}

void TelBanner::setLine(bool line)
{
    if (this->line != line) {
        this->line = line;
        update();
    }
}

void TelBanner::setPadding(int padding)
{
    if (this->padding != padding) {
        this->padding = padding;
        update();
    }
}

void TelBanner::setFontSize(int fontSize)
{
    if (this->fontSize != fontSize) {
        this->fontSize = fontSize;
        update();
    }
}

void TelBanner::setText(const QString &text)
{
    if (this->text != text) {
        this->text = text;
        update();
    }
}

void TelBanner::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void TelBanner::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void TelBanner::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}


TelLetter::TelLetter(QWidget *parent) : QWidget(parent)
{
    letters = "*ABCDEFGHIJKLMNOPQRSTUVWXYZ#";
    highLetter = "A";

    normalColor = QColor(100, 100, 100);
    highColor = QColor(34, 163, 169);

    pressed = false;
}

void TelLetter::mousePressEvent(QMouseEvent *event)
{
    checkPos(event->pos());
    pressed = true;
}

void TelLetter::mouseReleaseEvent(QMouseEvent *event)
{
    pressed = false;
}

void TelLetter::mouseMoveEvent(QMouseEvent *event)
{
    if (pressed) {
        checkPos(event->pos());
    }
}

void TelLetter::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();

    //设置平滑绘制
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //计算当前高度每个字母所占的高度
    QStringList list = letters.split("");
    int count = list.count();
    int letterHeight = height / (count - 2);

    //在最右侧垂直依次绘制
    int letterY = 0;
    QFont font;
    for (int i = 1; i < count - 1; i++) {
        QString str = list.at(i);
        QRect textRect(0, letterY, width, letterHeight);

        //突出显示高亮字母
        if (str == highLetter) {
            font.setBold(true);
            painter.setPen(highColor);
        } else {
            font.setBold(false);
            painter.setPen(normalColor);
        }

        painter.setFont(font);
        painter.drawText(textRect, Qt::AlignCenter, str);
        letterY += letterHeight;
    }
}

void TelLetter::checkPos(const QPoint &pos)
{
    //根据按下处的坐标
    int letterY = pos.y();

    //如果超过当前窗体范围则不处理
    if (letterY < 30 || letterY > (height() - 30)) {
        return;
    }

    //计算当前高度每个字母所占的高度
    QStringList list = letters.split("");
    int count = list.count();
    int letterHeight = height() / (count - 2);

    //找到对应的索引高亮显示,发出信号通知
    int letterIndex = letterY / letterHeight;
    setHighLetter(list.at(letterIndex + 1));
    emit letterClicked(highLetter, letterIndex * letterHeight);
}

QString TelLetter::getLetters() const
{
    return this->letters;
}

QString TelLetter::getHighLetter() const
{
    return this->highLetter;
}

QColor TelLetter::getNormalColor() const
{
    return this->normalColor;
}

QColor TelLetter::getHighColor() const
{
    return this->highColor;
}

void TelLetter::setLetters(const QString &letters)
{
    if (this->letters != letters) {
        this->letters = letters;
        update();
    }
}

void TelLetter::setHighLetter(const QString &highLetter)
{
    if (this->highLetter != highLetter) {
        this->highLetter = highLetter;
        update();
    }
}

void TelLetter::setNormalColor(const QColor &normalColor)
{
    if (this->normalColor != normalColor) {
        this->normalColor = normalColor;
        update();
    }
}

void TelLetter::setHighColor(const QColor &highColor)
{
    if (this->highColor != highColor) {
        this->highColor = highColor;
        update();
    }
}


TelButton::TelButton(QWidget *parent) : QWidget(parent)
{
    pixVisible = true;
    padding = 30;
    space = 10;

    pixmap = QPixmap(":/image/tel.png");
    name = "张三";
    type = "公司";
    tel = "13888888888";

    bgColor = QColor(0, 0, 0, 30);
    nameColor = QColor(0, 0, 0);
    typeColor = QColor(100, 100, 100);

    pressed = false;
}

void TelButton::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    emit btnPressed();
    pressed = true;
    update();
    QWidget::mousePressEvent(event);
}

void TelButton::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标按下与松开同一个位置才算
    if (lastPos == event->pos()) {
        emit btnRelease();
    }

    pressed = false;
    update();
    QWidget::mouseReleaseEvent(event);
}

void TelButton::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void TelButton::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int pixSize = qMin(width, height) / 1.5;

    //设置平滑绘制
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    //painter.drawRect(this->rect());

    //如果鼠标按下则绘制背景
    if (pressed) {
        painter.setPen(bgColor);
        painter.setBrush(bgColor);
        painter.drawRect(this->rect());
    }

    //绘制左侧小图标
    QRect rectPix(padding, height / 2 - pixSize / 2, pixSize, pixSize);
    if (pixVisible) {
        QPixmap pix = pixmap.scaled(pixSize, pixSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(rectPix.x(), rectPix.y(), pix);
    }

    //绘制姓名
    QPoint p = rectPix.topRight();
    QRect rectName(p.x() + space, 0, width - p.x() - space, height / 1.5);
    painter.setPen(nameColor);
    painter.drawText(rectName, Qt::AlignLeft | Qt::AlignVCenter, name);

    //绘制类型,需要重新设置字体,更小
    QFont font;
    font.setPixelSize(font.pixelSize() - 2);
    painter.setFont(font);
    QRect rectType(p.x() + space, height / 2, width - p.x() - space, height / 2);
    painter.setPen(typeColor);
    painter.drawText(rectType, Qt::AlignLeft | Qt::AlignTop, type);
}

bool TelButton::getPixVisible() const
{
    return this->pixVisible;
}

int TelButton::getPadding() const
{
    return this->padding;
}

int TelButton::getSpace() const
{
    return this->space;
}

QPixmap TelButton::getPixmap() const
{
    return this->pixmap;
}

QString TelButton::getName() const
{
    return this->name;
}

QString TelButton::getType() const
{
    return this->type;
}

QString TelButton::getTel() const
{
    return this->tel;
}

QColor TelButton::getBgColor() const
{
    return this->bgColor;
}

QColor TelButton::getNameColor() const
{
    return this->nameColor;
}

QColor TelButton::getTypeColor() const
{
    return this->typeColor;
}

QSize TelButton::sizeHint() const
{
    return QSize(60, 40);
}

QSize TelButton::minimumSizeHint() const
{
    return QSize(50, 40);
}

void TelButton::setPixVisible(bool pixVisible)
{
    if (this->pixVisible != pixVisible) {
        this->pixVisible = pixVisible;
        update();
    }
}

void TelButton::setPadding(int padding)
{
    if (this->padding != padding) {
        this->padding = padding;
        update();
    }
}

void TelButton::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void TelButton::setPixmap(const QPixmap &pixmap)
{
    this->pixmap = pixmap;
    update();
}

void TelButton::setName(const QString &name)
{
    if (this->name != name) {
        this->name = name;
        update();
    }
}

void TelButton::setType(const QString &type)
{
    if (this->type != type) {
        this->type = type;
        update();
    }
}

void TelButton::setTel(const QString &tel)
{
    if (this->tel != tel) {
        this->tel = tel;
        update();
    }
}

void TelButton::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void TelButton::setNameColor(const QColor &nameColor)
{
    if (this->nameColor != nameColor) {
        this->nameColor = nameColor;
        update();
    }
}

void TelButton::setTypeColor(const QColor &typeColor)
{
    if (this->typeColor != typeColor) {
        this->typeColor = typeColor;
        update();
    }
}

ScrollBar::ScrollBar(QWidget *parent) : QScrollBar(parent)
{
}

int ScrollBar::getSliderHeight()
{
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect rect = style()->subControlRect(QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSlider, this);
    return rect.height();
}


TelPanel::TelPanel(QWidget *parent) : QWidget(parent)
{
    this->initControl();
    this->initForm();
    this->initBar();
}

bool TelPanel::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == widget) {
        if (event->type() == QEvent::Resize) {
            this->initBar();
        }
    }

    return QWidget::eventFilter(watched, event);
}

void TelPanel::resizeEvent(QResizeEvent *)
{
    scrollArea->resize(size());

    //根据宽度比例调整滚动条占的区域
    int width = this->width();
    int height = this->height();
    int scrollWidth = 10;
    int offset = 3;
    scrollBar->setGeometry(width - scrollWidth - offset, offset, scrollWidth, height - offset * 2);
}

void TelPanel::enterEvent(QEvent *)
{
    //scrollBar->show();
}

void TelPanel::leaveEvent(QEvent *)
{
    //scrollBar->hide();
}

void TelPanel::mousePressEvent(QMouseEvent *event)
{
    pressed = true;
    pressedPos = event->pos();
    pressedY = event->pos().y();
    pressedTime = QDateTime::currentDateTime();
    scrollBar->show();
    animation->stop();
}

void TelPanel::mouseReleaseEvent(QMouseEvent *event)
{
    pressed = false;

    //说明是单击按钮
    if (pressedPos == event->pos()) {
        return;
    }

    //判断当前时间和鼠标按下事件比较,时间短则说明是滑动
    QDateTime now = QDateTime::currentDateTime();
    if (pressedTime.msecsTo(now) > 600) {
        return;
    }

    //可以改变下面的值来调整幅度
    int offset = movetop ? step : -step;
    int value = scrollArea->verticalScrollBar()->value();
    animation->setStartValue(value);
    animation->setEndValue(value + offset);
    animation->start();
    timer->start(800);
}

void TelPanel::mouseMoveEvent(QMouseEvent *event)
{
    int currentY = event->pos().y();
    int offset = pressedY - currentY;
    int scal = offset * 2;
    movetop = (offset > 0);

    //如果滚动条已经在顶部且当前下滑或者在底部且当前上滑则无需滚动
    int value = scrollArea->verticalScrollBar()->value();
    int height = scrollArea->verticalScrollBar()->height();
    if ((value == 0 && !movetop) || ((value + height) == widget->height() && movetop)) {
        return;
    }

    if (pressedY != currentY) {
        //模拟鼠标滚轮
        QWheelEvent wheelEvent(QPoint(0, 0), -scal, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(widget, &wheelEvent);
        pressedY = currentY;
    }
}

void TelPanel::initControl()
{
    //滚动条区域
    scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("TelPanel_ScrollArea");
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea#TelPanel_ScrollArea{border:none;background:transparent;}");

    //替换垂直滚动条,以便获取滚动条手柄的高度
    ScrollBar *bar = new ScrollBar;
    scrollArea->setVerticalScrollBar(bar);

    //设置滚动条不显示,用自定义的滚动条
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //滚动条
    scrollBar = new QScrollBar(Qt::Vertical, this);
    scrollBar->setVisible(false);
    connect(scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), scrollBar, SLOT(setValue(int)));
    connect(scrollBar, SIGNAL(valueChanged(int)), scrollArea->verticalScrollBar(), SLOT(setValue(int)));
    connect(scrollArea->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(setRange(int, int)));
    connect(scrollBar, SIGNAL(valueChanged(int)), this, SIGNAL(positionChanged(int)));

    //元素载体窗体
    widget = new QWidget(scrollArea);
    widget->installEventFilter(this);
    widget->setObjectName("TelPanel_Widget");
    widget->setGeometry(QRect(0, 0, 100, 100));
    widget->setStyleSheet("QWidget#TelPanel_Widget{background:transparent;}");
    scrollArea->setWidget(widget);

    //表格布局
    gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
}

void TelPanel::initForm()
{
    step = 1200;
    margin = 0;
    space = 0;
    autoWidth = false;
    autoHeight = false;
    columnCount = 1;

    normalColor = QColor(0, 0, 0, 35);
    highColor = QColor(0, 0, 0, 75);

    pressed = false;

    //定义动画产生平滑数值
    animation = new QPropertyAnimation(scrollArea->verticalScrollBar(), "value");
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->setDuration(500);

    //启动定时器隐藏滚动条
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkBar()));
}

void TelPanel::initBar()
{
    //获取到原有滚动条手柄的高度,重新设置新的滚动条的手柄高度
    ScrollBar *bar = (ScrollBar *) scrollArea->verticalScrollBar();
    //原有高度可能太小,在此基础上加点
    int sliderHeight = bar->getSliderHeight() + 50;
    sliderHeight = sliderHeight > this->height() ? this->height() : sliderHeight;

    //滚动条样式
    QStringList list;
    list.append(QString("QScrollBar:vertical{background:transparent;padding:0px;}"));
    list.append(QString("QScrollBar::handle:vertical{min-height:%1px;}").arg(sliderHeight));
    list.append(QString("QScrollBar::handle:vertical{background:rgba(%1,%2,%3,%4);border-radius:5px;}")
                .arg(normalColor.red()).arg(normalColor.green()).arg(normalColor.blue()).arg(normalColor.alpha()));
    list.append(QString("QScrollBar::handle:vertical:hover,QScrollBar::handle:vertical:pressed{background:rgba(%1,%2,%3,%4);}")
                .arg(highColor.red()).arg(highColor.green()).arg(highColor.blue()).arg(highColor.alpha()));
    list.append(QString("QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:none;}"));
    list.append(QString("QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{background:none;}"));
    scrollBar->setStyleSheet(list.join(""));
}

void TelPanel::checkBar()
{
    //如果当前为按下则不需要隐藏
    if (pressed) {
        return;
    }

    scrollBar->hide();
    timer->stop();
}

void TelPanel::setRange(int min, int max)
{
    scrollBar->setRange(min, max);
}

int TelPanel::getStep() const
{
    return this->step;
}

int TelPanel::getMargin() const
{
    return this->margin;
}

int TelPanel::getSpace() const
{
    return this->space;
}

bool TelPanel::getAutoWidth() const
{
    return this->autoWidth;
}

bool TelPanel::getAutoHeight() const
{
    return this->autoHeight;
}

QColor TelPanel::getNormalColor() const
{
    return this->normalColor;
}

QColor TelPanel::getHighColor() const
{
    return this->highColor;
}

int TelPanel::getPosition() const
{
    return scrollBar->value();
}

int TelPanel::getColumnCount() const
{
    return this->columnCount;
}

QList<QWidget *> TelPanel::getItems() const
{
    return this->items;
}

QList<int> TelPanel::getIndexs() const
{
    return this->indexs;
}

QList<QWidget *> TelPanel::getBanners() const
{
    return this->banners;
}

void TelPanel::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
    }
}

void TelPanel::setMargin(int left, int top, int right, int bottom)
{
    gridLayout->setContentsMargins(left, top, right, bottom);
}

void TelPanel::setMargin(int margin)
{
    if (this->margin != margin) {
        setMargin(margin, margin, margin, margin);
    }
}

void TelPanel::setSpace(int space)
{
    if (this->space != space) {
        gridLayout->setSpacing(space);
    }
}

void TelPanel::setAutoWidth(bool autoWidth)
{
    if (this->autoWidth != autoWidth) {
        this->autoWidth = autoWidth;
    }
}

void TelPanel::setAutoHeight(bool autoHeight)
{
    if (this->autoHeight != autoHeight) {
        this->autoHeight = autoHeight;
    }
}

void TelPanel::setPosition(int value)
{
    scrollBar->setValue(value);
}

void TelPanel::setNormalColor(const QColor &normalColor)
{
    if (this->normalColor != normalColor) {
        this->normalColor = normalColor;
        this->initBar();
    }
}

void TelPanel::setHighColor(const QColor &highColor)
{
    if (this->highColor != highColor) {
        this->highColor = highColor;
        this->initBar();
    }
}

void TelPanel::setIndexs(const QList<int> indexs)
{
    if (this->indexs != indexs) {
        this->indexs = indexs;
    }
}

void TelPanel::setBanners(QList<QWidget *> banners)
{
    this->banners = banners;
}

void TelPanel::setColumnCount(int columnCount)
{
    if (this->columnCount != columnCount) {
        this->columnCount = columnCount;
    }
}

void TelPanel::setItems(QList<QWidget *> items)
{
    this->items = items;

    int row = 0;
    int column = 0;
    int count = 0;
    int temp = 0;

    //单独添加第一行标识符
    if (indexs.count() > 0 && indexs.first() == 0) {
        gridLayout->addWidget(banners.first(), row, column, 1, columnCount);
        row++;
    }

    foreach (QWidget *item, items) {
        //逐行添加元素到表格布局
        gridLayout->addWidget(item, row, column);
        column++;
        count++;
        temp++;

        //强制插入分割控件,另起一行
        int index = indexs.indexOf(count);
        if (index >= 0) {
            row++;
            column = 0;
            gridLayout->addWidget(banners.at(index), row, column, 1, columnCount);

            //奇数偶数增加的数量不一样
            if (temp % columnCount == 0) {
                temp += columnCount;
            } else {
                temp += 1;
            }

            row++;
        }

        //如果到了列数则换行
        if (temp % columnCount == 0) {
            row++;
            column = 0;
        }
    }

    row++;

    //设置右边弹簧
    if (!autoWidth) {
        QSpacerItem *hSpacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
        gridLayout->addItem(hSpacer, 0, gridLayout->columnCount());
    }

    //设置底边弹簧
    if (!autoHeight) {
        QSpacerItem *vSpacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
        gridLayout->addItem(vSpacer, row, 0);
    }
}

QSize TelPanel::sizeHint() const
{
    return QSize(300, 200);
}

QSize TelPanel::minimumSizeHint() const
{
    return QSize(20, 20);
}


TelWidget::TelWidget(QWidget *parent) : QWidget(parent)
{
    this->initControl();
    this->initForm();
}

TelWidget::~TelWidget()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void TelWidget::resizeEvent(QResizeEvent *)
{
    showEvent(NULL);
}

void TelWidget::showEvent(QShowEvent *)
{
    int width = 18;
    int x = telPanel->width() - width * 2;
    int y = 0;
    int height = telPanel->height();
    telLetter->setGeometry(x, y, width, height);

    //设置中间字母导航间隔标签位置
    telBanner->resize(telPanel->width(), 30);
}

void TelWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //优先绘制背景图片
    if (!bgImage.isNull()) {
        QPixmap pix = bgImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, pix);
    } else {
        painter.setPen(Qt::NoPen);
        painter.setBrush(bgColor);
        painter.drawRect(this->rect());
    }
}

void TelWidget::initControl()
{
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName("verticalLayout");
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    telPanel = new TelPanel;
    telPanel->setObjectName("telPanel");
    verticalLayout->addWidget(telPanel);

    //设置面板的元素间距
    telPanel->setMargin(0, 0, 0, 0);
    //设置是否自动拉伸元素的宽度
    telPanel->setAutoWidth(true);
    //设置列数
    telPanel->setColumnCount(2);

    //突出显示字母
    telHigh = new TelHigh(telPanel);
    telHigh->setVisible(false);

    //顶部间隔字母导航
    telBanner = new TelBanner(telPanel);
    telBanner->setVisible(false);

    //右侧字母列表
    telLetter = new TelLetter(telPanel);
    connect(telLetter, SIGNAL(letterClicked(QString, int)), this, SLOT(letterClicked(QString, int)));

    //绑定面板滑动位置改变信号槽,计算当前字母
    connect(telPanel, SIGNAL(positionChanged(int)), this, SLOT(positionChanged(int)));

    //定时器隐藏突出显示字母
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), telHigh, SLOT(hide()));
    timer->setInterval(1000);
}

void TelWidget::initForm()
{
    bgImage = QPixmap();
    bgColor = Qt::transparent;

    telHighFontSize = telHigh->getFontSize();
    telHighBgImage = telHigh->getBgImage();
    telHighBgColor = telHigh->getBgColor();
    telHighTextColor = telHigh->getTextColor();

    telBannerBgColor = telBanner->getBgColor();
    telBannerTextColor = telBanner->getTextColor();
    telBannerLineColor = telBanner->getLineColor();

    telLetterNormalColor = telLetter->getNormalColor();
    telLetterHighColor = telLetter->getHighColor();

    telButtonBgColor = QColor(0, 0, 0, 30);
    telButtonNameColor = QColor(0, 0, 0);
    telButtonTypeColor = QColor(100, 100, 100);

    telPanelNormalColor = telPanel->getNormalColor();
    telPanelHighColor = telPanel->getHighColor();
}

void TelWidget::btnPressed()
{
    //记录下滚动条位置,过滤鼠标松开地方
    lastPosition = telPanel->getPosition();
}

void TelWidget::btnRelease()
{
    //如果鼠标按下时候和松开时候的滚动条位置一致则说明是单击
    int position = telPanel->getPosition();
    if (lastPosition == position) {
        TelButton *btn = (TelButton *)sender();
        emit telClicked(btn->getName(), btn->getType(), btn->getTel());
    }
}

void TelWidget::positionChanged(int value)
{
    //找到当前位置的按钮的姓名的首字母
    for (int i = 0; i < items.count(); i++) {
        QWidget *item = items.at(i);
        QPoint p = item->pos();

        //相邻近似算法,当前滚动条的值需要加上按钮的高度,不然找到的是上一个
        int offset = qAbs(p.y() - (value + 20));
        if (offset < 5) {
            TelButton *btn = (TelButton *)item;
            QString letter = btn->property("letter").toString();
            telLetter->setHighLetter(letter);
            telBanner->setText(letter);
            break;
        }
    }
}

void TelWidget::letterClicked(const QString &letter, int letterY)
{
    //找到当前字母所在的第一行,滚动条滚过去
    for (int i = 0; i < items.count(); i++) {
        QWidget *w = items.at(i);
        QString str = w->property("letter").toString();
        if (str == letter) {
            //需要减去字母导航标签的高度
            telPanel->setPosition(w->pos().y() - 30);
            break;
        }
    }

    //根据不同的类型移动到不同的位置
    if (!telHigh->getBgImage().isNull()) {
        telHigh->resize(100, 55);
        telHigh->move(telPanel->width() - telHigh->width() - 12, letterY - 15);
    } else {
        telHigh->resize(55, 55);
        telHigh->move((telPanel->width() - telHigh->width()) / 2, (telPanel->height() - telHigh->height()) / 2);
    }

    telHigh->setText(letter);
    telHigh->show();
    timer->stop();
    timer->start();
}

QString TelWidget::getNames() const
{
    return this->names;
}

QString TelWidget::getTypes() const
{
    return this->types;
}

QString TelWidget::getTels() const
{
    return this->tels;
}

QPixmap TelWidget::getBgImage() const
{
    return this->bgImage;
}

QColor TelWidget::getBgColor() const
{
    return this->bgColor;
}

int TelWidget::getTelHighFontSize() const
{
    return this->telHighFontSize;
}

QPixmap TelWidget::getTelHighBgImage() const
{
    return this->telHighBgImage;
}

QColor TelWidget::getTelHighBgColor() const
{
    return this->telHighBgColor;
}

QColor TelWidget::getTelHighTextColor() const
{
    return this->telHighTextColor;
}

QColor TelWidget::getTelBannerBgColor() const
{
    return this->telBannerBgColor;
}

QColor TelWidget::getTelBannerTextColor() const
{
    return this->telBannerTextColor;
}

QColor TelWidget::getTelBannerLineColor() const
{
    return this->telBannerLineColor;
}

QColor TelWidget::getTelLetterNormalColor() const
{
    return this->telLetterNormalColor;
}

QColor TelWidget::getTelLetterHighColor() const
{
    return this->telLetterHighColor;
}

QColor TelWidget::getTelButtonBgColor() const
{
    return this->telButtonBgColor;
}

QColor TelWidget::getTelButtonNameColor() const
{
    return this->telButtonNameColor;
}

QColor TelWidget::getTelButtonTypeColor() const
{
    return this->telButtonTypeColor;
}

QColor TelWidget::getTelPanelNormalColor() const
{
    return this->telPanelNormalColor;
}

QColor TelWidget::getTelPanelHighColor() const
{
    return this->telPanelHighColor;
}

QSize TelWidget::sizeHint() const
{
    return QSize(300, 500);
}

QSize TelWidget::minimumSizeHint() const
{
    return QSize(50, 150);
}

void TelWidget::setNames(const QString &names)
{
    if (this->names != names) {
        setInfo(names, types, tels);
    }
}

void TelWidget::setTypes(const QString &types)
{
    if (this->types != types) {
        setInfo(names, types, tels);
    }
}

void TelWidget::setTels(const QString &tels)
{
    if (this->tels != tels) {
        setInfo(names, types, tels);
    }
}

void TelWidget::setInfo(const QString &names, const QString &types, const QString &tels)
{
    setInfo(names.split("|"), types.split("|"), tels.split("|"), QList<QPixmap>());
}

void TelWidget::setInfo(const QStringList &names, const QStringList &types,
                        const QStringList &tels, const QList<QPixmap> &pixmaps)
{
    this->names = names.join("|");
    this->types = types.join("|");
    this->tels = tels.join("|");
    this->pixmaps = pixmaps;

    if (names.isEmpty() || types.isEmpty() || tels.isEmpty()) {
        return;
    }

    //行标识符文字集合
    QList<QString> texts;
    texts << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "H" << "I" << "J" << "K" << "L" << "M"
          << "N" << "O" << "P" << "Q" << "R" << "S" << "T" << "U" << "V" << "W" << "X" << "Y" << "Z" << "#";

    QList<QString> listName = names;
    QList<QString> listType = types;
    QList<QString> listTel = tels;
    QList<QPixmap> listPix = pixmaps;
    int countName = listName.count();
    int countType = listType.count();
    int countTel = listTel.count();
    int countPix = listPix.count();

    if (countName == countType && countType == countTel && countTel == countPix) {
        //取出对应汉字首字母,先对所有姓名按照字母从小到大排序
        QList<TelInfo> poundInfos, telInfos;
        for (int i = 0; i < countName; i++) {
            TelInfo telInfo;
            telInfo.name = listName.at(i);
            telInfo.type = listType.at(i);
            telInfo.tel = listTel.at(i);
            telInfo.pixmap = listPix.at(i);

            //如果首字母未找到字母则归结到 # 分类中
            QString letter = ZhToPY::Instance()->zhToZM(listName.at(i).at(0));
            if (texts.contains(letter)) {
                telInfo.letter = ZhToPY::Instance()->zhToJP(listName.at(i));
                telInfos << telInfo;
            } else {
                telInfo.letter = "#";
                poundInfos << telInfo;
            }
        }

        //对信息集合进行升序排序
        qSort(telInfos.begin(), telInfos.end());

        //对最后的 # 类别追加到末尾
        foreach (TelInfo telInfo, poundInfos) {
            telInfos << telInfo;
        }

        //先要清空所有元素
        qDeleteAll(items);
        qDeleteAll(banners);
        items.clear();
        banners.clear();

        //生成电话本按钮
        for (int i = 0; i < countName; i++) {
            TelInfo telInfo = telInfos.at(i);
            TelButton *btn = new TelButton;
            connect(btn, SIGNAL(btnPressed()), this, SLOT(btnPressed()));
            connect(btn, SIGNAL(btnRelease()), this, SLOT(btnRelease()));

            //设置字母属性
            QString letter = telInfo.letter.at(0);
            btn->setProperty("letter", letter);

            //设置头像+姓名+类型+电话
            btn->setPixmap(telInfo.pixmap);
            btn->setName(telInfo.name);
            btn->setType(telInfo.type);
            btn->setTel(telInfo.tel);
            items << btn;
        }

        //逐个计算字母对应的索引
        QList<int> tempIndex;
        int textCount = texts.count();
        for (int j = 0; j < textCount; j++) {
            QString text = texts.at(j);
            int index = -1;
            for (int k = 0; k < items.count(); k++) {
                if (items.at(k)->property("letter").toString() == text) {
                    index = k;
                    break;
                }
            }

            tempIndex << index;
        }

        //过滤索引,标识符索引>=0才算数
        QList<int> indexs;
        for (int j = 0; j < textCount; j++) {
            int index = tempIndex.at(j);
            if (index >= 0) {
                TelBanner *banner = new TelBanner;
                banner->setText(texts.at(j));
                banners << banner;
                indexs << index;
            }
        }

        //设置标识符+元素集合
        telPanel->setIndexs(indexs);
        telPanel->setBanners(banners);
        telPanel->setItems(items);

        //重新设置颜色
        setTelHighBgColor(telHighBgColor);
        setTelBannerBgColor(telBannerBgColor);
        setTelBannerTextColor(telBannerTextColor);
        setTelLetterNormalColor(telLetterNormalColor);
        setTelLetterHighColor(telLetterHighColor);
        setTelButtonNameColor(telButtonNameColor);
        setTelButtonTypeColor(telButtonTypeColor);
        setTelPanelNormalColor(telPanelNormalColor);
        setTelPanelHighColor(telPanelHighColor);
    }
}

void TelWidget::addInfo(const QString &name, const QString &type,
                        const QString &tel, const QPixmap &pixmap)
{
    names = names + "|" + name;
    types = types + "|" + type;
    tels = tels + "|" + tel;
    pixmaps.append(pixmap);
    setInfo(names.split("|"), types.split("|"), tels.split("|"), pixmaps);
}

void TelWidget::setBgImage(const QPixmap &bgImage)
{
    this->bgImage = bgImage;
    update();
}

void TelWidget::setBgColor(const QColor &bgColor)
{
    this->bgColor = bgColor;
    update();
}

void TelWidget::setTelHighFontSize(int telHighFontSize)
{
    this->telHighFontSize = telHighFontSize;
    telHigh->setFontSize(telHighFontSize);
}

void TelWidget::setTelHighBgImage(const QPixmap &telHighBgImage)
{
    this->telHighBgImage = telHighBgImage;
    telHigh->setBgImage(telHighBgImage);
}

void TelWidget::setTelHighBgColor(const QColor &telHighBgColor)
{
    this->telHighBgColor = telHighBgColor;
    telHigh->setBgColor(telHighBgColor);
}

void TelWidget::setTelHighTextColor(const QColor &telHighTextColor)
{
    this->telHighTextColor = telHighTextColor;
    telHigh->setTextColor(telHighTextColor);
}

void TelWidget::setTelBannerBgColor(const QColor &telBannerBgColor)
{
    this->telBannerBgColor = telBannerBgColor;
    telBanner->setBgColor(telBannerBgColor);
    foreach (QWidget *banner, banners) {
        TelBanner *b = (TelBanner *)banner;
        b->setBgColor(telBannerBgColor);
    }
}

void TelWidget::setTelBannerTextColor(const QColor &telBannerTextColor)
{
    this->telBannerTextColor = telBannerTextColor;
    telBanner->setTextColor(telBannerTextColor);
    foreach (QWidget *banner, banners) {
        TelBanner *b = (TelBanner *)banner;
        b->setTextColor(telBannerTextColor);
    }
}

void TelWidget::setTelBannerLineColor(const QColor &telBannerLineColor)
{
    this->telBannerLineColor = telBannerLineColor;
    telBanner->setLineColor(telBannerLineColor);
    foreach (QWidget *banner, banners) {
        TelBanner *b = (TelBanner *)banner;
        b->setLineColor(telBannerLineColor);
    }
}

void TelWidget::setTelLetterNormalColor(const QColor &telLetterNormalColor)
{
    this->telLetterNormalColor = telLetterNormalColor;
    telLetter->setNormalColor(telLetterNormalColor);
}

void TelWidget::setTelLetterHighColor(const QColor &telLetterHighColor)
{
    this->telLetterHighColor = telLetterHighColor;
    telLetter->setHighColor(telLetterHighColor);
}

void TelWidget::setTelButtonBgColor(const QColor &telButtonBgColor)
{
    this->telButtonBgColor = telButtonBgColor;
    foreach (QWidget *item, items) {
        TelButton *btn = (TelButton *)item;
        btn->setBgColor(telButtonBgColor);
    }
}

void TelWidget::setTelButtonNameColor(const QColor &telButtonNameColor)
{
    this->telButtonNameColor = telButtonNameColor;
    foreach (QWidget *item, items) {
        TelButton *btn = (TelButton *)item;
        btn->setNameColor(telButtonNameColor);
    }
}

void TelWidget::setTelButtonTypeColor(const QColor &telButtonTypeColor)
{
    this->telButtonTypeColor = telButtonTypeColor;
    foreach (QWidget *item, items) {
        TelButton *btn = (TelButton *)item;
        btn->setTypeColor(telButtonTypeColor);
    }
}

void TelWidget::setTelPanelNormalColor(const QColor &telPanelNormalColor)
{
    this->telPanelNormalColor = telPanelNormalColor;
    telPanel->setNormalColor(telPanelNormalColor);
}

void TelWidget::setTelPanelHighColor(const QColor &telPanelHighColor)
{
    this->telPanelHighColor = telPanelHighColor;
    telPanel->setHighColor(telPanelHighColor);
}
