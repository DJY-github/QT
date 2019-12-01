#pragma execution_character_set("utf-8")

#include "rulerdouble.h"
#include "qpainter.h"
#include "qdebug.h"

RulerDouble::RulerDouble(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;
    alarmValue = 90;

    minValueRight = 0;
    maxValueRight = 100;
    valueRight = 0;
    alarmValueRight = 90;

    longStep = 10;
    shortStep = 2;
    longStepRight = 10;
    shortStepRight = 2;

    bgColor = QColor(2, 16, 34);
    scaleColor = QColor(255, 255, 255);
    textColor = QColor(200, 200, 200);
    alarmScaleColor = QColor(255, 107, 107);

    space = 20;
    scaleStyle = ScaleStyle_Single;

    setFont(QFont("Arial", 9));
}

void RulerDouble::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);

    //绘制左边刻度尺
    drawLeftScale(&painter);
    //绘制右边刻度尺
    drawRightScale(&painter);

    //绘制左边刻度值
    drawLeftText(&painter);
    //绘制左边刻度值
    drawRightText(&painter);

    //绘制左边指示器
    drawLeftPointer(&painter);
    //绘制右边指示器
    drawRightPointer(&painter);
}

void RulerDouble::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawRect(rect());
    painter->restore();
}

void RulerDouble::drawLeftScale(QPainter *painter)
{    
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    int longStep = this->longStep;
    int shortStep = this->shortStep;

    QPen pen;
    pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(scaleColor);
    painter->save();
    painter->setPen(pen);

    //绘制纵向标尺线
    double initLeftX = space;
    double initY = space;

    //左侧纵向标尺线
    painter->drawLine(QPointF(initLeftX, initY), QPointF(initLeftX, height() - space));

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
            painter->drawLine(QPointF(initLeftX + longLineLen, initY), QPointF(initLeftX, initY));
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 7;
            } else {
                shortLineLen = 4;
            }

            painter->drawLine(QPointF(initLeftX + shortLineLen, initY), QPointF(initLeftX, initY));
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void RulerDouble::drawRightScale(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    int longStep = this->longStep;
    int shortStep = this->shortStep;

    //如果是双精度样式,则范围值及步长取右边的范围值及步长
    if (scaleStyle == ScaleStyle_Double) {
        minValue = this->minValueRight;
        maxValue = this->maxValueRight;
        longStep = this->longStepRight;
        shortStep = this->shortStepRight;
    }

    QPen pen;
    pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(scaleColor);
    painter->save();
    painter->setPen(pen);

    //绘制纵向标尺线
    double initRightX = this->width() - space;
    double initY = space;

    //右侧纵向标尺线
    painter->drawLine(QPointF(initRightX, initY), QPointF(initRightX, height() - space));

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
            painter->drawLine(QPointF(initRightX - longLineLen, initY), QPointF(initRightX, initY));
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 7;
            } else {
                shortLineLen = 4;
            }

            painter->drawLine(QPointF(initRightX - shortLineLen, initY), QPointF(initRightX, initY));
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void RulerDouble::drawLeftText(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    int longStep = this->longStep;
    int shortStep = this->shortStep;

    painter->save();
    painter->setPen(textColor);

    double initCenterX = space;
    double initCenterY = space / 2;

    double initLeftX = space;
    double initLeftY = space;

    //绘制纵向标尺刻度
    double length = this->height() - 2 * space;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            QString strValue = QString("%1").arg(i);

            if (scaleStyle == ScaleStyle_Single) {
                //中间刻度值
                QRect textRect(initCenterX, initCenterY, this->width() - space * 2, 20);
                painter->drawText(textRect, Qt::AlignCenter, strValue);
            } else if (scaleStyle == ScaleStyle_Double) {
                //左刻度值
                QPointF textLeftPot(initLeftX + longLineLen + shortLineLen, initLeftY + 4);
                painter->drawText(textLeftPot, strValue);
            }
        }

        initCenterY += increment * shortStep;
        initLeftY += increment * shortStep;
    }

    painter->restore();
}

void RulerDouble::drawRightText(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    int longStep = this->longStep;
    int shortStep = this->shortStep;

    //如果是双精度样式,则范围值及步长取右边的范围值及步长
    if (scaleStyle == ScaleStyle_Double) {
        minValue = this->minValueRight;
        maxValue = this->maxValueRight;
        longStep = this->longStepRight;
        shortStep = this->shortStepRight;
    }

    painter->save();
    painter->setPen(textColor);

    double initCenterX = space;
    double initCenterY = space / 2;

    double initRightX = this->width() - space;
    double initRightY = space;

    //绘制纵向标尺刻度
    double length = this->height() - 2 * space;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            QString strValue = QString("%1").arg(i);

            if (scaleStyle == ScaleStyle_Single) {
                //中间刻度值
                QRect textRect(initCenterX, initCenterY, this->width() - space * 2, 20);
                painter->drawText(textRect, Qt::AlignCenter, strValue);
            } else if (scaleStyle == ScaleStyle_Double) {
                //右刻度值
                double fontWidth = painter->fontMetrics().width(strValue);
                QPointF textRightPot(initRightX - longLineLen - shortLineLen - fontWidth, initRightY + 4);
                painter->drawText(textRightPot, strValue);
            }
        }

        initCenterY += increment * shortStep;
        initRightY += increment * shortStep;
    }

    painter->restore();
}

void RulerDouble::drawLeftPointer(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    double value = this->value;

    painter->save();
    painter->setPen(alarmScaleColor);
    painter->setBrush(alarmScaleColor);

    //找到当前值所在坐标
    double barHeight = this->height() - space * 2;
    double increment = (double)barHeight / (maxValue - minValue);

    int offset = 10;
    double initLeftX = space + offset;
    double initY = this->height() - space - ((value - minValue) * increment);

    //左侧三角形指示器
    QPolygon leftPts;
    leftPts.append(QPoint(initLeftX, initY));
    leftPts.append(QPoint(initLeftX + offset, initY - offset / 2));
    leftPts.append(QPoint(initLeftX + offset, initY + offset / 2));
    painter->drawPolygon(leftPts);

    painter->restore();
}

void RulerDouble::drawRightPointer(QPainter *painter)
{
    double minValue = this->minValue;
    double maxValue = this->maxValue;
    double value = this->value;

    //如果是双精度样式,则范围值及步长取右边的范围值及步长
    if (scaleStyle == ScaleStyle_Double) {
        minValue = this->minValueRight;
        maxValue = this->maxValueRight;
        value = this->valueRight;
    }

    painter->save();
    painter->setPen(alarmScaleColor);
    painter->setBrush(alarmScaleColor);

    //找到当前值所在坐标
    double barHeight = this->height() - space * 2;
    double increment = (double)barHeight / (maxValue - minValue);

    int offset = 10;
    double initRightX = this->width() - space - offset;
    double initY = this->height() - space - ((value - minValue) * increment);

    //右侧三角形指示器
    QPolygon rightPts;
    rightPts.append(QPoint(initRightX, initY));
    rightPts.append(QPoint(initRightX - offset, initY - offset / 2));
    rightPts.append(QPoint(initRightX - offset, initY + offset / 2));
    painter->drawPolygon(rightPts);

    painter->restore();
}

double RulerDouble::getMinValue() const
{
    return this->minValue;
}

double RulerDouble::getMaxValue() const
{
    return this->maxValue;
}

double RulerDouble::getValue() const
{
    return this->value;
}

double RulerDouble::getAlarmValue() const
{
    return this->alarmValue;
}

double RulerDouble::getMinValueRight() const
{
    return this->minValueRight;
}

double RulerDouble::getMaxValueRight() const
{
    return this->maxValueRight;
}

double RulerDouble::getValueRight() const
{
    return this->valueRight;
}

double RulerDouble::getAlarmValueRight() const
{
    return this->alarmValueRight;
}

int RulerDouble::getLongStep() const
{
    return this->longStep;
}

int RulerDouble::getShortStep() const
{
    return this->shortStep;
}

int RulerDouble::getLongStepRight() const
{
    return this->longStepRight;
}

int RulerDouble::getShortStepRight() const
{
    return this->shortStepRight;
}

QColor RulerDouble::getBgColor() const
{
    return this->bgColor;
}

QColor RulerDouble::getScaleColor() const
{
    return this->scaleColor;
}

QColor RulerDouble::getTextColor() const
{
    return this->textColor;
}

QColor RulerDouble::getAlarmScaleColor() const
{
    return this->alarmScaleColor;
}

int RulerDouble::getSpace() const
{
    return this->space;
}

RulerDouble::ScaleStyle RulerDouble::getScaleStyle() const
{
    return this->scaleStyle;
}

QSize RulerDouble::sizeHint() const
{
    return QSize(120, 300);
}

QSize RulerDouble::minimumSizeHint() const
{
    return QSize(50, 100);
}

void RulerDouble::setRange(double minValue, double maxValue)
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

void RulerDouble::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void RulerDouble::setRangeRight(double minValueRight, double maxValueRight)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValueRight >= maxValueRight) {
        return;
    }

    this->minValueRight = minValueRight;
    this->maxValueRight = maxValueRight;

    //如果目标值不在范围值内,则重新设置目标值
    if (valueRight < minValueRight || valueRight > maxValueRight) {
        setValueRight(valueRight);
    }

    update();
}

void RulerDouble::setRangeRight(int minValueRight, int maxValueRight)
{
    setRangeRight((double)minValueRight, (double)maxValueRight);
}

void RulerDouble::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void RulerDouble::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void RulerDouble::setMinValueRight(double minValue)
{
    setRangeRight(minValue, maxValue);
}

void RulerDouble::setMaxValueRight(double maxValue)
{
    setRangeRight(minValue, maxValue);
}

void RulerDouble::setValue(double value)
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
    update();
}

void RulerDouble::setValue(int value)
{
    setValue((double)value);
}

void RulerDouble::setValueRight(double valueRight)
{
    //值小于最小值或者值大于最大值则无需处理
    if (valueRight < minValueRight || valueRight > maxValueRight) {
        return;
    }

    this->valueRight = valueRight;
    update();
}

void RulerDouble::setValueRight(int valueRight)
{
    setValueRight((double)valueRight);
}

void RulerDouble::setAlarmValue(double alarmValue)
{
    if (this->alarmValue != alarmValue) {
        this->alarmValue = alarmValue;
        update();
    }
}

void RulerDouble::setAlarmValueRight(double alarmValueRight)
{
    if (this->alarmValueRight != alarmValueRight) {
        this->alarmValueRight = alarmValueRight;
        update();
    }
}

void RulerDouble::setLongStep(int longStep)
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

void RulerDouble::setShortStep(int shortStep)
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

void RulerDouble::setLongStepRight(int longStepRight)
{
    //短步长不能超过长步长
    if (longStepRight < shortStepRight) {
        return;
    }

    if (this->longStepRight != longStepRight) {
        this->longStepRight = longStepRight;
        update();
    }
}

void RulerDouble::setShortStepRight(int shortStepRight)
{
    //短步长不能超过长步长
    if (longStepRight < shortStepRight) {
        return;
    }

    if (this->shortStepRight != shortStepRight) {
        this->shortStepRight = shortStepRight;
        update();
    }
}

void RulerDouble::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void RulerDouble::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void RulerDouble::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void RulerDouble::setAlarmScaleColor(const QColor &alarmScaleColor)
{
    if (this->alarmScaleColor != alarmScaleColor) {
        this->alarmScaleColor = alarmScaleColor;
        update();
    }
}

void RulerDouble::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void RulerDouble::setScaleStyle(const RulerDouble::ScaleStyle &scaleStyle)
{
    if (this->scaleStyle != scaleStyle) {
        this->scaleStyle = scaleStyle;
        update();
    }
}
