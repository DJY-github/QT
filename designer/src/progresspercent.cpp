#pragma execution_character_set("utf-8")

#include "progresspercent.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

ProgressPercent::ProgressPercent(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    nullPosition = 0;
    borderWidth = 10;

    waterHeight = 0.08;
    waterDensity = 2.0;

    showPercent = true;
    showFree = false;
    showSmallCircle = false;
    clockWise = true;
    borderOut = false;

    usedColor = QColor(100, 184, 255);
    freeColor = QColor(100, 100, 100);
    circleColor = QColor(70, 70, 70);
    textColor = QColor(250, 250, 250);

    percentStyle = PercentStyle_Arc;

    offset = 0;
    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    setFont(QFont("Arial", 8));
}

ProgressPercent::~ProgressPercent()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void ProgressPercent::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    int radius = 99;

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制中心圆
    drawCircle(&painter, radius);

    int offset = 1;

    //根据样式绘制进度
    if (percentStyle == PercentStyle_Arc) {
        drawArc(&painter, radius - borderWidth / offset);
    } else if (percentStyle == PercentStyle_Polo) {
        drawPolo(&painter, radius - borderWidth / offset);
    } else if (percentStyle == PercentStyle_Wave) {
        drawWave(&painter, radius - borderWidth / offset);
    } else if (percentStyle == PercentStyle_Arc_Polo) {
        drawArc(&painter, radius - borderWidth / offset);
        drawPolo(&painter, radius - borderWidth - borderWidth);
    } else if (percentStyle == PercentStyle_Arc_Wave) {
        drawArc(&painter, radius - borderWidth / offset);
        drawWave(&painter, radius - borderWidth - borderWidth);
    }

    //绘制当前值
    drawValue(&painter, radius);
}

void ProgressPercent::drawCircle(QPainter *painter, int radius)
{
    if (borderOut) {
        if (percentStyle == PercentStyle_Arc) {
            radius = radius - borderWidth * 1.5;
        } else if (percentStyle == PercentStyle_Arc_Polo || percentStyle == PercentStyle_Arc_Wave) {
            radius = radius - borderWidth * 2;
        }
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(circleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressPercent::drawArc(QPainter *painter, int radius)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen;
    pen.setWidthF(borderWidth);

    //这里可以更改画笔样式更换线条风格
    //pen.setCapStyle(Qt::RoundCap);

    double arcLength = 360.0 / (maxValue - minValue) * (value - minValue);
    QRect rect(-radius, -radius, radius * 2, radius * 2);

    //逆时针为顺时针分负数
    if (!clockWise) {
        arcLength = -arcLength;
    }

    //绘制剩余进度圆弧
    if (showFree) {
        pen.setColor(freeColor);
        painter->setPen(pen);
        painter->drawArc(rect, (nullPosition - arcLength) * 16, -(360 - arcLength) * 16);
    }

    //绘制当前进度圆弧
    pen.setColor(usedColor);
    painter->setPen(pen);
    painter->drawArc(rect, nullPosition * 16, -arcLength * 16);

    //绘制进度圆弧前面的小圆
    if (showSmallCircle) {
        int offset = radius - borderWidth + 1;
        radius = borderWidth / 2 - 1;
        painter->rotate(-nullPosition - 90);

        QRect circleRect(-radius, radius + offset, radius * 2, radius * 2);
        painter->rotate(arcLength);
        painter->drawEllipse(circleRect);
    }

    painter->restore();
}

void ProgressPercent::drawPolo(QPainter *painter, int radius)
{
    painter->save();

    //计算当前值所占百分比对应高度
    double percentHeight = (double)radius / (maxValue - minValue) * (value - minValue);

    //大圆路径
    QPainterPath bigPath;
    bigPath.addEllipse(-radius, -radius, radius * 2, radius * 2);

    //底部水池灌水所占的矩形区域路径
    QPainterPath smallPath;
    smallPath.addRect(-radius, radius - percentHeight * 2, radius * 2, percentHeight * 2);

    //将两个路径重合相交部分提取,就是水池注水所占面积
    QPainterPath path;
    path = bigPath.intersected(smallPath);

    painter->setPen(usedColor);
    painter->setBrush(usedColor);
    painter->drawPath(path);

    painter->restore();
}

void ProgressPercent::drawWave(QPainter *painter, int radius)
{
    //起始坐标和结束坐标
    int startX = - radius;
    int startY = - radius;
    int endX = radius;
    int endY = radius;
    int side = radius * 2;

    //计算当前值所占百分比
    double percent = 1 - (double)(value - minValue) / (maxValue - minValue);

    //正弦曲线公式 y = A * qSin(ωx + φ) + k

    //w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度
    double w = waterDensity * M_PI / endX;

    //A表示振幅,可以理解为水波的高度,值越大高度越高(越浪 ^_^),取值高度的百分比
    double A = endY * waterHeight;

    //k表示y轴偏移,可以理解为进度,取值高度的进度百分比
    double k = endY * percent;

    //圆形的区域要重新计算
    k = (side * percent) + startY;

    //第一条波浪路径集合
    QPainterPath waterPath1;
    //第二条波浪路径集合
    QPainterPath waterPath2;

    //移动到左上角起始点
    waterPath1.moveTo(startX, endY);
    waterPath2.moveTo(startX, endY);

    offset += 0.6;
    if (offset > (endX / 2)) {
        offset = 0;
    }

    for(int x = startX; x <= endX; x++) {
        //第一条波浪Y轴
        double waterY1 = (double)(A * qSin(w * x + offset)) + k;
        //第二条波浪Y轴
        double waterY2 = (double)(A * qSin(w * x + offset + (endX / 2 * w))) + k;

        //如果当前值为最小值则Y轴为右下角Y轴
        if (this->value == minValue) {
            waterY1 = endY;
            waterY2 = endY;
        }

        //如果当前值为最大值则Y轴为右上角Y轴
        if (this->value == maxValue) {
            waterY1 = startY;
            waterY2 = startY;
        }

        //将两个点连接成线
        waterPath1.lineTo(x, waterY1);
        waterPath2.lineTo(x, waterY2);
    }

    //移动到右下角结束点,整体形成一个闭合路径
    waterPath1.lineTo(endX, endY);
    waterPath2.lineTo(endX, endY);

    //大路径
    QPainterPath bigPath;
    bigPath.addEllipse(startX, startY, side, side);

    //新路径,用大路径减去波浪区域的路径,形成遮罩效果
    QPainterPath path;
    QColor waterColor1 = usedColor;
    waterColor1.setAlpha(100);
    QColor waterColor2 = usedColor;
    waterColor2.setAlpha(200);

    painter->save();
    painter->setPen(Qt::NoPen);

    //第一条波浪挖去后的路径
    path = bigPath.intersected(waterPath1);
    painter->setBrush(waterColor1);
    painter->drawPath(path);

    //第二条波浪挖去后的路径
    path = bigPath.intersected(waterPath2);
    painter->setBrush(waterColor2);
    painter->drawPath(path);

    painter->restore();
}

void ProgressPercent::drawValue(QPainter *painter, int radius)
{
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(showPercent ? 65 : 75);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg(value);

    if (showPercent) {
        strValue = QString("%1%").arg((double)(value - minValue) / (maxValue - minValue) * 100);
    }

    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

int ProgressPercent::getMinValue() const
{
    return this->minValue;
}

int ProgressPercent::getMaxValue() const
{
    return this->maxValue;
}

int ProgressPercent::getValue() const
{
    return this->value;
}

int ProgressPercent::getNullPosition() const
{
    return this->nullPosition;
}

int ProgressPercent::getBorderWidth() const
{
    return this->borderWidth;
}

double ProgressPercent::getWaterHeight() const
{
    return this->waterHeight;
}

double ProgressPercent::getWaterDensity() const
{
    return this->waterDensity;
}

bool ProgressPercent::getShowPercent() const
{
    return this->showPercent;
}

bool ProgressPercent::getShowFree() const
{
    return this->showFree;
}

bool ProgressPercent::getShowSmallCircle() const
{
    return this->showSmallCircle;
}

bool ProgressPercent::getClockWise() const
{
    return this->clockWise;
}

bool ProgressPercent::getBorderOut() const
{
    return this->borderOut;
}

QColor ProgressPercent::getUsedColor() const
{
    return this->usedColor;
}

QColor ProgressPercent::getFreeColor() const
{
    return this->freeColor;
}

QColor ProgressPercent::getCircleColor() const
{
    return this->circleColor;
}

QColor ProgressPercent::getTextColor() const
{
    return this->textColor;
}

ProgressPercent::PercentStyle ProgressPercent::getPercentStyle() const
{
    return this->percentStyle;
}

QSize ProgressPercent::sizeHint() const
{
    return QSize(200, 200);
}

QSize ProgressPercent::minimumSizeHint() const
{
    return QSize(10, 10);
}

void ProgressPercent::setRange(int minValue, int maxValue)
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

void ProgressPercent::setMinValue(int minValue)
{
    setRange(minValue, maxValue);
}

void ProgressPercent::setMaxValue(int maxValue)
{
    setRange(minValue, maxValue);
}

void ProgressPercent::setValue(int value)
{
    //值小于最小值或者值大于最大值或者值和当前值一致则无需处理
    if (value < minValue || value > maxValue || value == this->value) {
        return;
    }

    this->value = value;
    update();
    emit valueChanged(value);

    if (this->percentStyle == PercentStyle_Wave || this->percentStyle == PercentStyle_Arc_Wave) {
        //如果当前值为最小值或者最大值则停止浪,不要再浪了 ^_^
        if (this->value == minValue || this->value == maxValue) {
            if (timer->isActive()) {
                timer->stop();
            }
        } else {
            if (!timer->isActive()) {
                timer->start();
            }
        }
    } else {
        if (timer->isActive()) {
            timer->stop();
        }
    }
}

void ProgressPercent::setNullPosition(int nullPosition)
{
    if (this->nullPosition != nullPosition) {
        this->nullPosition = nullPosition;
        update();
    }
}

void ProgressPercent::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        update();
    }
}

void ProgressPercent::setWaterHeight(double waterHeight)
{
    if (waterHeight > 0.1) {
        return;
    }

    if (this->waterHeight != waterHeight) {
        this->waterHeight = waterHeight;
        update();
    }
}

void ProgressPercent::setWaterDensity(double waterDensity)
{
    if (this->waterDensity != waterDensity) {
        this->waterDensity = waterDensity;
        update();
    }
}

void ProgressPercent::setShowPercent(bool showPercent)
{
    if (this->showPercent != showPercent) {
        this->showPercent = showPercent;
        update();
    }
}

void ProgressPercent::setShowFree(bool showFree)
{
    if (this->showFree != showFree) {
        this->showFree = showFree;
        update();
    }
}

void ProgressPercent::setShowSmallCircle(bool showSmallCircle)
{
    if (this->showSmallCircle != showSmallCircle) {
        this->showSmallCircle = showSmallCircle;
        update();
    }
}

void ProgressPercent::setClockWise(bool clockWise)
{
    if (this->clockWise != clockWise) {
        this->clockWise = clockWise;
        update();
    }
}

void ProgressPercent::setBorderOut(bool borderOut)
{
    if (this->borderOut != borderOut) {
        this->borderOut = borderOut;
        update();
    }
}

void ProgressPercent::setUsedColor(const QColor &usedColor)
{
    if (this->usedColor != usedColor) {
        this->usedColor = usedColor;
        update();
    }
}

void ProgressPercent::setFreeColor(const QColor &freeColor)
{
    if (this->freeColor != freeColor) {
        this->freeColor = freeColor;
        update();
    }
}

void ProgressPercent::setCircleColor(const QColor &circleColor)
{
    if (this->circleColor != circleColor) {
        this->circleColor = circleColor;
        update();
    }
}

void ProgressPercent::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void ProgressPercent::setPercentStyle(const ProgressPercent::PercentStyle &percentStyle)
{
    if (this->percentStyle != percentStyle) {
        this->percentStyle = percentStyle;
        update();

        if (this->percentStyle == PercentStyle_Wave || this->percentStyle == PercentStyle_Arc_Wave) {
            if (!timer->isActive()) {
                timer->start();
            }
        }
    }
}
