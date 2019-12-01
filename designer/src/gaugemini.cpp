#pragma execution_character_set("utf-8")

#include "gaugemini.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmath.h"
#include "qdebug.h"

GaugeMini::GaugeMini(QWidget *parent) : QWidget(parent)
{
    minValue = -100.0;
    maxValue = 100.0;
    value = 0;
    precision = 1;

    step = 20;
    startAngle = 45;
    endAngle = 45;

    borderColor = QColor(0, 0, 0);
    bgColor = QColor(50, 50, 50);
    textColor = QColor(0, 0, 0);
    percentColor = QColor(100, 184, 255);

    doublePercent = true;
    showValue = false;
    pointerStyle = PointerStyle_Line;

    setFont(QFont("Arial", 9));
}

GaugeMini::~GaugeMini()
{

}

void GaugeMini::mousePressEvent(QMouseEvent *e)
{
    pressed = true;
    setPressedValue(e->pos());
}

void GaugeMini::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
}

void GaugeMini::mouseMoveEvent(QMouseEvent *e)
{
    if (pressed) {
        setPressedValue(e->pos());
    }
}

void GaugeMini::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制刻度线
    drawScale(&painter);
    //绘制背景圆
    drawBgCircle(&painter);
    //绘制中心圆
    drawCenterCircle(&painter);

    //根据指示器形状绘制指示器
    if (pointerStyle == PointerStyle_Line) {
        drawPointerLine(&painter);
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

void GaugeMini::drawScale(QPainter *painter)
{
    int radius = 96;
    int offset = 10;
    painter->save();

    painter->rotate(startAngle);
    double angleStep = (360.0 - startAngle - endAngle) / step;
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);

    QPen pen;
    pen.setWidthF(5.0);
    pen.setCapStyle(Qt::RoundCap);

    double rotate = 0;
    for (int i = 0; i <= step; i++) {
        if (doublePercent) {
            bool right = i >= (step / 2);
            if (!right) {
                pen.setColor((rotate < degRotate) ? textColor : percentColor);
            } else {
                pen.setColor((rotate <= degRotate) ? percentColor : textColor);
            }

            //矫正左侧值为最小值时第一格颜色
            if (value == minValue && !right) {
                pen.setColor(percentColor);
            }

            //矫正左侧值时中间格颜色
            if (value <= ((maxValue - minValue) / 2 + minValue) && i == (step / 2)) {
                pen.setColor(percentColor);
            }

            //矫正中间值中间格颜色
            if (value == ((maxValue - minValue) / 2 + minValue)) {
                pen.setColor(textColor);
            }
        } else {
            if (rotate <= degRotate) {
                pen.setColor(percentColor);
            } else {
                pen.setColor(textColor);
            }

            //矫正左侧值为最小值时第一格颜色
            if (value == minValue) {
                pen.setColor(textColor);
            }
        }

        painter->setPen(pen);
        painter->drawLine(0, radius - offset, 0, radius);
        painter->rotate(angleStep);
        rotate += angleStep;
    }

    painter->restore();
}

void GaugeMini::drawBgCircle(QPainter *painter)
{
    int radius = 75;
    painter->save();

    QPen pen;
    pen.setWidthF(5.0);
    pen.setColor(borderColor);

    painter->setPen(pen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void GaugeMini::drawCenterCircle(QPainter *painter)
{
    int radius = 15;
    painter->save();

    QColor color = percentColor;
    if (doublePercent) {
        bool center = (value == (maxValue - minValue) / 2 + minValue);
        color = center ? borderColor : percentColor;
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void GaugeMini::drawPointerLine(QPainter *painter)
{
    int radius = 62;
    painter->save();

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);

    QColor color = percentColor;
    if (doublePercent) {
        bool center = (value == (maxValue - minValue) / 2 + minValue);
        color = center ? borderColor : percentColor;
    }

    painter->setPen(QPen(color, 10, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void GaugeMini::drawPointerIndicator(QPainter *painter)
{
    int radius = 65;
    int offset = 8;
    painter->save();
    painter->setOpacity(0.8);

    QPolygon pts;
    pts.setPoints(3, -offset, 0, offset, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);

    QColor color = percentColor;
    if (doublePercent) {
        bool center = (value == (maxValue - minValue) / 2 + minValue);
        color = center ? borderColor : percentColor;
    }

    painter->setPen(color);
    painter->setBrush(color);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeMini::drawPointerIndicatorR(QPainter *painter)
{
    int radius = 62;
    int offset = 8;
    painter->save();
    painter->setOpacity(0.6);

    QPolygon pts;
    pts.setPoints(3, -offset, 0, offset, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);

    QColor color = percentColor;
    if (doublePercent) {
        bool center = (value == (maxValue - minValue) / 2 + minValue);
        color = center ? borderColor : percentColor;
    }

    QPen pen;
    pen.setColor(color);
    painter->setPen(pen);
    painter->setBrush(color);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(offset - 1);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void GaugeMini::drawPointerTriangle(QPainter *painter)
{
    int radius = 25;
    int offset = 40;
    painter->save();

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);

    QColor color = percentColor;
    if (doublePercent) {
        bool center = (value == (maxValue - minValue) / 2 + minValue);
        color = center ? borderColor : percentColor;
    }

    painter->setPen(color);
    painter->setBrush(color);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeMini::drawValue(QPainter *painter)
{
    if (!showValue) {
        return;
    }

    int radius = 100;
    painter->save();

    QString strValue = QString::number(value, 'f', precision);
    painter->setPen(Qt::white);
    QFont font;

#if 0
    font.setPixelSize(radius * 0.5);
    painter->setFont(font);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, strValue);
#else
    font.setPixelSize(radius * 0.3);
    painter->setFont(font);
    QRect rect(-radius, -radius, radius * 2, radius * 1.65);
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignBottom, strValue);
#endif

    painter->restore();
}

void GaugeMini::setPressedValue(QPointF pressedPoint)
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

double GaugeMini::getMinValue() const
{
    return this->minValue;
}

double GaugeMini::getMaxValue() const
{
    return this->maxValue;
}

double GaugeMini::getValue() const
{
    return this->value;
}

int GaugeMini::getPrecision() const
{
    return this->precision;
}

int GaugeMini::getStep() const
{
    return this->step;
}

int GaugeMini::getStartAngle() const
{
    return this->startAngle;
}

int GaugeMini::getEndAngle() const
{
    return this->endAngle;
}

QColor GaugeMini::getBorderColor() const
{
    return this->borderColor;
}

QColor GaugeMini::getBgColor() const
{
    return this->bgColor;
}

QColor GaugeMini::getTextColor() const
{
    return this->textColor;
}

QColor GaugeMini::getPercentColor() const
{
    return this->percentColor;
}

bool GaugeMini::getDoublePercent() const
{
    return this->doublePercent;
}

bool GaugeMini::getShowValue() const
{
    return this->showValue;
}

GaugeMini::PointerStyle GaugeMini::getPointerStyle() const
{
    return this->pointerStyle;
}

QSize GaugeMini::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeMini::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeMini::setRange(double minValue, double maxValue)
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

void GaugeMini::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeMini::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeMini::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeMini::setValue(double value)
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

void GaugeMini::setValue(int value)
{
    setValue((double)value);
}

void GaugeMini::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeMini::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
        update();
    }
}

void GaugeMini::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeMini::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeMini::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        update();
    }
}

void GaugeMini::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void GaugeMini::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeMini::setPercentColor(const QColor &percentColor)
{
    if (this->percentColor != percentColor) {
        this->percentColor = percentColor;
        update();
    }
}

void GaugeMini::setDoublePercent(bool doublePercent)
{
    if (this->doublePercent != doublePercent) {
        this->doublePercent = doublePercent;
        update();
    }
}

void GaugeMini::setShowValue(bool showValue)
{
    if (this->showValue != showValue) {
        this->showValue = showValue;
        update();
    }
}

void GaugeMini::setPointerStyle(const GaugeMini::PointerStyle &pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        update();
    }
}
