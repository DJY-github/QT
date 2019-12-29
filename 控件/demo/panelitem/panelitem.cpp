#pragma execution_character_set("utf-8")

#include "panelitem.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

PanelItem::PanelItem(QWidget *parent) : QWidget(parent)
{
    titleHeight = 30;
    titleText = "";
    titleFont = QFont(font().family(), 15);
    titleAlignment = Alignment_Center;
    titleColor = QColor(255, 255, 255);
    titleDisableColor = QColor(230, 230, 230);

    borderWidth = 3;
    borderRadius = 5;
    borderColor = QColor(21, 156, 119);
    borderDisableColor = QColor(180, 180, 180);

    alarmTextColor = QColor(250, 250, 250);
    alarmDarkColor = QColor(205, 0, 0);
    alarmNormalColor = QColor(80, 80, 80);
    alarmInterval = 500;

    isAlarm = false;
    isEnable = true;

    isDark = false;
    tempColor = borderColor;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkAlarm()));
    timer->setInterval(alarmInterval);
}

PanelItem::~PanelItem()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void PanelItem::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制边框
    drawBorder(&painter);
    //绘制标题
    drawTitle(&painter);
}

void PanelItem::drawBorder(QPainter *painter)
{
    if (borderWidth <= 0) {
        return;
    }

    painter->save();

    QPen pen;
    pen.setWidth(borderWidth);
    pen.setColor(tempColor);

    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    QRect rect(borderWidth / 2, borderWidth / 2, width() - borderWidth, height() - borderWidth);
    painter->drawRoundedRect(rect, borderRadius, borderRadius);

    painter->restore();
}

void PanelItem::drawTitle(QPainter *painter)
{
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(tempColor);

    int offset = borderWidth - borderWidth / 3;
    QRect rect(offset, offset, width() - offset * 2, titleHeight);
    painter->drawRect(rect);

    //绘制标题文字
    if (isEnable) {
        painter->setPen(isAlarm ? alarmTextColor : titleColor);
    } else {
        painter->setPen(titleDisableColor);
    }

    painter->setFont(titleFont);

    //文字区域要重新计算
    offset = borderWidth * 3;
    QRect textRect(offset, 0, width() - offset * 2, titleHeight);

    Qt::Alignment align;
    if (titleAlignment == Alignment_Left) {
        align = Qt::AlignLeft | Qt::AlignVCenter;
    } else if (titleAlignment == Alignment_Center) {
        align = Qt::AlignHCenter | Qt::AlignVCenter;
    } else if (titleAlignment == Alignment_Right) {
        align = Qt::AlignRight | Qt::AlignVCenter;
    }

    painter->drawText(textRect, align, titleText);

    painter->restore();
}

int PanelItem::getTitleHeight() const
{
    return this->titleHeight;
}

QString PanelItem::getTitleText() const
{
    return this->titleText;
}

QFont PanelItem::getTitleFont() const
{
    return this->titleFont;
}

PanelItem::Alignment PanelItem::getTitleAlignment() const
{
    return this->titleAlignment;
}

QColor PanelItem::getTitleColor() const
{
    return this->titleColor;
}

QColor PanelItem::getTitleDisableColor() const
{
    return this->titleDisableColor;
}

int PanelItem::getBorderWidth() const
{
    return this->borderWidth;
}

int PanelItem::getBorderRadius() const
{
    return this->borderRadius;
}

QColor PanelItem::getBorderColor() const
{
    return this->borderColor;
}

QColor PanelItem::getBorderDisableColor() const
{
    return this->borderDisableColor;
}

int PanelItem::getAlarmInterval() const
{
    return this->alarmInterval;
}

QColor PanelItem::getAlarmTextColor() const
{
    return this->alarmTextColor;
}

QColor PanelItem::getAlarmDarkColor() const
{
    return this->alarmDarkColor;
}

QColor PanelItem::getAlarmNormalColor() const
{
    return this->alarmNormalColor;
}

bool PanelItem::getIsAlarm() const
{
    return this->isAlarm;
}

bool PanelItem::getIsEnable() const
{
    return this->isEnable;
}

QSize PanelItem::sizeHint() const
{
    return QSize(250, 200);
}

QSize PanelItem::minimumSizeHint() const
{
    return QSize(30, 20);
}

void PanelItem::checkAlarm()
{
    if (isDark) {
        tempColor = alarmNormalColor;
    } else {
        tempColor = alarmDarkColor;
    }

    isDark = !isDark;
    update();
}

void PanelItem::setAlarm(bool alarm)
{
    if (!isEnable) {
        return;
    }

    isAlarm = alarm;

    if (alarm) {
        if (!timer->isActive()) {
            timer->start();
        }

        isDark = true;
        tempColor = alarmDarkColor;
    } else {
        if (timer->isActive()) {
            timer->stop();
        }

        isDark = false;
        tempColor = borderColor;
    }

    update();
}

void PanelItem::setEnable(bool enable)
{
    isEnable = enable;
    if (timer->isActive()) {
        timer->stop();
    }

    if (enable) {
        tempColor = borderColor;
    } else {
        tempColor = borderDisableColor;
    }

    update();

    //将对应的子元素设置启用禁用状态
    QList<QWidget *> widgets = this->findChildren<QWidget *>();
    foreach (QWidget *w, widgets) {
        w->setEnabled(enable);
    }
}

void PanelItem::setTitleHeight(int titleHeight)
{
    if (this->titleHeight != titleHeight) {
        this->titleHeight = titleHeight;
        update();
    }
}

void PanelItem::setTitleText(const QString &titleText)
{
    if (this->titleText != titleText) {
        this->titleText = titleText;
        update();
    }
}

void PanelItem::setTitleFont(const QFont &titleFont)
{
    if (this->titleFont != titleFont) {
        this->titleFont = titleFont;
        update();
    }
}

void PanelItem::setTitleAlignment(const Alignment &titleAlignment)
{
    if (this->titleAlignment != titleAlignment) {
        this->titleAlignment = titleAlignment;
        update();
    }
}

void PanelItem::setTitleColor(const QColor &titleColor)
{
    if (this->titleColor != titleColor) {
        this->titleColor = titleColor;
        update();
    }
}

void PanelItem::setTitleDisableColor(const QColor &titleDisableColor)
{
    if (this->titleDisableColor != titleDisableColor) {
        this->titleDisableColor = titleDisableColor;
        update();
    }
}

void PanelItem::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        update();
    }
}

void PanelItem::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        update();
    }
}

void PanelItem::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        setEnable(isEnable);
        update();
    }
}

void PanelItem::setBorderDisableColor(const QColor &borderDisableColor)
{
    if (this->borderDisableColor != borderDisableColor) {
        this->borderDisableColor = borderDisableColor;
        setEnable(isEnable);
        update();
    }
}

void PanelItem::setAlarmInterval(int alarmInterval)
{
    if (this->alarmInterval != alarmInterval && alarmInterval >= 100) {
        this->alarmInterval = alarmInterval;
        timer->setInterval(alarmInterval);
    }
}

void PanelItem::setAlarmTextColor(const QColor &alarmTextColor)
{
    if (this->alarmTextColor != alarmTextColor) {
        this->alarmTextColor = alarmTextColor;
        update();
    }
}

void PanelItem::setAlarmDarkColor(const QColor &alarmDarkColor)
{
    if (this->alarmDarkColor != alarmDarkColor) {
        this->alarmDarkColor = alarmDarkColor;
        setAlarm(isAlarm);
        update();
    }
}

void PanelItem::setAlarmNormalColor(const QColor &alarmNormalColor)
{
    if (this->alarmNormalColor != alarmNormalColor) {
        this->alarmNormalColor = alarmNormalColor;
        setAlarm(isAlarm);
        update();
    }
}

