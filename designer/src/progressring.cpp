#pragma execution_character_set("utf-8")

#include "progressring.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

ProgressRing::ProgressRing(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;
    text = "";

    clockWise = true;
    showPercent = false;
    alarmMode = 0;
    startAngle = 90;
    ringPadding = 3;
    ringWidth = 15;

    animation = false;
    animationStep = 0.5;

    bgColor = QColor(250, 250, 250);
    circleColor = QColor(240, 240, 240);
    ringColor = QColor(23, 160, 134);
    ringBgColor = QColor(250, 250, 250);
    textColor = QColor(50, 50, 50);

    ringValue1 = 10;
    ringValue2 = 30;
    ringValue3 = 70;

    ringColor1 = QColor(24, 189, 155);
    ringColor2 = QColor(255, 192, 0);
    ringColor3 = QColor(255, 107, 107);

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 8));
}

ProgressRing::~ProgressRing()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void ProgressRing::paintEvent(QPaintEvent *)
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
    //绘制进度
    drawRing(&painter);

    //绘制间隔,重新绘制一个圆遮住,产生间距效果
    if (ringPadding > 0) {
        drawPadding(&painter);
    }

    //绘制中间圆
    drawCircle(&painter);
    //绘制当前值
    drawValue(&painter);
}

void ProgressRing::drawBg(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    //这里有个技巧,如果没有间距则设置成圆环的背景色
    painter->setBrush(ringPadding == 0 ? ringBgColor : bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressRing::drawRing(QPainter *painter)
{
    int radius = 99 - ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(ringColor);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0;
    double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;

    //如果逆时针
    if (!clockWise) {
        angleCurrent = -angleCurrent;
        angleOther = -angleOther;
    }

    //动态设置当前进度颜色
    QColor color = ringColor;
    if (alarmMode == 1) {
        if (currentValue >= ringValue3) {
            color = ringColor3;
        } else if (currentValue >= ringValue2) {
            color = ringColor2;
        } else {
            color = ringColor1;
        }
    } else if (alarmMode == 2) {
        if (currentValue <= ringValue1) {
            color = ringColor1;
        } else if (currentValue <= ringValue2) {
            color = ringColor2;
        } else {
            color = ringColor3;
        }
    }

    //绘制当前值饼圆
    painter->setBrush(color);
    painter->drawPie(rect, (startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余值饼圆
    painter->setBrush(ringBgColor);
    painter->drawPie(rect, (startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void ProgressRing::drawPadding(QPainter *painter)
{
    int radius = 99 - ringWidth - ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressRing::drawCircle(QPainter *painter)
{
    //文字的区域要减去进度的宽度及间距
    int radius = 99 - ringWidth - (ringPadding * 2);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(circleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressRing::drawValue(QPainter *painter)
{
    //文字的区域要减去进度的宽度及间距
    int radius = 99 - ringWidth - (ringPadding * 2);
    painter->save();
    painter->setPen(textColor);

    QFont font;
    int fontSize = radius - (showPercent ? 20 : 6);
    font.setPixelSize(fontSize);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue;
    if (showPercent) {
        double percent = (currentValue * 100) / (maxValue - minValue);
        strValue = QString("%1%").arg(percent, 0, 'f', precision);
    } else {
        strValue = QString("%1").arg(currentValue, 0, 'f', precision);
    }

    //如果定义了显示的文字则优先显示
    strValue = text.isEmpty() ? strValue : text;
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void ProgressRing::updateValue()
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

double ProgressRing::getMinValue() const
{
    return this->minValue;
}

double ProgressRing::getMaxValue() const
{
    return this->maxValue;
}

double ProgressRing::getValue() const
{
    return this->value;
}

int ProgressRing::getPrecision() const
{
    return this->precision;
}

QString ProgressRing::getText() const
{
    return this->text;
}

bool ProgressRing::getClipCenter() const
{
    return this->clipCenter;
}

bool ProgressRing::getClockWise() const
{
    return this->clockWise;
}

bool ProgressRing::getShowPercent() const
{
    return this->showPercent;
}

int ProgressRing::getAlarmMode() const
{
    return this->alarmMode;
}

int ProgressRing::getStartAngle() const
{
    return this->startAngle;
}

int ProgressRing::getRingPadding() const
{
    return this->ringPadding;
}

int ProgressRing::getRingWidth() const
{
    return this->ringWidth;
}

bool ProgressRing::getAnimation() const
{
    return this->animation;
}

double ProgressRing::getAnimationStep() const
{
    return this->animationStep;
}

QColor ProgressRing::getBgColor() const
{
    return this->bgColor;
}

QColor ProgressRing::getTextColor() const
{
    return this->textColor;
}

QColor ProgressRing::getRingColor() const
{
    return this->ringColor;
}

QColor ProgressRing::getRingBgColor() const
{
    return this->ringBgColor;
}

QColor ProgressRing::getCircleColor() const
{
    return this->circleColor;
}

int ProgressRing::getRingValue1() const
{
    return this->ringValue1;
}

int ProgressRing::getRingValue2() const
{
    return this->ringValue2;
}

int ProgressRing::getRingValue3() const
{
    return this->ringValue3;
}

QColor ProgressRing::getRingColor1() const
{
    return this->ringColor1;
}

QColor ProgressRing::getRingColor2() const
{
    return this->ringColor2;
}

QColor ProgressRing::getRingColor3() const
{
    return this->ringColor3;
}

QSize ProgressRing::sizeHint() const
{
    return QSize(200, 200);
}

QSize ProgressRing::minimumSizeHint() const
{
    return QSize(20, 20);
}

void ProgressRing::setRange(double minValue, double maxValue)
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

void ProgressRing::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void ProgressRing::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void ProgressRing::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void ProgressRing::setValue(double value)
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

void ProgressRing::setValue(int value)
{
    setValue((double)value);
}

void ProgressRing::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void ProgressRing::setText(const QString &text)
{
    if (this->text != text) {
        this->text = text;
        update();
    }
}

void ProgressRing::setClipCenter(bool clipCenter)
{
    if (this->clipCenter != clipCenter) {
        this->clipCenter = clipCenter;
        update();
    }
}

void ProgressRing::setClockWise(bool clockWise)
{
    if (this->clockWise != clockWise) {
        this->clockWise = clockWise;
        update();
    }
}

void ProgressRing::setShowPercent(bool showPercent)
{
    if (this->showPercent != showPercent) {
        this->showPercent = showPercent;
        update();
    }
}

void ProgressRing::setAlarmMode(int alarmMode)
{
    if (this->alarmMode != alarmMode) {
        this->alarmMode = alarmMode;
        update();
    }
}

void ProgressRing::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void ProgressRing::setRingPadding(int ringPadding)
{
    if (this->ringPadding != ringPadding) {
        this->ringPadding = ringPadding;
        update();
    }
}

void ProgressRing::setRingWidth(int ringWidth)
{
    if (this->ringWidth != ringWidth) {
        this->ringWidth = ringWidth;
        update();
    }
}

void ProgressRing::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void ProgressRing::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void ProgressRing::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void ProgressRing::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void ProgressRing::setRingColor(const QColor &ringColor)
{
    if (this->ringColor != ringColor) {
        this->ringColor = ringColor;
        update();
    }
}

void ProgressRing::setRingBgColor(const QColor &ringBgColor)
{
    if (this->ringBgColor != ringBgColor) {
        this->ringBgColor = ringBgColor;
        update();
    }
}

void ProgressRing::setCircleColor(const QColor &circleColor)
{
    if (this->circleColor != circleColor) {
        this->circleColor = circleColor;
        update();
    }
}

void ProgressRing::setRingValue1(int ringValue1)
{
    if (this->ringValue1 != ringValue1) {
        this->ringValue1 = ringValue1;
        update();
    }
}

void ProgressRing::setRingValue2(int ringValue2)
{
    if (this->ringValue2 != ringValue2) {
        this->ringValue2 = ringValue2;
        update();
    }
}

void ProgressRing::setRingValue3(int ringValue3)
{
    if (this->ringValue3 != ringValue3) {
        this->ringValue3 = ringValue3;
        update();
    }
}

void ProgressRing::setRingColor1(const QColor &ringColor1)
{
    if (this->ringColor1 != ringColor1) {
        this->ringColor1 = ringColor1;
        update();
    }
}

void ProgressRing::setRingColor2(const QColor &ringColor2)
{
    if (this->ringColor2 != ringColor2) {
        this->ringColor2 = ringColor2;
        update();
    }
}

void ProgressRing::setRingColor3(const QColor &ringColor3)
{
    if (this->ringColor3 != ringColor3) {
        this->ringColor3 = ringColor3;
        update();
    }
}
