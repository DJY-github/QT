#pragma execution_character_set("utf-8")

#include "progressplay.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

ProgressPlay::ProgressPlay(QWidget *parent) : QWidget(parent)
{
    valueAll = 100;
    valuePlay = 20;
    valueLoad = 50;

    colorPlay = QColor(34, 163, 169);
    colorLoad = QColor(255, 192, 1);
    bgColor = QColor(40, 45, 48);
    textColor = QColor(255, 255, 255);

    radius = 0;
    autoRadius = false;
    showProgressRadius = false;

    borderWidth = 0;
    borderColor = QColor(255, 255, 255);
}

void ProgressPlay::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    if (autoRadius) {
        radius = this->height() / 2;
    }

    //绘制背景
    drawBg(&painter);
    //绘制缓存进度,必须先绘制缓存的,然后绘制播放的遮住
    drawValueLoad(&painter);
    //绘制已播放进度
    drawValuePlay(&painter);

    //绘制边框
    if (borderWidth > 0) {
        drawBorder(&painter);
    }
}

void ProgressPlay::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    //将背景区域减少一个像素,这样圆角区域不会产生轻微锯齿状
    QRect rect(1, 1, this->width() - 2, this->height() - 2);
    painter->drawRoundedRect(rect, radius, radius);
    painter->restore();
}

void ProgressPlay::drawValueLoad(QPainter *painter)
{
    painter->save();

    double percent = (double)valueLoad / valueAll;
    int width = this->width() * percent;

    painter->setPen(Qt::NoPen);
    painter->setBrush(colorLoad);

    //计算绘制的区域,需要裁剪圆角部分
    QPainterPath clipPath;
    clipPath.addRoundedRect(this->rect(), radius, radius);
    painter->setClipPath(clipPath);
    QRect rect(0, 0, width, this->height());

    if (showProgressRadius) {
        painter->drawRoundedRect(rect, radius, radius);
    } else {
        painter->drawRect(rect);
    }

    painter->restore();
}

void ProgressPlay::drawValuePlay(QPainter *painter)
{
    painter->save();

    double percent = (double)valuePlay / valueAll;
    int width = this->width() * percent;

    painter->setPen(Qt::NoPen);
    painter->setBrush(colorPlay);

    //计算绘制的区域,需要裁剪圆角部分
    QPainterPath clipPath;
    clipPath.addRoundedRect(this->rect(), radius, radius);
    painter->setClipPath(clipPath);
    QRect rect(0, 0, width, this->height());

    if (showProgressRadius) {
        painter->drawRoundedRect(rect, radius, radius);
    } else {
        painter->drawRect(rect);
    }

    painter->restore();
}

void ProgressPlay::drawBorder(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setWidthF(borderWidth);
    pen.setColor(borderColor);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    QRect rect(1, 1, this->width() - 2, this->height() - 2);
    painter->drawRoundedRect(rect, radius, radius);
    painter->restore();
}

int ProgressPlay::getValueAll() const
{
    return this->valueAll;
}

int ProgressPlay::getValuePlay() const
{
    return this->valuePlay;
}

int ProgressPlay::getValueLoad() const
{
    return this->valueLoad;
}

QColor ProgressPlay::getColorPlay() const
{
    return this->colorPlay;
}

QColor ProgressPlay::getColorLoad() const
{
    return this->colorLoad;
}

QColor ProgressPlay::getBgColor() const
{
    return this->bgColor;
}

QColor ProgressPlay::getTextColor() const
{
    return this->textColor;
}

int ProgressPlay::getRadius() const
{
    return this->radius;
}

bool ProgressPlay::getAutoRadius() const
{
    return this->autoRadius;
}

bool ProgressPlay::getShowProgressRadius() const
{
    return this->showProgressRadius;
}

double ProgressPlay::getBorderWidth() const
{
    return this->borderWidth;
}

QColor ProgressPlay::getBorderColor() const
{
    return this->borderColor;
}

QSize ProgressPlay::sizeHint() const
{
    return QSize(300, 30);
}

QSize ProgressPlay::minimumSizeHint() const
{
    return QSize(10, 5);
}

void ProgressPlay::setValueAll(int valueAll)
{
    if (this->valueAll != valueAll && valueAll >= 0) {
        this->valueAll = valueAll;
        this->update();;
    }
}

void ProgressPlay::setValuePlay(int valuePlay)
{
    if (this->valuePlay != valuePlay && valuePlay >= 0 && valuePlay <= valueLoad) {
        this->valuePlay = valuePlay;
        this->update();;
    }
}

void ProgressPlay::setValueLoad(int valueLoad)
{
    if (this->valueLoad != valueLoad && valueLoad >= 0 && valueLoad <= valueAll) {
        this->valueLoad = valueLoad;
        this->update();;
    }
}

void ProgressPlay::setColorPlay(const QColor &colorPlay)
{
    if (this->colorPlay != colorPlay) {
        this->colorPlay = colorPlay;
        this->update();;
    }
}

void ProgressPlay::setColorLoad(const QColor &colorLoad)
{
    if (this->colorLoad != colorLoad) {
        this->colorLoad = colorLoad;
        this->update();;
    }
}

void ProgressPlay::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();;
    }
}

void ProgressPlay::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();;
    }
}

void ProgressPlay::setRadius(int radius)
{
    if (this->radius != radius) {
        this->radius = radius;
        this->update();;
    }
}

void ProgressPlay::setAutoRadius(bool autoRadius)
{
    if (this->autoRadius != autoRadius) {
        this->autoRadius = autoRadius;
        this->update();;
    }
}

void ProgressPlay::setShowProgressRadius(bool showProgressRadius)
{
    if (this->showProgressRadius != showProgressRadius) {
        this->showProgressRadius = showProgressRadius;
        this->update();;
    }
}

void ProgressPlay::setBorderWidth(double borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        this->update();;
    }
}

void ProgressPlay::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        this->update();;
    }
}
