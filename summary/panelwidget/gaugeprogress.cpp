#pragma execution_character_set("utf-8")

#include "gaugeprogress.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmath.h"
#include "qpropertyanimation.h"
#include "qdatetime.h"
#include "qdebug.h"

GaugeProgress::GaugeProgress(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    startAngle = 0;
    endAngle = 0;

    bgColor = QColor(30, 30, 30);
    progressColor = QColor(100, 184, 255);
    progressBgColor = QColor(50, 50, 50);
    circleColorStart = QColor(80, 80, 80);
    circleColorEnd = QColor(50, 50, 50);
    textColor = QColor(200, 200, 200);

    showPointer = true;
    showValue = false;
    pointerStyle = PointerStyle_Circle;

    hover = false;
    radiusCoverCircle = 85;
    radiusCircle = 80;

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    animation = new QPropertyAnimation(this, "");
    animation->setStartValue(0);
    animation->setEndValue(10);
    animation->setDuration(300);
    connect(animation, SIGNAL(valueChanged(QVariant)), this, SLOT(updateRadius(QVariant)));

    setFont(QFont("Arial", 9));
}

GaugeProgress::~GaugeProgress()
{

}

void GaugeProgress::enterEvent(QEvent *)
{
    hover = true;
    animation->stop();
    animation->start();
}

void GaugeProgress::leaveEvent(QEvent *)
{
    hover = false;
    animation->stop();
    animation->start();
}

void GaugeProgress::mousePressEvent(QMouseEvent *e)
{
    pressed = true;
    setPressedValue(e->pos());
}

void GaugeProgress::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
}

void GaugeProgress::mouseMoveEvent(QMouseEvent *e)
{
    if (pressed) {
        setPressedValue(e->pos());
    }
}

void GaugeProgress::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景
    drawBg(&painter);
    //绘制饼圆
    drawColorPie(&painter);
    //绘制覆盖圆 用以遮住饼圆多余部分
    drawCoverCircle(&painter);
    //绘制中心圆
    drawCircle(&painter);

    //根据指示器形状绘制指示器
    if (pointerStyle == PointerStyle_Circle) {
        drawPointerCircle(&painter);
    } else if (pointerStyle == PointerStyle_Indicator) {
        drawPointerIndicator(&painter);
    } else if (pointerStyle == PointerStyle_IndicatorR) {
        drawPointerIndicatorR(&painter);
    } else if (pointerStyle == PointerStyle_Triangle) {
        drawPointerTriangle(&painter);
    }

    //绘制当前值
    drawValue(&painter);
}

void GaugeProgress::drawBg(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeProgress::drawColorPie(QPainter *painter)
{
    int radius = 95;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleCurrent = angleAll * ((value - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;

    //绘制当前值饼圆
    painter->setBrush(progressColor);
    painter->drawPie(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余值饼圆
    painter->setBrush(progressBgColor);
    painter->drawPie(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void GaugeProgress::drawCoverCircle(QPainter *painter)
{
    int radius = radiusCoverCircle;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeProgress::drawCircle(QPainter *painter)
{
    int radius = radiusCircle;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, circleColorStart);
    bgGradient.setColorAt(1.0, circleColorEnd);
    painter->setBrush(bgGradient);

    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeProgress::drawPointerCircle(QPainter *painter)
{
    if (!showPointer) {
        return;
    }

    int radius = 15;
    int offset = radiusCircle - 60;
    painter->save();
    painter->setPen(Qt::NoPen);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);

    painter->setBrush(progressColor);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void GaugeProgress::drawPointerIndicator(QPainter *painter)
{
    if (!showPointer) {
        return;
    }

    int radius = radiusCircle - 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(progressColor);

    QPolygon pts;
    pts.setPoints(3, -8, 0, 8, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //绘制中心圆点
    radius = radius / 4;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void GaugeProgress::drawPointerIndicatorR(QPainter *painter)
{
    if (!showPointer) {
        return;
    }

    int radius = radiusCircle - 15;
    painter->save();

    QPen pen;
    pen.setWidth(1);
    pen.setColor(progressColor);
    painter->setPen(pen);
    painter->setBrush(progressColor);

    QPolygon pts;
    pts.setPoints(3, -8, 0, 8, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    //绘制中心圆点
    radius = radius / 4;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void GaugeProgress::drawPointerTriangle(QPainter *painter)
{
    if (!showPointer) {
        return;
    }

    int radius = 20;
    int offset = radiusCircle - 25;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(progressColor);

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeProgress::drawValue(QPainter *painter)
{
    if (!showValue) {
        return;
    }

    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(showPointer ? radius - 50 : radius - 15);
    font.setBold(true);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)value, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->restore();
}

void GaugeProgress::setEasingCurve()
{
    //随机选择一种动画效果
    int index = qrand() % 40;
    animation->setEasingCurve((QEasingCurve::Type)index);
}

void GaugeProgress::updateRadius(QVariant radius)
{
    //如果鼠标悬停则逐渐变小,鼠标移开则逐渐变大直到恢复
    int step = radius.toInt();

    if (hover) {
        radiusCoverCircle = 85 - step;
        radiusCircle = 80 - step;
    } else {
        radiusCoverCircle = 75 + step;
        radiusCircle = 70 + step;
    }

    update();
}

void GaugeProgress::setPressedValue(QPointF pressedPoint)
{
    //计算总角度
    double length = 360 - startAngle - endAngle;

    //计算最近的刻度
    QPointF point = pressedPoint - rect().center();
    double theta = -atan2(-point.x(), -point.y()) * 180 / M_PI;
    theta = theta + length / 2;

    //计算每一个角度对应值移动多少
    double increment = (maxValue - minValue) / length;
    double currentValue = (theta * increment) + minValue;

    //过滤圆弧外的值
    if (currentValue <= minValue) {
        currentValue = minValue;
    } else if (currentValue >= maxValue) {
        currentValue = maxValue;
    }

    setValue(currentValue);
}

double GaugeProgress::getMinValue() const
{
    return this->minValue;
}

double GaugeProgress::getMaxValue() const
{
    return this->maxValue;
}

double GaugeProgress::getValue() const
{
    return this->value;
}

int GaugeProgress::getPrecision() const
{
    return this->precision;
}

int GaugeProgress::getStartAngle() const
{
    return this->startAngle;
}

int GaugeProgress::getEndAngle() const
{
    return this->endAngle;
}

QColor GaugeProgress::getBgColor() const
{
    return this->bgColor;
}

QColor GaugeProgress::getProgressColor() const
{
    return this->progressColor;
}

QColor GaugeProgress::getProgressBgColor() const
{
    return this->progressBgColor;
}

QColor GaugeProgress::getCircleColorStart() const
{
    return this->circleColorStart;
}

QColor GaugeProgress::getCircleColorEnd() const
{
    return this->circleColorEnd;
}

QColor GaugeProgress::getTextColor() const
{
    return this->textColor;
}

bool GaugeProgress::getShowPointer() const
{
    return this->showPointer;
}

bool GaugeProgress::getShowValue() const
{
    return this->showValue;
}

GaugeProgress::PointerStyle GaugeProgress::getPointerStyle() const
{
    return this->pointerStyle;
}

QSize GaugeProgress::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeProgress::minimumSizeHint() const
{
    return QSize(20, 20);
}

void GaugeProgress::setRange(double minValue, double maxValue)
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

void GaugeProgress::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeProgress::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeProgress::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeProgress::setValue(double value)
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

void GaugeProgress::setValue(int value)
{
    setValue((double)value);
}

void GaugeProgress::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeProgress::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeProgress::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeProgress::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void GaugeProgress::setProgressColor(const QColor &progressColor)
{
    if (this->progressColor != progressColor) {
        this->progressColor = progressColor;
        update();
    }
}

void GaugeProgress::setProgressBgColor(const QColor &progressBgColor)
{
    if (this->progressBgColor != progressBgColor) {
        this->progressBgColor = progressBgColor;
        update();
    }
}

void GaugeProgress::setCircleColorStart(const QColor &circleColorStart)
{
    if (this->circleColorStart != circleColorStart) {
        this->circleColorStart = circleColorStart;
        update();
    }
}

void GaugeProgress::setCircleColorEnd(const QColor &circleColorEnd)
{
    if (this->circleColorEnd != circleColorEnd) {
        this->circleColorEnd = circleColorEnd;
        update();
    }
}

void GaugeProgress::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeProgress::setShowPointer(bool showPointer)
{
    if (this->showPointer != showPointer) {
        this->showPointer = showPointer;
        update();
    }
}

void GaugeProgress::setShowValue(bool showValue)
{
    if (this->showValue != showValue) {
        this->showValue = showValue;
        update();
    }
}

void GaugeProgress::setPointerStyle(const GaugeProgress::PointerStyle &pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        update();
    }
}
