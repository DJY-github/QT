#pragma execution_character_set("utf-8")

#include "rulerprogress.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

RulerProgress::RulerProgress(QWidget *parent) :	QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    precision = 0;
    longStep = 10;
    shortStep = 1;
    rulerTop = true;

    animation = false;
    animationStep = 0.5;

    bgColor = QColor(60, 60, 60);
    lineColor = QColor(255, 255, 255);
    progressColor = QColor(100, 184, 255, 180);

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 8));
}

RulerProgress::~RulerProgress()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void RulerProgress::mousePressEvent(QMouseEvent *e)
{
    setPressedValue(e->pos());
}

void RulerProgress::mouseMoveEvent(QMouseEvent *e)
{
    setPressedValue(e->pos());
}

void RulerProgress::setPressedValue(QPoint pressedPoint)
{
    int x = pressedPoint.x();
    double length = width();
    double increment = length / (maxValue - minValue);
    double value = x / increment;
    setValue(value);
}

void RulerProgress::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制渐变背景
    drawBg(&painter);
    //绘制进度
    drawProgress(&painter);
    //绘制标尺
    if (rulerTop) {
        drawRulerTop(&painter);
    } else {
        drawRulerBottom(&painter);
    }
}

void RulerProgress::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);
    painter->setBrush(bgColor);
    painter->drawRect(rect());
    painter->restore();
}

void RulerProgress::drawProgress(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(progressColor);

    double length = width();
    double increment = length / (maxValue - minValue);
    double initX = (currentValue - minValue) * increment;

    QRect rect(0, 0, initX, height());
    painter->drawRect(rect);
    painter->restore();
}

void RulerProgress::drawRulerTop(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    double initX = 0;

    //绘制横向标尺上部分底部线
    double initTopY = 0;
    QPointF lineTopLeftPot = QPointF(initX, initTopY);
    QPointF lineTopRightPot = QPointF(width() - initX, initTopY);
    painter->drawLine(lineTopLeftPot, lineTopRightPot);

    //绘制上部分及下部分横向标尺刻度
    double length = width();
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 15;
    int shortLineLen = 10;

    //根据范围值绘制刻度值及刻度值 长线条需要移动10像素 短线条需要移动5像素
    for (int i = minValue; i <= maxValue; i = i + shortStep) {
        if (i % longStep == 0) {
            QPointF topPot = QPointF(initX, initTopY);
            QPointF bottomPot = QPointF(initX, initTopY + longLineLen);
            painter->drawLine(topPot, bottomPot);

            //第一个值和最后一个值不要绘制
            if (i == minValue || i == maxValue) {
                initX += increment * shortStep;
                continue;
            }

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double textWidth = fontMetrics().width(strValue);
            double textHeight = fontMetrics().height();

            QPointF textPot = QPointF(initX - textWidth / 2, initTopY + textHeight + longLineLen);
            painter->drawText(textPot, strValue);
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 10;
            } else {
                shortLineLen = 6;
            }

            QPointF topPot = QPointF(initX, initTopY);
            QPointF bottomPot = QPointF(initX, initTopY + shortLineLen);
            painter->drawLine(topPot, bottomPot);
        }

        initX += increment * shortStep;
    }

    painter->restore();
}

void RulerProgress::drawRulerBottom(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    double initX = 0;

    //绘制横向标尺下部分底部线
    double initBottomY = height();
    QPointF lineBottomLeftPot = QPointF(initX, initBottomY);
    QPointF lineBottomRightPot = QPointF(width() - initX, initBottomY);
    painter->drawLine(lineBottomLeftPot, lineBottomRightPot);

    //绘制上部分及下部分横向标尺刻度
    double length = width();
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 15;
    int shortLineLen = 10;

    //根据范围值绘制刻度值及刻度值 长线条需要移动10像素 短线条需要移动5像素
    for (int i = minValue; i <= maxValue; i = i + shortStep) {
        if (i % longStep == 0) {
            QPointF topPot = QPointF(initX, initBottomY);
            QPointF bottomPot = QPointF(initX, initBottomY - longLineLen);
            painter->drawLine(topPot, bottomPot);

            //第一个值和最后一个值不要绘制
            if (i == minValue || i == maxValue) {
                initX += increment * shortStep;
                continue;
            }

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double textWidth = fontMetrics().width(strValue);
            double textHeight = fontMetrics().height();

            QPointF textPot = QPointF(initX - textWidth / 2, initBottomY - textHeight / 2 - longLineLen);
            painter->drawText(textPot, strValue);
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 10;
            } else {
                shortLineLen = 6;
            }

            QPointF topPot = QPointF(initX, initBottomY);
            QPointF bottomPot = QPointF(initX, initBottomY - shortLineLen);
            painter->drawLine(topPot, bottomPot);
        }

        initX += increment * shortStep;
    }

    painter->restore();
}

double RulerProgress::getMinValue() const
{
    return this->minValue;
}

double RulerProgress::getMaxValue() const
{
    return this->maxValue;
}

double RulerProgress::getValue() const
{
    return this->value;
}

int RulerProgress::getPrecision() const
{
    return this->precision;
}

int RulerProgress::getLongStep() const
{
    return this->longStep;
}

int RulerProgress::getShortStep() const
{
    return this->shortStep;
}

bool RulerProgress::getRulerTop() const
{
    return this->rulerTop;
}

bool RulerProgress::getAnimation() const
{
    return this->animation;
}

double RulerProgress::getAnimationStep() const
{
    return this->animationStep;
}

QColor RulerProgress::getBgColor() const
{
    return this->bgColor;
}

QColor RulerProgress::getLineColor() const
{
    return this->lineColor;
}

QColor RulerProgress::getProgressColor() const
{
    return this->progressColor;
}

QSize RulerProgress::sizeHint() const
{
    return QSize(500, 50);
}

QSize RulerProgress::minimumSizeHint() const
{
    return QSize(50, 20);
}

void RulerProgress::setRange(double minValue, double maxValue)
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

void RulerProgress::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void RulerProgress::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void RulerProgress::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void RulerProgress::setValue(double value)
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

void RulerProgress::setValue(int value)
{
    setValue((double)value);
}

void RulerProgress::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void RulerProgress::setLongStep(int longStep)
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

void RulerProgress::setShortStep(int shortStep)
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

void RulerProgress::setRulerTop(bool rulerTop)
{
    if (this->rulerTop != rulerTop) {
        this->rulerTop = rulerTop;
        update();
    }
}

void RulerProgress::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void RulerProgress::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void RulerProgress::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void RulerProgress::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void RulerProgress::setProgressColor(const QColor &progressColor)
{
    if (this->progressColor != progressColor) {
        this->progressColor = progressColor;
        update();
    }
}

void RulerProgress::updateValue()
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
