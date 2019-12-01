#pragma execution_character_set("utf-8")

#include "progressthree.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

ProgressThree::ProgressThree(QWidget *parent) : QWidget(parent)
{
    value1 = 10;
    value2 = 10;
    value3 = 10;

    color1 = QColor(34, 163, 169);
    color2 = QColor(255, 192, 1);
    color3 = QColor(214, 77, 84);

    radius = 0;
    autoRadius = false;

    showValue = false;
    showPercent = false;
    autoFont = false;

    borderWidth = 0;
    borderColor = QColor(255, 255, 255);

    bgColor = QColor(40, 45, 48);
    textColor = QColor(255, 255, 255);

    width1 = 0;
    width2 = 0;
    width3 = 0;
}

void ProgressThree::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    if (autoRadius) {
        radius = this->height() / 2;
    }

    //设置文字字体+颜色
    if (autoFont) {
        QFont font;
        font.setPixelSize(this->height() * 0.8);
        painter.setFont(font);
    }

    //绘制背景
    drawBg(&painter);
    //绘制值1
    drawValue1(&painter);
    //绘制值2
    drawValue2(&painter);

    //绘制值3
    if (value3 > 0) {
        drawValue3(&painter);
    }

    //最后绘制边框盖上去
    if (borderWidth > 0) {
        drawBorder(&painter);
    }
}

void ProgressThree::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    //将背景区域减少一个像素,这样圆角区域不会产生轻微锯齿状
    QRect rect(1, 1, this->width() - 2, this->height() - 2);
    painter->drawRoundedRect(rect, radius, radius);
    painter->restore();
}

void ProgressThree::drawValue1(QPainter *painter)
{
    painter->save();

    //计算百分比以及对应的宽度
    int sum = value1 + value2 + value3;
    double percent = (double)value1 / sum;
    width1 = this->width() * percent;

    painter->setPen(Qt::NoPen);
    painter->setBrush(color1);

    //计算绘制的区域,需要裁剪圆角部分
    QPainterPath clipPath;
    clipPath.addRoundedRect(this->rect(), radius, radius);
    painter->setClipPath(clipPath);
    QRect rect(0, 0, width1, this->height());
    painter->drawRect(rect);

    //绘制文字
    if (showValue) {
        QString text = QString::number(value1);
        if (showPercent) {
            text = QString("%1%").arg(QString::number(percent * 100, 'f', 0));
        }

        painter->setPen(textColor);
        painter->drawText(rect, Qt::AlignCenter, text);
    }

    painter->restore();
}

void ProgressThree::drawValue2(QPainter *painter)
{
    painter->save();

    //计算百分比以及对应的宽度
    int sum = value1 + value2 + value3;
    double percent = (double)value2 / sum;
    width2 = this->width() * percent;

    painter->setPen(Qt::NoPen);
    painter->setBrush(color2);

    //计算绘制的区域,需要裁剪圆角部分
    QPainterPath clipPath;
    clipPath.addRoundedRect(this->rect(), radius, radius);
    painter->setClipPath(clipPath);
    QRect rect(width1, 0, width2, this->height());
    painter->drawRect(rect);

    //绘制文字
    if (showValue) {
        QString text = QString::number(value2);
        if (showPercent) {
            text = QString("%1%").arg(QString::number(percent * 100, 'f', 0));
        }

        painter->setPen(textColor);
        painter->drawText(rect, Qt::AlignCenter, text);
    }

    painter->restore();
}

void ProgressThree::drawValue3(QPainter *painter)
{
    painter->save();

    //宽度减去其他两个就是
    int sum = value1 + value2 + value3;
    double percent = (double)value3 / sum;
    width3 = this->width() - width1 - width2;

    painter->setPen(Qt::NoPen);
    painter->setBrush(color3);

    //计算绘制的区域,需要裁剪圆角部分
    QPainterPath clipPath;
    clipPath.addRoundedRect(this->rect(), radius, radius);
    painter->setClipPath(clipPath);
    QRect rect(width1 + width2, 0, width3, this->height());
    painter->drawRect(rect);

    //绘制文字
    if (showValue) {
        QString text = QString::number(value3);
        if (showPercent) {
            text = QString("%1%").arg(QString::number(percent * 100, 'f', 0));
        }

        painter->setPen(textColor);
        painter->drawText(rect, Qt::AlignCenter, text);
    }

    painter->restore();
}

void ProgressThree::drawBorder(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setWidthF(borderWidth);
    pen.setColor(borderColor);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    QRect rect(1, 1, this->width() - 2, this->height() - 2);
    painter->drawRoundedRect(rect, radius, radius);
    painter->restore();
}

int ProgressThree::getValue1() const
{
    return this->value1;
}

int ProgressThree::getValue2() const
{
    return this->value2;
}

int ProgressThree::getValue3() const
{
    return this->value3;
}

QColor ProgressThree::getColor1() const
{
    return this->color1;
}

QColor ProgressThree::getColor2() const
{
    return this->color2;
}

QColor ProgressThree::getColor3() const
{
    return this->color3;
}

int ProgressThree::getRadius() const
{
    return this->radius;
}

bool ProgressThree::getAutoRadius() const
{
    return this->autoRadius;
}

bool ProgressThree::getShowValue() const
{
    return this->showValue;
}

bool ProgressThree::getShowPercent() const
{
    return this->showPercent;
}

bool ProgressThree::getAutoFont() const
{
    return this->autoFont;
}

double ProgressThree::getBorderWidth() const
{
    return this->borderWidth;
}

QColor ProgressThree::getBorderColor() const
{
    return this->borderColor;
}

QColor ProgressThree::getBgColor() const
{
    return this->bgColor;
}

QColor ProgressThree::getTextColor() const
{
    return this->textColor;
}

QSize ProgressThree::sizeHint() const
{
    return QSize(300, 30);
}

QSize ProgressThree::minimumSizeHint() const
{
    return QSize(10, 5);
}

void ProgressThree::setValue1(int value1)
{
    if (this->value1 != value1 && value1 >= 0) {
        this->value1 = value1;
        this->update();;
    }
}

void ProgressThree::setValue2(int value2)
{
    if (this->value2 != value2 && value2 >= 0) {
        this->value2 = value2;
        this->update();;
    }
}

void ProgressThree::setValue3(int value3)
{
    if (this->value3 != value3 && value3 >= 0) {
        this->value3 = value3;
        this->update();;
    }
}

void ProgressThree::setColor1(const QColor &color1)
{
    if (this->color1 != color1) {
        this->color1 = color1;
        this->update();;
    }
}

void ProgressThree::setColor2(const QColor &color2)
{
    if (this->color2 != color2) {
        this->color2 = color2;
        this->update();;
    }
}

void ProgressThree::setColor3(const QColor &color3)
{
    if (this->color3 != color3) {
        this->color3 = color3;
        this->update();;
    }
}

void ProgressThree::setRadius(int radius)
{
    if (this->radius != radius) {
        this->radius = radius;
        this->update();;
    }
}

void ProgressThree::setAutoRadius(bool autoRadius)
{
    if (this->autoRadius != autoRadius) {
        this->autoRadius = autoRadius;
        this->update();;
    }
}

void ProgressThree::setShowValue(bool showValue)
{
    if (this->showValue != showValue) {
        this->showValue = showValue;
        this->update();;
    }
}

void ProgressThree::setShowPercent(bool showPercent)
{
    if (this->showPercent != showPercent) {
        this->showPercent = showPercent;
        this->update();;
    }
}

void ProgressThree::setAutoFont(bool autoFont)
{
    if (this->autoFont != autoFont) {
        this->autoFont = autoFont;
        this->update();;
    }
}

void ProgressThree::setBorderWidth(double borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        this->update();;
    }
}

void ProgressThree::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        this->update();;
    }
}

void ProgressThree::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();;
    }
}

void ProgressThree::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();;
    }
}

