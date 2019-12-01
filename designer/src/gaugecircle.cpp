#pragma execution_character_set("utf-8")

#include "gaugecircle.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeCircle::GaugeCircle(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    scaleMajor = 10;
    scaleMinor = 5;
    startAngle = 0;
    endAngle = 0;

    animation = false;
    animationStep = 1.1;

    usedColor = QColor(100, 184, 255);
    freeColor = QColor(100, 100, 100);

    scaleColor = QColor(50, 50, 50);
    pointerColor = QColor(255, 107, 107);
    textColor = QColor(250, 250, 250);
    titleColor = QColor(50, 50, 50);

    showOverlay = false;
    overlayColor = QColor(70, 70, 70, 60);

    pointerStyle = PointerStyle_Triangle;

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    offsetY = 17;
    radiusY = 20;

    setFont(QFont("Arial", 8));
}

GaugeCircle::~GaugeCircle()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void GaugeCircle::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    //直径取最大值的一半
    int side = qMax(width, height) / 2;

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2.0, height / 1.0);
    painter.scale(side / 100.0, side / 100.0);

    //绘制当前值及剩余值圆弧
    drawArc(&painter);

    //绘制刻度线
    drawScale(&painter);
    //绘制刻度值
    drawScaleNum(&painter);

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

    //绘制指针中心圆外边框
    drawRoundCircle(&painter);
    //绘制指针中心圆
    drawCenterCircle(&painter);
    //绘制当前值
    drawValue(&painter);
    //绘制遮罩层
    drawOverlay(&painter);
}

void GaugeCircle::drawArc(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //绘制圆弧方法绘制圆环
    int penWidth = 10;
    QRectF rect(-radius + penWidth / 2, -radius + penWidth / 2, radius * 2 - penWidth, radius * 2 - penWidth);
    //可以自行修改画笔的后三个参数,形成各种各样的效果,例如Qt::FlatCap改为Qt::FlatCap可以产生圆角效果
    QPen pen(usedColor, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 180.0 - startAngle - endAngle;
    double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;

    //绘制当前值饼圆
    painter->setPen(pen);
    painter->drawArc(rect, (180 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余值饼圆
    pen.setColor(freeColor);
    painter->setPen(pen);
    painter->drawArc(rect, (180 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void GaugeCircle::drawScale(QPainter *painter)
{
    int radius = 67;
    painter->save();

    painter->rotate(startAngle + 90);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (180.0 - startAngle - endAngle) / steps;

    QPen pen;
    pen.setColor(scaleColor);
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 10, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeCircle::drawScaleNum(QPainter *painter)
{
    int radius = 76;
    painter->save();
    painter->setPen(scaleColor);

    double startRad = (180 - startAngle) * (M_PI / 180);
    double deltaRad = (180 - startAngle - endAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString strValue = QString("%1").arg(value);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height() - offsetY;
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void GaugeCircle::drawPointerCircle(QPainter *painter)
{
    int radius = 8;
    int offset = 32;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    painter->rotate(startAngle + 90);
    double degRotate = (180.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void GaugeCircle::drawPointerIndicator(QPainter *painter)
{
    int radius = 85;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, radiusY, 5, radiusY, 0, radius);

    painter->rotate(startAngle + 90);
    double degRotate = (180.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeCircle::drawPointerIndicatorR(QPainter *painter)
{
    int radius = 85;
    painter->save();
    painter->setOpacity(0.6);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(pointerColor);
    painter->setPen(pen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, radiusY, 5, radiusY, 0, radius);

    painter->rotate(startAngle + 90);
    double degRotate = (180.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void GaugeCircle::drawPointerTriangle(QPainter *painter)
{
    int radius = 10;
    int offset = 45;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0 + offset, 5, 0 + offset, 0, radius + offset);

    painter->rotate(startAngle + 90);
    double degRotate = (180.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeCircle::drawRoundCircle(QPainter *painter)
{
    int radius = 18;
    painter->save();
    painter->setOpacity(0.6);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius - radiusY, radius * 2, radius * 2);
    painter->restore();
}

void GaugeCircle::drawCenterCircle(QPainter *painter)
{
    int radius = 13;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius - radiusY, radius * 2, radius * 2);
    painter->restore();
}

void GaugeCircle::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);

    QRectF textRect(-radius, -radius - radiusY, radius * 2, radius * 2);
    QString strValue = QString::number(currentValue, 'f', 0);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void GaugeCircle::drawOverlay(QPainter *painter)
{
    if (!showOverlay) {
        return;
    }

    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);

    //高光的形状为小圆扣掉大圆的部分
    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0, 0);
    overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, overlayColor);
    overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, overlayColor);
    painter->setBrush(linearGradient);
    painter->rotate(-20);
    painter->drawPath(highlight);

    painter->restore();
}

void GaugeCircle::updateValue()
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

double GaugeCircle::getMinValue() const
{
    return this->minValue;
}

double GaugeCircle::getMaxValue() const
{
    return this->maxValue;
}

double GaugeCircle::getValue() const
{
    return this->value;
}

int GaugeCircle::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeCircle::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugeCircle::getStartAngle() const
{
    return this->startAngle;
}

int GaugeCircle::getEndAngle() const
{
    return this->endAngle;
}

bool GaugeCircle::getAnimation() const
{
    return this->animation;
}

double GaugeCircle::getAnimationStep() const
{
    return this->animationStep;
}

QColor GaugeCircle::getUsedColor() const
{
    return this->usedColor;
}

QColor GaugeCircle::getFreeColor() const
{
    return this->freeColor;
}

QColor GaugeCircle::getScaleColor() const
{
    return this->scaleColor;
}

QColor GaugeCircle::getPointerColor() const
{
    return this->pointerColor;
}

QColor GaugeCircle::getTextColor() const
{
    return this->textColor;
}

QColor GaugeCircle::getTitleColor() const
{
    return this->titleColor;
}

bool GaugeCircle::getShowOverlay() const
{
    return this->showOverlay;
}

QColor GaugeCircle::getOverlayColor() const
{
    return this->overlayColor;
}

GaugeCircle::PointerStyle GaugeCircle::getPointerStyle() const
{
    return this->pointerStyle;
}

QSize GaugeCircle::sizeHint() const
{
    return QSize(200, 100);
}

QSize GaugeCircle::minimumSizeHint() const
{
    return QSize(50, 25);
}

void GaugeCircle::setRange(double minValue, double maxValue)
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

void GaugeCircle::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeCircle::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeCircle::setValue(double value)
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

void GaugeCircle::setValue(int value)
{
    setValue((double)value);
}

void GaugeCircle::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugeCircle::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void GaugeCircle::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeCircle::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeCircle::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void GaugeCircle::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void GaugeCircle::setUsedColor(const QColor &usedColor)
{
    if (this->usedColor != usedColor) {
        this->usedColor = usedColor;
        update();
    }
}

void GaugeCircle::setFreeColor(const QColor &freeColor)
{
    if (this->freeColor != freeColor) {
        this->freeColor = freeColor;
        update();
    }
}

void GaugeCircle::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void GaugeCircle::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        update();
    }
}

void GaugeCircle::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeCircle::setTitleColor(const QColor &titleColor)
{
    if (this->titleColor != titleColor) {
        this->titleColor = titleColor;
        update();
    }
}

void GaugeCircle::setShowOverlay(bool showOverlay)
{
    if (this->showOverlay != showOverlay) {
        this->showOverlay = showOverlay;
        update();
    }
}

void GaugeCircle::setOverlayColor(const QColor &overlayColor)
{
    if (this->overlayColor != overlayColor) {
        this->overlayColor = overlayColor;
        update();
    }
}

void GaugeCircle::setPointerStyle(const GaugeCircle::PointerStyle &pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        update();
    }
}
