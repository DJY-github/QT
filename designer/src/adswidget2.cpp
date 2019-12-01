#pragma execution_character_set("utf-8")

#include "adswidget2.h"
#include "qpainter.h"
#include "qevent.h"
#include "qlabel.h"
#include "qlayout.h"
#include "qpropertyanimation.h"
#include "qsequentialanimationgroup.h"
#include "qparallelanimationgroup.h"
#include "qtimer.h"
#include "qdebug.h"

AdsWidget2::AdsWidget2(QWidget *parent) : QWidget(parent)
{
    this->initWidget();
    this->initForm();
    this->initQss();
}

AdsWidget2::~AdsWidget2()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

bool AdsWidget2::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj->inherits("QLabel")) {
            //先停止定时器,防止按下切换的时候短时间内再度切换
            timer->stop();
            changedAds((QLabel *)obj);
            timer->start(interval);
        }
    }

    return QWidget::eventFilter(obj, event);
}

void AdsWidget2::enterEvent(QEvent *)
{
    if (hoverStop) {
        timer->stop();
    }
}

void AdsWidget2::leaveEvent(QEvent *)
{
    if (hoverStop) {
        timer->start();
    }
}

void AdsWidget2::showEvent(QShowEvent *)
{
    //立即设置当前指示器
    if (names.count() > 0) {
        animationImage->setStartValue(0);
        animationImage->setEndValue(width());
        animationMax->setStartValue(maxWidth);
        animationMax->setEndValue(minWidth);
        animationMin->setStartValue(minWidth);
        animationMin->setEndValue(maxWidth);
        animationGroup->start();
        changedAds(labs.at(0));
    }

    if (!timer->isActive()) {
        timer->start();
    }
}

void AdsWidget2::paintEvent(QPaintEvent *)
{
    if (names.count() == 0) {
        return;
    }

    int width = this->width();
    int height = this->height();

    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    painter.setPen(tipColor);

    //设置字体
    QFont font;
    font.setPixelSize(15);
    painter.setFont(font);

    //取出上一张图片+当前图片,并平滑缩放
    QPixmap previousPix(names.at(previousIndex));
    QPixmap currentPix(names.at(currentIndex));
    previousPix = previousPix.scaled(width, height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    currentPix = currentPix.scaled(width, height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    int widthOffset = offset + width;
    if (leftToRight) {
        widthOffset = offset - width;
    }

    //绘制上一张图片
    painter.drawPixmap(offset, 0, previousPix);
    //绘制当前图片
    painter.drawPixmap(widthOffset, 0, currentPix);

    //绘制上一张图片提示信息,有可能上一张图片提示信息为空
    if (previousIndex <= tips.count() - 1) {
        painter.drawText(QRect(offset + 10, height - minHeight - 40, width - 20, 30), tips.at(previousIndex), option);
    }

    //绘制当前图片提示信息,有可能当前图片提示信息为空
    if (currentIndex <= tips.count() - 1) {
        painter.drawText(QRect(widthOffset + 10, height - minHeight - 40, width - 20, 30), tips.at(currentIndex), option);
    }
}

void AdsWidget2::initWidget()
{
    //放置指示器的窗体载体
    widgetNav = new QWidget(this);
    widgetNav->setObjectName(QString::fromUtf8("widgetNav"));

    //给指示器窗体加上左右布局
    layout = new QHBoxLayout(widgetNav);
    layout->setSpacing(3);

    //主布局,上下布局
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    //上部弹簧,用于将指示器区域弹到底部
    QSpacerItem *verticalSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacer);

    //将指示器窗体加入到主布局中下部
    verticalLayout->addWidget(widgetNav);

    //实例化左侧右侧弹簧
    spacerLeft = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    spacerRight = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void AdsWidget2::initForm()
{
    hoverStop = true;
    showNumber = false;

    minHeight = 6;
    minWidth = 6;
    maxWidth = 25;
    interval = 3000;
    navRadius = 3;

    navColor = QColor(220, 220, 220);
    textColor = QColor(20, 20, 20);
    tipColor = QColor(255, 255, 255);
    darkColor = QColor(255, 255, 255);

    imageNames.clear();
    imageTips.clear();

    navPosition = NavPosition_Left;
    navStyle = NavStyle_Ellipse;

    leftToRight = true;
    offset = 0;
    currentIndex = 0;
    previousIndex = 0;

    //定时器切换图片
    timer = new QTimer(this);
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(changedAds()));

    this->setMouseTracking(true);

    //定义动画组
    animationGroup = new QParallelAnimationGroup(this);

    //定义动画切换图片
    animationImage = new QPropertyAnimation(this, "");
    connect(animationImage, SIGNAL(valueChanged(const QVariant &)), this, SLOT(changedImage(const QVariant &)));
    animationImage->setEasingCurve(QEasingCurve::OutCirc);
    animationImage->setDuration(1000);
    animationGroup->addAnimation(animationImage);

    QSequentialAnimationGroup *sequentialGroup = new QSequentialAnimationGroup(animationGroup);

    //用于切换最小拉伸宽度
    animationMin = new QPropertyAnimation(sequentialGroup, "");
    connect(animationMin, SIGNAL(valueChanged(const QVariant &)), this, SLOT(changedMin(const QVariant &)));
    animationMin->setEasingCurve(QEasingCurve::OutCubic);
    animationMin->setDuration(500);

    //用于切换最大拉伸宽度
    animationMax = new QPropertyAnimation(sequentialGroup, "");
    connect(animationMax, SIGNAL(valueChanged(const QVariant &)), this, SLOT(changedMax(const QVariant &)));
    animationMax->setEasingCurve(QEasingCurve::OutCubic);
    animationMax->setDuration(500);

    //按钮切换串行运行
    sequentialGroup->addAnimation(animationMin);
    sequentialGroup->addAnimation(animationMax);
    animationGroup->addAnimation(sequentialGroup);
}

void AdsWidget2::initQss()
{
    //可自行拓展自定义样式
    if (navStyle == NavStyle_Dot) {
        qssNormal = QString("border:none;background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,"
                            "stop:0 #00FFFFFF,stop:0.4 #00FFFFFF,"
                            "stop:0.5 #00FFFFFF,stop:0.6 #00FFFFFF,stop:0.7 rgba(%1,%2,%3,%4));"
                            "color:rgba(%5,%6,%7,%8);border-radius:%9px;")
                    .arg(navColor.red()).arg(navColor.green()).arg(navColor.blue()).arg(navColor.alpha())
                    .arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()).arg(navColor.alpha()).arg(navRadius);
        qssCurrent = QString("border:none;background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,"
                             "stop:0 rgba(%1,%2,%3,%4),stop:0.4 rgba(%1,%2,%3,%4),"
                             "stop:0.5 #00FFFFFF,stop:0.6 #00FFFFFF,stop:0.7 rgba(%1,%2,%3,%4));"
                             "color:rgba(%5,%6,%7,%8);border-radius:%9px;")
                     .arg(darkColor.red()).arg(darkColor.green()).arg(darkColor.blue()).arg(darkColor.alpha())
                     .arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()).arg(navColor.alpha()).arg(navRadius);

    } else {
        qssNormal = QString("border:none;background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);border-radius:%9px;")
                    .arg(navColor.red()).arg(navColor.green()).arg(navColor.blue()).arg(navColor.alpha())
                    .arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()).arg(navColor.alpha()).arg(navRadius);
        qssCurrent = QString("border:none;background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);border-radius:%9px;")
                     .arg(darkColor.red()).arg(darkColor.green()).arg(darkColor.blue()).arg(darkColor.alpha())
                     .arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()).arg(textColor.alpha()).arg(navRadius);
    }
}

void AdsWidget2::changedAds()
{
    if (names.count() == 0) {
        return;
    }

    previousIndex = currentIndex;
    if (currentIndex < names.count() - 1) {
        currentIndex++;
    } else {
        currentIndex = 0;
    }

    changedAds(labs.at(currentIndex));
}

void AdsWidget2::changedAds(QLabel *lab)
{
    int index = labs.indexOf(lab);

    //如果索引负数则取最后一张
    if (index < 0) {
        index = names.count() - 1;
    }

    //如果索引到了最大张数则取第一张
    if (index >= names.count()) {
        index = 0;
    }

    currentIndex = index;

    //图片切换,计算当前是否左滑右滑
    if (previousIndex < currentIndex) {
        animationImage->setStartValue(0);
        animationImage->setEndValue(0 - width());
        leftToRight = false;
    } else {
        animationImage->setStartValue(0);
        animationImage->setEndValue(width());
        leftToRight = true;
    }

    animationGroup->start();

    //将当前指示器突出显示
    foreach (QLabel *currentLab, labs) {
        if (currentLab == lab) {
            currentLab->setStyleSheet(qssCurrent);
        } else {
            currentLab->setStyleSheet(qssNormal);
        }
    }
}

void AdsWidget2::changedImage(const QVariant &variant)
{
    offset = variant.toInt();
    update();
}

void AdsWidget2::changedMin(const QVariant &variant)
{
    labs.at(currentIndex)->setFixedWidth(variant.toInt());
}

void AdsWidget2::changedMax(const QVariant &variant)
{
    //设置按钮最大宽度,产生动态拉伸效果
    for (int i = 0; i < names.count(); i++) {
        if (currentIndex != i && labs.at(i)->width() > minWidth) {
            labs.at(i)->setFixedWidth(variant.toInt());
        }
    }
}

bool AdsWidget2::getHoverStop() const
{
    return this->hoverStop;
}

bool AdsWidget2::getShowNumber() const
{
    return this->showNumber;
}

int AdsWidget2::getMinHeight() const
{
    return this->minHeight;
}

int AdsWidget2::getMinWidth() const
{
    return this->minWidth;
}

int AdsWidget2::getMaxWidth() const
{
    return this->maxWidth;
}

int AdsWidget2::getInterval() const
{
    return this->interval;
}

int AdsWidget2::getNavRadius() const
{
    return this->navRadius;
}

QColor AdsWidget2::getNavColor() const
{
    return this->navColor;
}

QColor AdsWidget2::getTextColor() const
{
    return this->textColor;
}

QColor AdsWidget2::getTipColor() const
{
    return this->tipColor;
}

QColor AdsWidget2::getDarkColor() const
{
    return this->darkColor;
}

QString AdsWidget2::getImageNames() const
{
    return this->imageNames;
}

QString AdsWidget2::getImageTips() const
{
    return this->imageTips;
}

AdsWidget2::NavPosition AdsWidget2::getNavPosition() const
{
    return this->navPosition;
}

AdsWidget2::NavStyle AdsWidget2::getNavStyle() const
{
    return this->navStyle;
}

QSize AdsWidget2::sizeHint() const
{
    return QSize(200, 150);
}

QSize AdsWidget2::minimumSizeHint() const
{
    return QSize(20, 15);
}

void AdsWidget2::setHoverStop(bool hoverStop)
{
    if (this->hoverStop != hoverStop) {
        this->hoverStop = hoverStop;
        update();
    }
}

void AdsWidget2::setShowNumber(bool showNumber)
{
    if (this->showNumber != showNumber) {
        this->showNumber = showNumber;
        update();
    }
}

void AdsWidget2::setMinHeight(int minHeight)
{
    if (this->minHeight != minHeight) {
        this->minHeight = minHeight;
        update();
    }
}

void AdsWidget2::setMinWidth(int minWidth)
{
    if (this->minWidth != minWidth) {
        this->minWidth = minWidth;
        update();
    }
}

void AdsWidget2::setMaxWidth(int maxWidth)
{
    if (this->maxWidth != maxWidth) {
        this->maxWidth = maxWidth;
        update();
    }
}

void AdsWidget2::setInterval(int interval)
{
    if (this->interval != interval) {
        this->interval = interval;
        timer->setInterval(this->interval);
        update();
    }
}

void AdsWidget2::setNavRadius(int navRadius)
{
    if (this->navRadius != navRadius) {
        this->navRadius = navRadius;
        this->initQss();
        update();
    }
}

void AdsWidget2::setNavColor(const QColor &navColor)
{
    if (this->navColor != navColor) {
        this->navColor = navColor;
        this->initQss();
        update();
    }
}

void AdsWidget2::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->initQss();
        update();
    }
}

void AdsWidget2::setTipColor(const QColor &tipColor)
{
    if (this->tipColor != tipColor) {
        this->tipColor = tipColor;
        this->initQss();
        update();
    }
}

void AdsWidget2::setDarkColor(const QColor &darkColor)
{
    if (this->darkColor != darkColor) {
        this->darkColor = darkColor;
        this->initQss();
        update();
    }
}

void AdsWidget2::setImageNames(const QString &imageNames)
{
    if (this->imageNames != imageNames && !imageNames.isEmpty()) {
        this->imageNames = imageNames;
        names = this->imageNames.split(";");
        if (names.count() == 0) {
            return;
        }

        //先清空原有所有指示器
        qDeleteAll(labs);
        labs.clear();

        //将左右弹簧移除
        layout->removeItem(spacerLeft);
        layout->removeItem(spacerRight);

        //底部指示器左侧弹簧
        if (navPosition != NavPosition_Left) {
            layout->addItem(spacerLeft);
        }

        //根据图片链表自动生成导航指示器和图片链表
        for (int i = 0; i < names.count(); i++) {
            QLabel *lab = new QLabel;
            lab->setStyleSheet(qssNormal);
            widgetNav->layout()->addWidget(lab);
            lab->setFixedSize(minWidth, minHeight);

            if (showNumber) {
                lab->setAlignment(Qt::AlignCenter);
                lab->setText(QString::number(i + 1));
            }

            lab->installEventFilter(this);
            labs.append(lab);
        }

        //底部指示器右侧弹簧
        if (navPosition != NavPosition_Right) {
            layout->addItem(spacerRight);
        }
    }
}

void AdsWidget2::setImageTips(const QString &imageTips)
{
    if (this->imageTips != imageTips && !imageTips.isEmpty()) {
        this->imageTips = imageTips;
        tips = this->imageTips.split(";");
        update();
    }
}

void AdsWidget2::setNavPosition(const AdsWidget2::NavPosition &navPosition)
{
    if (this->navPosition != navPosition) {
        this->navPosition = navPosition;

        if (timer->isActive()) {
            timer->stop();
        }

        //重新设置图片集合
        if (names.count() > 0) {
            QString imageNames = this->imageNames;
            this->imageNames.clear();
            setImageNames(imageNames);
        }

        showEvent(NULL);
    }
}

void AdsWidget2::setNavStyle(const AdsWidget2::NavStyle &navStyle)
{
    if (this->navStyle != navStyle) {
        this->navStyle = navStyle;

        if (navStyle == NavStyle_Ellipse) {
            showNumber = false;
            minHeight = 6;
            minWidth = 6;
            maxWidth = 25;
            navRadius = 3;
        } else if (navStyle == NavStyle_Circle) {
            showNumber = true;
            minHeight = 26;
            minWidth = 26;
            maxWidth = 26;
            navRadius = 13;
        } else if (navStyle == NavStyle_Rect) {
            showNumber = true;
            minHeight = 25;
            minWidth = 25;
            maxWidth = 25;
            navRadius = 3;
        } else if (navStyle == NavStyle_Dot) {
            showNumber = false;
            minHeight = 16;
            minWidth = 16;
            maxWidth = 16;
            navRadius = 8;
        } else if (navStyle == NavStyle_LongRect) {
            showNumber = false;
            minHeight = 6;
            minWidth = 35;
            maxWidth = 35;
            navRadius = 0;
        }

        this->initQss();

        if (timer->isActive()) {
            timer->stop();
        }

        //重新设置图片集合
        if (names.count() > 0) {
            QString imageNames = this->imageNames;
            this->imageNames.clear();
            setImageNames(imageNames);
        }

        showEvent(NULL);
    }
}
