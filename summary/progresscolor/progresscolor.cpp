#pragma execution_character_set("utf-8")

#include "progresscolor.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

ProgressColor::ProgressColor(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;

    precision = 0;
    step = 0;
    space = 5;
    radius = 5;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);

    lineColor = QColor(230, 230, 230);
    textColor = QColor(0, 0, 0);

    barBgColor = QColor(250, 250, 250);
    barColor = QColor(100, 184, 255);

    setFont(QFont("Arial", 8));
}

void ProgressColor::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    //drawBg(&painter);
    //绘制进度
    drawBar(&painter);
}

void ProgressColor::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void ProgressColor::drawBar(QPainter *painter)
{
    painter->save();

    //自动计算文字字体大小
    QFont font;
    font.setPixelSize((width() / 10) * 0.35);
    painter->setFont(font);

    //计算进度值字符的宽度
    double currentValue = (double)(value - minValue) * 100 / (maxValue - minValue);
    QString strValue = QString("%1%").arg(currentValue, 0, 'f', precision);
    QString strMaxValue = QString("%1%").arg(maxValue, 0, 'f', precision);
    //字符的宽度取最大值字符的宽度 + 10
    int textWidth = painter->fontMetrics().width(strMaxValue) + 10;

    //绘制进度值背景
    QPointF textTopLeft(width() - space - textWidth, space);
    QPointF textBottomRight(width() - space, height() - space);
    QRectF textRect(textTopLeft, textBottomRight);
    painter->setPen(barBgColor);
    painter->setBrush(barBgColor);
    painter->drawRoundedRect(textRect, radius, radius);

    //绘制进度值
    painter->setPen(textColor);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    //绘制进度条背景
    QRectF barBgRect(QPointF(space, space), QPointF(width() - space * 2 - textWidth, height() - space));
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBgColor);
    painter->drawRoundedRect(barBgRect, radius, radius);

    //绘制进度条
    double length = width() - space  - space * 2 - textWidth;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    QRectF barRect(QPointF(space, space), QPointF(space + increment * (value - minValue), height() - space));
    painter->setBrush(barColor);
    painter->drawRoundedRect(barRect, radius, radius);

    //绘制背景分割线条 每一格长度7
    painter->setPen(lineColor);
    int initX = 5;
    int lineCount = barBgRect.width() / step;
    double lineX = (double)barBgRect.width() / lineCount;

    //线条高度在进度条高度上 - 1
    while (lineCount > 0) {
        QPointF topPot(initX + lineX, space + 1);
        QPointF bottomPot(initX + lineX, height() - space - 1);
        painter->drawLine(topPot, bottomPot);
        initX += lineX;
        lineCount--;
    }

    painter->restore();
}

double ProgressColor::getMinValue() const
{
    return this->minValue;
}

double ProgressColor::getMaxValue() const
{
    return this->maxValue;
}

double ProgressColor::getValue() const
{
    return this->value;
}

int ProgressColor::getPrecision() const
{
    return this->precision;
}

int ProgressColor::getStep() const
{
    return this->step;
}

int ProgressColor::getSpace() const
{
    return this->space;
}

int ProgressColor::getRadius() const
{
    return this->radius;
}

QColor ProgressColor::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor ProgressColor::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor ProgressColor::getLineColor() const
{
    return this->lineColor;
}

QColor ProgressColor::getTextColor() const
{
    return this->textColor;
}

QColor ProgressColor::getBarBgColor() const
{
    return this->barBgColor;
}

QColor ProgressColor::getBarColor() const
{
    return this->barColor;
}

QSize ProgressColor::sizeHint() const
{
    return QSize(300, 30);
}

QSize ProgressColor::minimumSizeHint() const
{
    return QSize(50, 20);
}

void ProgressColor::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (value < minValue || value > maxValue) {
        setValue(value);
    }

    update();
}

void ProgressColor::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void ProgressColor::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void ProgressColor::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void ProgressColor::setValue(double value)
{
    //值和当前值一致则无需处理
    if (value == this->value) {
        return;
    }

    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    this->value = value;
    emit valueChanged(value);
    update();
}

void ProgressColor::setValue(int value)
{
    setValue((double)value);
}

void ProgressColor::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void ProgressColor::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
        update();
    }
}

void ProgressColor::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void ProgressColor::setRadius(int radius)
{
    if (this->radius != radius) {
        this->radius = radius;
        update();
    }
}

void ProgressColor::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void ProgressColor::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void ProgressColor::setLineColor(QColor lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void ProgressColor::setTextColor(QColor textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void ProgressColor::setBarBgColor(QColor barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        update();
    }
}

void ProgressColor::setBarColor(QColor barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        update();
    }
}
