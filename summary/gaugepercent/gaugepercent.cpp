#pragma execution_character_set("utf-8")

#include "gaugepercent.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

GaugePercent::GaugePercent(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    scaleMajor = 10;
    scaleMinor = 5;
    startAngle = 60;
    endAngle = 60;

    arcColor = QColor(34, 163, 169);
    scaleColor = QColor(34, 163, 169, 100);
    scaleNumColor = QColor(34, 163, 169, 200);
    textColor = QColor(34, 163, 169);
    titleColor = QColor(34, 163, 169);
    baseColor = QColor(34, 163, 169);
    bgColor = Qt::transparent;

    title = "销售额任务";

    setFont(QFont("Microsoft Yahei", 10));
}

GaugePercent::~GaugePercent()
{
}

void GaugePercent::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    if (bgColor != Qt::transparent) {
        painter.setPen(Qt::NoPen);
        painter.fillRect(this->rect(), bgColor);
    }

    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制圆弧
    drawArc(&painter);
    //绘制圆弧进度小球
    drawCircle(&painter);
    //绘制刻度线
    drawScale(&painter);
    //绘制刻度值
    drawScaleNum(&painter);
    //绘制当前值
    drawValue(&painter);
    //绘制标题
    drawTitle(&painter);
}

void GaugePercent::drawArc(QPainter *painter)
{
    int radius = 95;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen;
    pen.setWidthF(5);
    pen.setCapStyle(Qt::RoundCap);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleCurrent = angleAll * ((value - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    //绘制当前进度圆弧
    pen.setColor(arcColor);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余进度圆弧
    pen.setColor(scaleColor);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void GaugePercent::drawCircle(QPainter *painter)
{
    int radius = 6;
    int offset = 83;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(arcColor);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void GaugePercent::drawScale(QPainter *painter)
{
    int radius = 90;
    painter->save();

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (360.0 - startAngle - endAngle) / steps;

    QPen pen;
    pen.setColor(scaleColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(1.0);
    painter->setPen(pen);

    for (int i = 0; i <= steps; i++) {
        painter->drawLine(0, radius - 5, 0, radius);
        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugePercent::drawScaleNum(QPainter *painter)
{
    int radius = 75;
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

void GaugePercent::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(30);
    painter->setFont(font);

    QRectF textRect(-radius, 0, radius * 2, radius / 3);
    QString strValue = QString("%1%").arg((double)value, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void GaugePercent::drawTitle(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(titleColor);

    QFont font;
    font.setPixelSize(20);
    painter->setFont(font);

    QRectF textRect(-radius, radius / 3, radius * 2, radius / 3);
    painter->drawText(textRect, Qt::AlignCenter, title);

    painter->restore();
}

double GaugePercent::getMinValue() const
{
    return this->minValue;
}

double GaugePercent::getMaxValue() const
{
    return this->maxValue;
}

double GaugePercent::getValue() const
{
    return this->value;
}

int GaugePercent::getPrecision() const
{
    return this->precision;
}

int GaugePercent::getScaleMajor() const
{
    return this->scaleMajor;
}

int GaugePercent::getScaleMinor() const
{
    return this->scaleMinor;
}

int GaugePercent::getStartAngle() const
{
    return this->startAngle;
}

int GaugePercent::getEndAngle() const
{
    return this->endAngle;
}

QColor GaugePercent::getArcColor() const
{
    return this->arcColor;
}

QColor GaugePercent::getScaleColor() const
{
    return this->scaleColor;
}

QColor GaugePercent::getScaleNumColor() const
{
    return this->scaleNumColor;
}

QColor GaugePercent::getTextColor() const
{
    return this->textColor;
}

QColor GaugePercent::getTitleColor() const
{
    return this->titleColor;
}

QColor GaugePercent::getBaseColor() const
{
    return this->baseColor;
}

QColor GaugePercent::getBgColor() const
{
    return this->bgColor;
}

QString GaugePercent::getTitle() const
{
    return this->title;
}

QSize GaugePercent::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugePercent::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugePercent::setRange(double minValue, double maxValue)
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

void GaugePercent::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugePercent::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugePercent::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugePercent::setValue(double value)
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

void GaugePercent::setValue(int value)
{
    setValue((double)value);
}

void GaugePercent::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugePercent::setScaleMajor(int scaleMajor)
{
    if (this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        update();
    }
}

void GaugePercent::setScaleMinor(int scaleMinor)
{
    if (this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        update();
    }
}

void GaugePercent::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugePercent::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugePercent::setArcColor(const QColor &arcColor)
{
    if (this->arcColor != arcColor) {
        this->arcColor = arcColor;
        update();
    }
}

void GaugePercent::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void GaugePercent::setScaleNumColor(const QColor &scaleNumColor)
{
    if (this->scaleNumColor != scaleNumColor) {
        this->scaleNumColor = scaleNumColor;
        update();
    }
}

void GaugePercent::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugePercent::setTitleColor(const QColor &titleColor)
{
    if (this->titleColor != titleColor) {
        this->titleColor = titleColor;
        update();
    }
}

void GaugePercent::setBaseColor(const QColor &baseColor)
{
    if (this->baseColor != baseColor) {
        this->baseColor = baseColor;

        //改变基准颜色,立马改变所有颜色
        arcColor = this->baseColor;
        textColor = this->baseColor;
        titleColor = this->baseColor;
        this->baseColor.setAlpha(100);
        scaleColor = this->baseColor;
        this->baseColor.setAlpha(200);
        scaleNumColor = this->baseColor;

        update();
    }
}

void GaugePercent::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void GaugePercent::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        update();
    }
}
