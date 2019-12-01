#pragma execution_character_set("utf-8")

#include "progressround.h"
#include "qpainter.h"
#include "qdebug.h"

ProgressRound::ProgressRound(QWidget *parent) : QWidget(parent)
{
    bgColor = Qt::transparent;
    textColor = QColor(255, 255, 255);
    baseColor = QColor(100, 100, 100);
    innerBgColor = QColor(40, 45, 48);
    borderColor = QColor(255, 255, 255);
    progressColor = QColor(34, 163, 169);

    value = 0;
    minValue = 0;
    maxValue = 100;
    precision = 0;

    nullPosition = 90;
    outlinePenWidth = 1;
    dataPenWidth = 2;

    barStyle = BarStyle_Donut;
    format = "%p";
    clockWise = true;

    setFont(QFont("Arial", 8));
}

void ProgressRound::paintEvent(QPaintEvent *)
{
    //半径取宽高的最小值
    double outerRadius = qMin(width(), height());
    //绘制区域在画面区域的基础上上下左右各减少一个像素,使得看起来完整
    QRectF baseRect(2, 2, outerRadius - 4, outerRadius - 4);

    //先将需要绘制的图形绘制到一张图片上,最后将图片绘制到屏幕
    QImage buffer(outerRadius, outerRadius, QImage::Format_ARGB32_Premultiplied);
    buffer.fill(Qt::transparent);

    QPainter painter(&buffer);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制数据颜色集合
    rebuildDataBrushIfNeeded();
    //绘制背景
    drawBg(&painter, buffer.rect());
    //绘制外框
    drawBase(&painter, baseRect);
    //绘制当前进度
    drawProgress(&painter, baseRect);

    //绘制中心
    double innerRadius(0);
    QRectF innerRect;
    calculateInnerRect(baseRect, outerRadius, innerRect, innerRadius);
    drawInnerBackground(&painter, innerRect);

    //绘制当前值
    drawValue(&painter, innerRect, innerRadius);
    painter.end();

    //绘制背景
    QPainter p(this);
    p.setRenderHints(QPainter::SmoothPixmapTransform);
    p.setPen(Qt::NoPen);
    p.setBrush(bgColor);
    p.drawRect(this->rect());

    //改成居中绘制图片
    int pixX = rect().center().x() - buffer.width() / 2;
    int pixY = rect().center().y() - buffer.height() / 2;
    QPoint point(pixX, pixY);
    p.drawImage(point, buffer);
}

void ProgressRound::drawBg(QPainter *painter, const QRectF &baseRect)
{
    painter->fillRect(baseRect,  Qt::transparent);
}

void ProgressRound::drawBase(QPainter *painter, const QRectF &baseRect)
{
    switch (barStyle) {
    case BarStyle_Donut:
        painter->setPen(QPen(baseColor, outlinePenWidth));
        painter->setBrush(baseColor);
        painter->drawEllipse(baseRect);
        break;

    case BarStyle_Pie:
        painter->setPen(QPen(baseColor, outlinePenWidth));
        painter->setBrush(baseColor);
        painter->drawEllipse(baseRect);
        break;

    case BarStyle_Line:
        painter->setPen(QPen(baseColor, outlinePenWidth));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(baseRect.adjusted(outlinePenWidth / 2, outlinePenWidth / 2, -outlinePenWidth / 2, -outlinePenWidth / 2));
        break;
    }
}

void ProgressRound::drawProgress(QPainter *painter, const QRectF &baseRect)
{
    if (value == minValue) {
        return;
    }

    double arcLength = 360.0 / (maxValue - minValue) * value;

    //逆时针为顺时针分负数
    if (!clockWise) {
        arcLength = -arcLength;
    }

    if (barStyle == BarStyle_Line) {
        painter->setPen(QPen(progressColor, dataPenWidth));
        painter->setBrush(Qt::NoBrush);
        painter->drawArc(baseRect.adjusted(outlinePenWidth / 2, outlinePenWidth / 2, -outlinePenWidth / 2, -outlinePenWidth / 2),
                         nullPosition * 16, -arcLength * 16);
        return;
    }

    QPainterPath dataPath;
    dataPath.setFillRule(Qt::WindingFill);

    dataPath.moveTo(baseRect.center());
    dataPath.arcTo(baseRect, nullPosition, -arcLength);
    dataPath.lineTo(baseRect.center());

    painter->setBrush(progressColor);
    painter->setPen(QPen(borderColor, dataPenWidth));
    painter->drawPath(dataPath);
}

void ProgressRound::calculateInnerRect(const QRectF &/*baseRect*/, double outerRadius, QRectF &innerRect, double &innerRadius)
{
    if (barStyle == BarStyle_Line) {
        innerRadius = outerRadius - outlinePenWidth;
    } else {
        innerRadius = outerRadius * 0.75;
    }

    double delta = (outerRadius - innerRadius) / 2;
    innerRect = QRectF(delta, delta, innerRadius, innerRadius);
}

void ProgressRound::drawInnerBackground(QPainter *painter, const QRectF &innerRect)
{
    if (barStyle == BarStyle_Donut) {
        painter->setBrush(innerBgColor);
        painter->drawEllipse(innerRect);
    }
}

void ProgressRound::drawValue(QPainter *painter, const QRectF &innerRect, double innerRadius)
{
    if (format.isEmpty()) {
        return;
    }

    QFont font;
    font.setPixelSize(innerRadius * qMax(0.05, (0.35 - (double)precision * 0.08)));
    painter->setFont(font);

    QRectF textRect(innerRect);
    painter->setPen(textColor);

    QString strValue;
    if (format == "%v") {
        strValue = QString::number(value, 'f', precision);
    } else if (format == "%p") {
        double procent = (value - minValue) / (maxValue - minValue) * 100.0;
        strValue = QString::number(procent, 'f', precision) + "%";
    } else if (format == "%m") {
        strValue = QString::number(maxValue - minValue + 1, 'f', precision) + "m";
    }

    painter->drawText(textRect, Qt::AlignCenter, strValue);
}

void ProgressRound::rebuildDataBrushIfNeeded()
{
    if (gradientData.count() == 0) {
        return;
    }

    QConicalGradient dataBrush;
    dataBrush.setCenter(0.5, 0.5);
    dataBrush.setCoordinateMode(QGradient::StretchToDeviceMode);

    for (int i = 0; i < gradientData.count(); i++) {
        dataBrush.setColorAt(1.0 - gradientData.at(i).first, gradientData.at(i).second);
    }

    dataBrush.setAngle(nullPosition);
    QPalette p(palette());
    p.setBrush(QPalette::Highlight, dataBrush);
    setPalette(p);
}

QColor ProgressRound::getBgColor() const
{
    return this->bgColor;
}

QColor ProgressRound::getTextColor() const
{
    return this->textColor;
}

QColor ProgressRound::getBaseColor() const
{
    return this->baseColor;
}

QColor ProgressRound::getInnerBgColor() const
{
    return this->innerBgColor;
}

QColor ProgressRound::getBorderColor() const
{
    return this->borderColor;
}

QColor ProgressRound::getProgressColor() const
{
    return this->progressColor;
}

double ProgressRound::getValue() const
{
    return this->value;
}

double ProgressRound::getMinValue() const
{
    return this->minValue;
}

double ProgressRound::getMaxValue() const
{
    return this->maxValue;
}

int ProgressRound::getPrecision() const
{
    return this->precision;
}

double ProgressRound::getNullPosition() const
{
    return this->nullPosition;
}

double ProgressRound::getOutlinePenWidth() const
{
    return this->outlinePenWidth;
}

double ProgressRound::getDataPenWidth() const
{
    return this->dataPenWidth;
}

ProgressRound::BarStyle ProgressRound::getBarStyle() const
{
    return this->barStyle;
}

QString ProgressRound::getFormat() const
{
    return this->format;
}

bool ProgressRound::getClockWise() const
{
    return this->clockWise;
}

QGradientStops ProgressRound::getGradientData() const
{
    return this->gradientData;
}

QSize ProgressRound::sizeHint() const
{
    return QSize(100, 100);
}

QSize ProgressRound::minimumSizeHint() const
{
    return QSize(10, 10);
}

void ProgressRound::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void ProgressRound::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void ProgressRound::setBaseColor(const QColor &baseColor)
{
    if (this->baseColor != baseColor) {
        this->baseColor = baseColor;
        this->update();
    }
}

void ProgressRound::setInnerBgColor(const QColor &innerBgColor)
{
    if (this->innerBgColor != innerBgColor) {
        this->innerBgColor = innerBgColor;
        this->update();
    }
}

void ProgressRound::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        this->update();
    }
}

void ProgressRound::setProgressColor(const QColor &progressColor)
{
    if (this->progressColor != progressColor) {
        this->progressColor = progressColor;
        this->update();
    }
}

void ProgressRound::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

    if (this->maxValue < this->minValue) {
        qSwap(this->maxValue, this->minValue);
    }

    if (value < this->minValue) {
        value = this->minValue;
    } else if (value > this->maxValue) {
        value = this->maxValue;
    }

    this->update();
}

void ProgressRound::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void ProgressRound::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void ProgressRound::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void ProgressRound::setValue(double value)
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
    this->update();
}

void ProgressRound::setValue(int value)
{
    setValue(double(value));
}

void ProgressRound::setPrecision(int precision)
{
    if (precision >= 0 && this->precision != precision) {
        this->precision = precision;
        this->update();
    }
}

void ProgressRound::setNullPosition(double nullPosition)
{
    if (this->nullPosition != nullPosition) {
        this->nullPosition = nullPosition;
        this->update();
    }
}

void ProgressRound::setBarStyle(const ProgressRound::BarStyle &barStyle)
{
    if (this->barStyle != barStyle) {
        this->barStyle = barStyle;
        this->update();
    }
}

void ProgressRound::setFormat(const QString &format)
{
    if (this->format != format) {
        this->format = format;
        this->update();
    }
}

void ProgressRound::setOutlinePenWidth(double outlinePenWidth)
{
    if (this->outlinePenWidth != outlinePenWidth) {
        this->outlinePenWidth = outlinePenWidth;
        this->update();
    }
}

void ProgressRound::setDataPenWidth(double dataPenWidth)
{
    if (this->dataPenWidth != dataPenWidth) {
        this->dataPenWidth = dataPenWidth;
        this->update();
    }
}

void ProgressRound::setClockWise(bool clockWise)
{
    if (this->clockWise != clockWise) {
        this->clockWise = clockWise;
        this->update();
    }
}

void ProgressRound::setGradientData(const QGradientStops &gradientData)
{
    if (this->gradientData != gradientData) {
        this->gradientData = gradientData;
        this->update();
    }
}
