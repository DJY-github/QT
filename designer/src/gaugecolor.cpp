#pragma execution_character_set("utf-8")

#include "gaugecolor.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeColor::GaugeColor(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    scaleMajor = 10;
    scaleMinor = 5;
    startAngle = 45;
    endAngle = 45;

    animation = true;
    animationStep = 0.5;

    borderColor1 = QColor(120, 120, 120);
    borderColor2 = QColor(30, 30, 30);
    percentColor1 = QColor(30, 231, 253);
    percentColor2 = QColor(50, 255, 0);
    percentColor3 = QColor(255, 80, 0);

    bgColor = QColor(20, 20, 20);
    scaleColor = QColor(250, 250, 250);
    scaleNumColor = QColor(250, 250, 250);
    pointerColor = QColor(255, 107, 107);
    textColor = QColor(255, 255, 255);

    pointerStyle = PointerStyle_Indicator;

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 10));
}

GaugeColor::~GaugeColor()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void GaugeColor::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制外边框圆,产生凹凸立体感
    drawCircle(&painter, 99, borderColor1, borderColor2);
    drawCircle(&painter, 90, bgColor, bgColor);

    //绘制当前进度外边透明部分
    drawPercent(&painter, 90, 0.5);
    //绘制当前进度
    drawPercent(&painter, 85, 1.0);
    //绘制圆,遮住当前进度没有透明部分,以便继续绘制透明部分
    drawCircle(&painter, 80, bgColor, bgColor);
    //绘制当前进度里边透明部分
    drawPercent(&painter, 80, 0.5);
    //绘制内部圆,遮住当前进度
    drawCircle(&painter, 75, borderColor1, borderColor2);

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
}

void GaugeColor::drawCircle(QPainter *painter, int radius, const QColor &color1, const QColor &color2)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    //设置上下渐变颜色
    QLinearGradient linearGradient(0, -radius, 0, radius);
    linearGradient.setColorAt(0, color1);
    linearGradient.setColorAt(1, color2);
    painter->setBrush(linearGradient);

    //绘制圆
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeColor::drawPercent(QPainter *painter, int radius, double opacity)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));

    //绘制中间多彩圆弧左侧进度部分
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    //设置圆锥渐变
    QConicalGradient gradient(0, 0, -(90 - endAngle));
    gradient.setColorAt(0, percentColor3);
    gradient.setColorAt(0.4, percentColor2);
    gradient.setColorAt(0.7, percentColor1);
    gradient.setColorAt(1, percentColor1);

    painter->setOpacity(opacity);
    painter->setBrush(gradient);
    painter->drawPie(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    painter->restore();
}

void GaugeColor::drawScale(QPainter *painter)
{
    int radius = 89;
    painter->save();

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (360.0 - startAngle - endAngle) / steps;

    QPen pen;
    pen.setColor(scaleColor);
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 13, 0, radius);
        } else {
            pen.setWidthF(1.0);
            painter->setPen(pen);
            painter->drawLine(0, radius - 8, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeColor::drawScaleNum(QPainter *painter)
{
    int radius = 57;
    painter->save();
    painter->setPen(scaleNumColor);

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - startAngle - endAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', precision);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void GaugeColor::drawPointerCircle(QPainter *painter)
{
    int radius = 5;
    int offset = 60;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void GaugeColor::drawPointerIndicator(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeColor::drawPointerIndicatorR(QPainter *painter)
{
    int radius = 75;
    painter->save();

    QPen pen;
    pen.setColor(pointerColor);
    painter->setPen(pen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void GaugeColor::drawPointerTriangle(QPainter *painter)
{
    int radius = 10;
    int offset = 65;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0 + offset, 5, 0 + offset, 0, radius + offset);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeColor::drawRoundCircle(QPainter *painter)
{
    int radius = 12;
    painter->save();
    painter->setOpacity(0.5);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeColor::drawCenterCircle(QPainter *painter)
{
    int radius = 8;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeColor::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(30);
    painter->setFont(font);

    QRectF textRect(-radius, radius / 3, radius * 2, radius / 3);
    QString strValue = QString("%1").arg((double)currentValue, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void GaugeColor::updateValue()
{
    if (!reverse) {
        if (currentValue >= value) {
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    update();
}

double GaugeColor::getMinValue() const
{
    return this->minValue;
}

double GaugeColor::getMaxValue() const
{
    return this->maxValue;
}

double GaugeColor::getValue() const
{
    return this->value;
}

int GaugeColor::getPrecision() const
{
    return this->precision;
}

int GaugeColor::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugeColor::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugeColor::getStartAngle() const
{
    return this->startAngle;
}

int GaugeColor::getEndAngle() const
{
    return this->endAngle;
}

bool GaugeColor::getAnimation() const
{
    return this->animation;
}

double GaugeColor::getAnimationStep() const
{
    return this->animationStep;
}

QColor GaugeColor::getBorderColor1() const
{
    return this->borderColor1;
}

QColor GaugeColor::getBorderColor2() const
{
    return this->borderColor2;
}

QColor GaugeColor::getPercentColor1() const
{
    return this->percentColor1;
}

QColor GaugeColor::getPercentColor2() const
{
    return this->percentColor2;
}

QColor GaugeColor::getPercentColor3() const
{
    return this->percentColor3;
}

QColor GaugeColor::getBgColor() const
{
    return this->bgColor;
}

QColor GaugeColor::getScaleColor() const
{
    return this->scaleColor;
}

QColor GaugeColor::getScaleNumColor() const
{
    return this->scaleNumColor;
}

QColor GaugeColor::getPointerColor() const
{
    return this->pointerColor;
}

QColor GaugeColor::getTextColor() const
{
    return this->textColor;
}

GaugeColor::PointerStyle GaugeColor::getPointerStyle() const
{
    return this->pointerStyle;
}

QSize GaugeColor::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeColor::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeColor::setRange(double minValue, double maxValue)
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

void GaugeColor::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeColor::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeColor::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeColor::setValue(double value)
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

void GaugeColor::setValue(int value)
{
    setValue((double)value);
}

void GaugeColor::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeColor::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugeColor::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void GaugeColor::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeColor::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeColor::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void GaugeColor::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void GaugeColor::setBorderColor1(const QColor &borderColor1)
{
    if (this->borderColor1 != borderColor1) {
        this->borderColor1 = borderColor1;
        update();
    }
}

void GaugeColor::setBorderColor2(const QColor &borderColor2)
{
    if (this->borderColor2 != borderColor2) {
        this->borderColor2 = borderColor2;
        update();
    }
}

void GaugeColor::setPercentColor1(const QColor &percentColor1)
{
    if (this->percentColor1 != percentColor1) {
        this->percentColor1 = percentColor1;
        update();
    }
}

void GaugeColor::setPercentColor2(const QColor &percentColor2)
{
    if (this->percentColor2 != percentColor2) {
        this->percentColor2 = percentColor2;
        update();
    }
}

void GaugeColor::setPercentColor3(const QColor &percentColor3)
{
    if (this->percentColor3 != percentColor3) {
        this->percentColor3 = percentColor3;
        update();
    }
}

void GaugeColor::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void GaugeColor::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void GaugeColor::setScaleNumColor(const QColor &scaleNumColor)
{
    if (this->scaleNumColor != scaleNumColor) {
        this->scaleNumColor = scaleNumColor;
        update();
    }
}

void GaugeColor::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        update();
    }
}

void GaugeColor::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeColor::setPointerStyle(const GaugeColor::PointerStyle &pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        update();
    }
}
