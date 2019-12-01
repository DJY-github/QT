#pragma execution_character_set("utf-8")

#include "gaugedecibel.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeDecibel::GaugeDecibel(QWidget *parent) : QWidget(parent)
{
    angle = 40;
    ave_angle = 1;
    value = 0;
    minValue = 0;
    maxValue = 150;

    mMin = 0;
    mMax = 0;
    isFirstData = true;

    bgColor = QColor(34, 163, 169);
    textColor = QColor(0, 0, 0);
    usedColor = QColor(67, 206, 244);
    triangleColor = QColor(214, 77, 84);

    currentValue = 0;
    reverse = false;
    animation = false;
    animationStep = 1;

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 9));
}

GaugeDecibel::~GaugeDecibel()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void GaugeDecibel::paintEvent(QPaintEvent *)
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
    //绘制旋转进度
    drawAngle(&painter);
    //绘制指针
    drawPointer(&painter);
    //绘制Min与Max倒三角
    drawTriangle(&painter);
    //绘制当前值
    drawValue(&painter);
}

void GaugeDecibel::drawBg(QPainter *painter)
{
    //留一点距离给绘制三角形
    int radius = 95;
    painter->save();

    QPen pen;
    pen.setColor(bgColor);
    pen.setWidthF(2);

    //绘制外轮廓
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    QRectF rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawEllipse(rect);
    painter->restore();
}

void GaugeDecibel::drawAngle(QPainter *painter)
{
    int radius = 93;
    painter->save();
    painter->rotate(angle);

    //设置画笔
    QPen pen;
    pen.setWidthF(1.5);
    pen.setCapStyle(Qt::RoundCap);

    //根据起始旋转度计算每次坐标需要旋转的角度,按照100等分计算
    //每次旋转的角度=360-(起始角度*2--分左右)/的角100
    double angle_num = maxValue - minValue; //角度平分数量
    ave_angle = (double)(360 - (angle * 2)) / angle_num;

    //绘制已使用百分比
    pen.setColor(usedColor);
    painter->setPen(pen);

    for (double i = 0; i < currentValue + 1; i++) {
        painter->drawLine(0, radius, 0, radius - 15);
        painter->rotate(ave_angle);
    }

    //绘制未使用百分比
    pen.setColor(bgColor);
    painter->setPen(pen);

    for (double i = currentValue + 1; i < (angle_num + 1); i++) {
        painter->drawLine(0, radius, 0, radius - 15);
        painter->rotate(ave_angle);
    }

    painter->restore();
}

void GaugeDecibel::drawPointer(QPainter *painter)
{
    int radius = 75;
    painter->save();
    QPen pen2 = painter->pen();
    pen2.setCapStyle(Qt::FlatCap);
    double penWidth2 = 2.5;
    pen2.setWidthF(penWidth2);

    QRectF rect2(-radius + penWidth2 / 2, -radius + penWidth2 / 2, radius * 2 - penWidth2, radius * 2 - penWidth2);
    double angleAll = 360.0 - angle * 2;

    //绘制圆环
    QConicalGradient conicalGradient(0, 0, -90);
    double nullPos = angle / 360 ;
    conicalGradient.setColorAt(0, Qt::red);
    conicalGradient.setColorAt(nullPos, Qt::red);
    conicalGradient.setColorAt(0.33, Qt::yellow);
    conicalGradient.setColorAt(0.66, Qt::green);
    conicalGradient.setColorAt(1.0 - nullPos, Qt::blue);
    conicalGradient.setColorAt(1.0, Qt::blue);

    QBrush brush(conicalGradient);
    QPen pen3(brush, penWidth2);

    painter->setPen(pen3);
    painter->drawArc(rect2, (270 - angle - angleAll) * 16, angleAll * 16);

    //画起始刻度
    //painter->rotate(angle);
    QPointF A1(0, radius - penWidth2);
    QPointF B1(0, radius - penWidth2 * 2);
    painter->drawLine(rotatePoint(A1, angle), rotatePoint(B1, angle));
    painter->drawLine(rotatePoint(A1, -angle), rotatePoint(B1, -angle));

    //绘制指针
    //painter->save();
    radius = 92;
    QPointF pa(0, radius + 0.5);
    QPointF pb(0, radius - 18);
    pen3.setCapStyle(Qt::RoundCap);
    painter->setPen(pen3);
    painter->drawLine(rotatePoint(pa, -angle - currentValue * ave_angle), rotatePoint(pb, -angle - currentValue * ave_angle));
    painter->restore();
}

void GaugeDecibel::drawTriangle(QPainter *painter)
{
    int radius = 97;
    painter->save();

    QPolygon minPolygon;
    minPolygon.append(QPoint(0, radius));
    minPolygon.append(QPoint(-3, radius + 5));
    minPolygon.append(QPoint(3, radius + 5));
    painter->setPen(Qt::NoPen);
    painter->setBrush(triangleColor);

    QPainterPath minPainterPath;
    minPainterPath.addPolygon(minPolygon);

    painter->rotate(angle + mMin * ave_angle);
    painter->drawPath(minPainterPath);
    painter->fillPath(minPainterPath, triangleColor);

    painter->restore();
    painter->save();

    QPolygon maxPolygon;
    maxPolygon.append(QPoint(0, radius));
    maxPolygon.append(QPoint(-3, radius + 5));
    maxPolygon.append(QPoint(3, radius + 5));
    painter->setPen(Qt::NoPen);
    painter->setBrush(triangleColor);

    QPainterPath maxPainterPath;
    maxPainterPath.addPolygon(maxPolygon);

    painter->rotate(angle + mMax * ave_angle);
    painter->drawPath(maxPainterPath);
    painter->fillPath(maxPainterPath, triangleColor);
    painter->restore();
}

void GaugeDecibel::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();

    QFont font;
    font.setPixelSize(60);
    painter->setFont(font);
    painter->setPen(textColor);

    QString valueStr = QString("%1").arg(QString::number(currentValue, 'f', 0));
    QRectF valueRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(valueRect, Qt::AlignCenter, valueStr);

    painter->restore();
}

QPointF GaugeDecibel::rotatePoint(const QPointF &A, const double &angle)
{
    double startRad = (360 - angle ) * (M_PI / 180);
    double x = A.x() * qCos(startRad) - A.y() * qSin(startRad);
    double y = A.y() * qCos(startRad) + A.x() * qSin(startRad);
    QPointF P(x, y);
    return P;
}

double GaugeDecibel::getValue() const
{
    return this->value;
}

double GaugeDecibel::getMinValue() const
{
    return this->minValue;
}

double GaugeDecibel::getMaxValue() const
{
    return this->maxValue;
}

bool GaugeDecibel::getAnimation() const
{
    return this->animation;
}

int GaugeDecibel::getAnimationStep() const
{
    return this->animationStep;
}

QColor GaugeDecibel::getBgColor() const
{
    return this->bgColor;
}

QColor GaugeDecibel::getTextColor() const
{
    return this->textColor;
}

QColor GaugeDecibel::getUsedColor() const
{
    return this->usedColor;
}

QColor GaugeDecibel::getTriangleColor() const
{
    return this->triangleColor;
}

QSize GaugeDecibel::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeDecibel::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeDecibel::setMinValue(double value)
{
    setRange(value, maxValue);
}

void GaugeDecibel::setMaxValue(double value)
{
    setRange(minValue, value);
}

void GaugeDecibel::setRange(double minValue, double maxValue)
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

    this->update();
}

void GaugeDecibel::checkMaxAndMin(double value)
{
    if(!isFirstData) {
        if(value < mMin) {
            mMin = value;
        }
        if(value > mMax) {
            mMax = value;
        }
    } else {
        mMin = value;
        mMax = value;
        isFirstData = false;
    }
}

void GaugeDecibel::setValue(double value)
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
        checkMaxAndMin(this->value);
        this->update();
    } else {
        timer->start();
    }
}

void GaugeDecibel::updateValue()
{
    if (!reverse) {
        if (currentValue >= value) {
            currentValue = value;
            checkMaxAndMin(currentValue);
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            currentValue = value;
            checkMaxAndMin(currentValue);
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    this->update();
}

void GaugeDecibel::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        this->update();
    }
}

void GaugeDecibel::setAnimationStep(int animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        this->update();
    }
}

void GaugeDecibel::setBgColor(const QColor &color)
{
    if (this->bgColor != color) {
        this->bgColor = color;
        this->update();
    }
}

void GaugeDecibel::setTextColor(const QColor &color)
{
    if (this->textColor != color) {
        this->textColor = color;
        this->update();
    }
}

void GaugeDecibel::setUsedColor(const QColor &color)
{
    if (this->usedColor != color) {
        this->usedColor = color;
        this->update();
    }
}

void GaugeDecibel::setTriangleColor(const QColor &color)
{
    if (this->triangleColor != color) {
        this->triangleColor = color;
        this->update();
    }
}
