#pragma execution_character_set("utf-8")

#include "rulerscale.h"
#include "qpainter.h"
#include "qmath.h"
#include "qdebug.h"

RulerScale::RulerScale(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    borderWidth = 6;
    scaleMajor = 0;
    scaleMinor = 0;

    scaleColor = QColor(20, 20, 20);
    scaleNumColor = QColor(0, 0, 0);
    pointerColor = QColor(80, 80, 80);
    borderColor = QColor(120, 120, 120);
    coverColor = QColor(120, 120, 120);
    textColor = QColor(250, 250, 250);

    orientation = (Qt::Horizontal | Qt::Vertical);
}

RulerScale::~RulerScale()
{

}

void RulerScale::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //如果设置了方向则以设置的方向绘制,没有则自动根据宽高调整
    bool vertical = (height > width);
    if(!(orientation & Qt::Vertical) ^ !(orientation & Qt::Horizontal)) {
        vertical = (bool)(orientation & Qt::Vertical);
    }

    double margin = qMax(fabs((double)minValue), fabs((double)maxValue));
    double wildcard = (qMin(minValue, maxValue) < 0) ? -8 : 8;
    while(margin < 1) {
        margin *= 10;
        wildcard /= 10;
    }
    while(margin >= 10) {
        margin /= 10;
        wildcard *= 10;
    }

    QString labelSample = QString::number(wildcard);
    QRectF boundingRect = painter.boundingRect(QRectF(0, 0, width, height), Qt::AlignBottom | Qt::AlignHCenter, labelSample);
    double wLabel = boundingRect.width();
    double hLabel = boundingRect.height();

    //窗体宽高互换
    int wWidget = width;
    int hWidget = height;
    if(vertical) {
        qSwap(wWidget, hWidget);
        qSwap(wLabel, hLabel);
    }

    double wScale = wWidget - wLabel - 2 * borderWidth;
    double hScale = 0.5 * hWidget - hLabel - borderWidth;
    double radius = 0.125 * qPow(wScale, 2) / hScale + 0.5 * hScale;

    //计算中心点坐标
    QPointF center;
    if(radius < hScale + 0.5 * hWidget - borderWidth) {
        radius = (4 * (hLabel + borderWidth) + qSqrt(4 * qPow(hLabel + borderWidth, 2) + 3 * qPow(wScale, 2))) / 3 - hLabel - 2 * borderWidth;
        center = QPointF(0.5 * wWidget, hWidget - borderWidth);
    } else {
        center = QPointF(0.5 * wWidget, radius + hLabel + borderWidth);
    }

    double angleSpan = - 360 / qAcos(-1) * qAsin(wScale / (2 * radius));
    double angleStart = 90 - 0.5 * angleSpan;
    double valueSpan = maxValue - minValue;
    double majorStep = fabs(valueSpan) * qMax(wLabel, 1.5 * boundingRect.height()) / wScale;
    int minorSteps = 0;
    int order = 0;

    //自动根据宽高计算刻度尺数量
    while(majorStep < 1) {
        majorStep *= 10;
        order--;
    }

    while(majorStep >= 10) {
        majorStep /= 10;
        order++;
    }

    if(majorStep > 5) {
        majorStep = 10 * qPow(10.0, order);
        minorSteps = 5;
    } else if(majorStep > 2) {
        majorStep = 5 * qPow(10.0, order);
        minorSteps = 5;
    } else {
        majorStep = 2 * qPow(10.0, order);
        minorSteps = 4;
    }

    //如果设置了刻度尺数量则以设置为准
    if(scaleMajor > 0) {
        majorStep = scaleMajor;
    }

    if(scaleMinor > 0) {
        minorSteps = scaleMinor;
    }

    //如果是纵向则先旋转90度,并移动坐标中心点
    if(vertical) {
        painter.rotate(90);
        painter.translate(0, -hWidget + wLabel / 4);
    }

    painter.translate(center);
    painter.rotate(fmod(minValue, majorStep / minorSteps) / valueSpan * angleSpan - angleStart);

    int offsetCount = (minorSteps - (int)qCeil(fmod(minValue, majorStep) / majorStep * minorSteps)) % minorSteps;
    double scaleWidth = qMin(qMin(0.25 * (hWidget - borderWidth), 0.25 * radius), 2.5 * boundingRect.height());

    //设置刻度尺颜色
    QPen pen;
    pen.setColor(scaleColor);
    pen.setCapStyle(Qt::RoundCap);

    //逐个绘制大刻度小刻度
    for(int i = 0; i <= (int)(minorSteps * valueSpan / majorStep); i++) {
        if(i % minorSteps == offsetCount) {
            pen.setWidthF(1.5);
            painter.setPen(pen);
            painter.drawLine(QLineF(radius - scaleWidth, 0, radius, 0));
        } else {
            pen.setWidthF(1.0);
            painter.setPen(pen);
            painter.drawLine(QLineF(radius - scaleWidth, 0, radius - scaleWidth * 0.4, 0));
        }

        painter.rotate(majorStep * angleSpan / (-valueSpan * minorSteps));
    }

    //重置坐标系
    painter.resetMatrix();

    //设置刻度值颜色
    pen.setColor(scaleNumColor);
    painter.setPen(pen);

    //逐个绘制刻度值
    QRect position;
    Qt::Alignment align;
    for(int i = (int)qCeil(minValue / majorStep); i <= (int)(maxValue / majorStep); i++) {
        double temp = qAcos(-1) / 180 * ((majorStep * i - minValue) / valueSpan * angleSpan + angleStart);
        if(vertical) {
            align = Qt::AlignLeft | Qt::AlignVCenter;
            position = QRect(width - center.y() + radius * qSin(temp), 0, width, height + 2 * radius * qCos(temp));
        } else {
            align = Qt::AlignHCenter | Qt::AlignBottom;
            position = QRect(0, 0, 2 * (center.x() + radius * qCos(temp)), center.y() - radius * qSin(temp));
        }

        painter.drawText(position, align, QString::number(i * majorStep));
    }

    //如果是纵向则先旋转90度,并移动坐标中心点
    if(vertical) {
        painter.rotate(90);
        painter.translate(0, -hWidget + wLabel / 4);
    }

    //绘制指针
    painter.setPen(pointerColor);
    painter.setBrush(pointerColor);

    QPolygon polygon;
    polygon.setPoints(5, 0, -2, (int)radius - 10, -2, (int)radius, 0, (int)radius - 10, 2, 0, 2);

    painter.translate(center);
    painter.rotate((minValue - value) / valueSpan * angleSpan - angleStart);
    painter.drawConvexPolygon(polygon);

    //重置坐标系
    painter.resetMatrix();

    //绘制边框矩形
    painter.setPen(Qt::NoPen);
    painter.setBrush(borderColor);
    double temp;
    if(vertical) {
        painter.drawRect(QRect(0, 0, borderWidth, height));
        center = QPointF(width - center.y() - wLabel / 4, 0.5 * height);
        temp = 0.25 * (hWidget - wLabel) - center.x() - borderWidth;
    } else {
        painter.drawRect(QRect(0, hWidget, wWidget, -borderWidth));
        temp = center.y() - borderWidth - 0.75 * hWidget;
    }

    //绘制椭圆盖子
    painter.setBrush(coverColor);
    temp = qMax(temp, 0.25 * radius);
    painter.drawEllipse(center, temp, temp);

    //绘制当前值
    QFont font;
    font.setPixelSize(20);
    painter.setFont(font);
    painter.setPen(textColor);
    QRect textRect = vertical ? QRect(0, 0, width / 5, height) : QRect(0, hWidget, wWidget, -height / 5);
    QString strValue = QString::number(value);
    painter.drawText(textRect, Qt::AlignCenter, strValue);
}

int RulerScale::getMinValue() const
{
    return this->minValue;
}

int RulerScale::getMaxValue() const
{
    return this->maxValue;
}

int RulerScale::getValue() const
{
    return this->value;
}

int RulerScale::getBorderWidth() const
{
    return this->borderWidth;
}

int RulerScale::getScaleMajor() const
{
    return this->scaleMajor;
}

int RulerScale::getScaleMinor() const
{
    return this->scaleMinor;
}

QColor RulerScale::getScaleColor() const
{
    return this->scaleColor;
}

QColor RulerScale::getScaleNumColor() const
{
    return this->scaleNumColor;
}

QColor RulerScale::getPointerColor() const
{
    return this->pointerColor;
}

QColor RulerScale::getBorderColor() const
{
    return this->borderColor;
}

QColor RulerScale::getCoverColor() const
{
    return this->coverColor;
}

QColor RulerScale::getTextColor() const
{
    return this->textColor;
}

Qt::Orientations RulerScale::getOrientation() const
{
    return this->orientation;
}

QSize RulerScale::sizeHint() const
{
    return QSize(200, 60);
}

QSize RulerScale::minimumSizeHint() const
{
    return QSize(80, 60);
}

void RulerScale::setRange(int minValue, int maxValue)
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

void RulerScale::setMinValue(int minValue)
{
    setRange(minValue, maxValue);
}

void RulerScale::setMaxValue(int maxValue)
{
    setRange(minValue, maxValue);
}

void RulerScale::setValue(int value)
{
    //值小于最小值或者值大于最大值或者值和当前值一致则无需处理
    if (value < minValue || value > maxValue || value == this->value) {
        return;
    }

    this->value = value;
    update();

    emit valueChanged(value);
}

void RulerScale::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        update();
    }
}

void RulerScale::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void RulerScale::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void RulerScale::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void RulerScale::setScaleNumColor(const QColor &scaleNumColor)
{
    if (this->scaleNumColor != scaleNumColor) {
        this->scaleNumColor = scaleNumColor;
        update();
    }
}

void RulerScale::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        update();
    }
}

void RulerScale::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        update();
    }
}

void RulerScale::setCoverColor(const QColor &coverColor)
{
    if (this->coverColor != coverColor) {
        this->coverColor = coverColor;
        update();
    }
}

void RulerScale::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void RulerScale::setOrientation(const Qt::Orientations &orientation)
{
    if (this->orientation != orientation) {
        this->orientation = orientation;
        update();
    }
}
