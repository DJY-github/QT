#pragma execution_character_set("utf-8")

#include "rulerbar.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

RulerBar::RulerBar(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;

    precision = 0;
    longStep = 10;
    shortStep = 1;
    space = 20;

    animation = false;
    animationStep = 0.5;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    lineColor = QColor(255, 255, 255);

    barBgColor = QColor(250, 250, 250);
    barColor = QColor(100, 184, 255);

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 8));
}

RulerBar::~RulerBar()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void RulerBar::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制标尺
    drawRuler(&painter);
    //绘制柱状背景
    drawBarBg(&painter);
    //绘制柱状
    drawBar(&painter);
}

void RulerBar::drawBg(QPainter *painter)
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

void RulerBar::drawRuler(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    //绘制纵向标尺线 20的长度为刻度尺文字的宽度
    double initX = space + 20;
    double initY = space;
    QPointF topPot(initX, initY);
    QPointF bottomPot(initX, height() - space);
    painter->drawLine(topPot, bottomPot);

    //绘制纵向标尺刻度
    double length = height() - 2 * space;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    //根据范围值绘制刻度值及刻度值
    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            QPointF leftPot(initX + longLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double fontWidth = painter->fontMetrics().width(strValue);
            double fontHeight = painter->fontMetrics().height();
            QPointF textPot(initX - fontWidth - 5, initY + fontHeight / 3);
            painter->drawText(textPot, strValue);
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 7;
            } else {
                shortLineLen = 4;
            }

            QPointF leftPot(initX + shortLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void RulerBar::drawBarBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    //20的长度为刻度尺文字的宽度 15为刻度尺到柱状图的宽度
    double initX = space + 20 + 15;
    QPointF topLeftPot(initX, space);
    QPointF bottomRightPot(width() - space , height() - space);
    barRect = QRectF(topLeftPot, bottomRightPot);

    painter->setBrush(barBgColor);
    painter->drawRect(barRect);
    painter->restore();
}

void RulerBar::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    double barHeight = barRect.height();
    double increment = (double)barHeight / (maxValue - minValue);
    double initY = (currentValue - minValue) * increment;

    QPointF topLeftPot(barRect.topLeft().x(), barRect.bottomLeft().y() - initY);
    QPointF bottomRightPot(barRect.bottomRight());
    QRectF currentRect(topLeftPot, bottomRightPot);

    painter->setBrush(barColor);
    painter->drawRect(currentRect);
    painter->restore();
}

double RulerBar::getMinValue() const
{
    return this->minValue;
}

double RulerBar::getMaxValue() const
{
    return this->maxValue;
}

double RulerBar::getValue() const
{
    return this->value;
}

int RulerBar::getPrecision() const
{
    return this->precision;
}

int RulerBar::getLongStep() const
{
    return this->longStep;
}

int RulerBar::getShortStep() const
{
    return this->shortStep;
}

int RulerBar::getSpace() const
{
    return this->space;
}

bool RulerBar::getAnimation() const
{
    return this->animation;
}

double RulerBar::getAnimationStep() const
{
    return this->animationStep;
}

QColor RulerBar::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor RulerBar::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor RulerBar::getLineColor() const
{
    return this->lineColor;
}

QColor RulerBar::getBarBgColor() const
{
    return this->barBgColor;
}

QColor RulerBar::getBarColor() const
{
    return this->barColor;
}

QSize RulerBar::sizeHint() const
{
    return QSize(100, 350);
}

QSize RulerBar::minimumSizeHint() const
{
    return QSize(20, 50);
}

void RulerBar::setRange(double minValue, double maxValue)
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

void RulerBar::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void RulerBar::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void RulerBar::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void RulerBar::setValue(double value)
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

    if (value > this->value) {
        reverse = false;
    } else if (value < this->value) {
        reverse = true;
    }

    this->value = value;
    emit valueChanged(value);

    if (!animation) {
        currentValue = this->value;
        update();
    } else {
        timer->start();
    }
}

void RulerBar::setValue(int value)
{
    setValue((double)value);
}

void RulerBar::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void RulerBar::setLongStep(int longStep)
{
    //短步长不能超过长步长
    if (longStep < shortStep) {
        return;
    }

    if (this->longStep != longStep) {
        this->longStep = longStep;
        update();
    }
}

void RulerBar::setShortStep(int shortStep)
{
    //短步长不能超过长步长
    if (longStep < shortStep) {
        return;
    }

    if (this->shortStep != shortStep) {
        this->shortStep = shortStep;
        update();
    }
}

void RulerBar::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void RulerBar::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void RulerBar::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void RulerBar::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void RulerBar::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void RulerBar::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void RulerBar::setBarBgColor(const QColor &barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        update();
    }
}

void RulerBar::setBarColor(const QColor &barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        update();
    }
}

void RulerBar::updateValue()
{
    if (!reverse) {
        if (currentValue >= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    update();
}
