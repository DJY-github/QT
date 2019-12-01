#pragma execution_character_set("utf-8")

#include "progressbutton.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

ProgressButton::ProgressButton(QWidget *parent) : QWidget(parent)
{
    lineWidth = 8;
    lineColor = QColor(250, 250, 250);
    borderWidth = 0;
    borderColor = QColor(14, 153, 160);
    borderRadius = 5;
    bgColor = QColor(34, 163, 169);

    value = 0;
    status = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), SLOT(progress()));
}

void ProgressButton::resizeEvent(QResizeEvent *e)
{
    tempWidth = e->size().width();
    this->update();
}

void ProgressButton::mousePressEvent(QMouseEvent *)
{
    if(!timer->isActive()) {
        status = 0;
        value = 0.0;
        tempWidth = this->width();
        timer->start();
    }
}

void ProgressButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    if (1 == status) {
        //绘制当前进度
        drawProgress(&painter);
    } else {
        //绘制按钮背景
        drawBg(&painter);
    }
}

void ProgressButton::drawBg(QPainter *painter)
{
    painter->save();

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPen pen;
    pen.setWidth(borderWidth);
    pen.setColor(borderColor);
    painter->setPen(borderWidth > 0 ? pen : Qt::NoPen);
    painter->setBrush(bgColor);

    QRect rect(((width - tempWidth) / 2) + borderWidth, borderWidth, tempWidth - (borderWidth * 2), height - (borderWidth * 2));
    painter->drawRoundedRect(rect, borderRadius, borderRadius);

    QFont font;
    font.setPixelSize(side - 18);
    painter->setFont(font);
    painter->setPen(lineColor);
    painter->drawText(rect, Qt::AlignCenter, status == 2 ? "完 成" : "开 始");

    painter->restore();
}

void ProgressButton::drawProgress(QPainter *painter)
{
    painter->save();

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    int radius = 99 - borderWidth;

    //绘制外圆
    QPen pen;
    pen.setWidth(borderWidth);
    pen.setColor(borderColor);
    painter->setPen(borderWidth > 0 ? pen : Qt::NoPen);
    painter->setBrush(bgColor);

    //平移坐标轴中心,等比例缩放
    QRect rectCircle(-radius, -radius, radius * 2, radius * 2);
    painter->translate(width / 2, height / 2);
    painter->scale(side / 200.0, side / 200.0);
    painter->drawEllipse(rectCircle);

    //绘制圆弧进度
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
    painter->setPen(pen);

    int offset = radius - lineWidth - 5;
    QRectF rectArc(-offset, -offset, offset * 2, offset * 2);
    int startAngle = offset * 16;
    int spanAngle = -value * 16;
    painter->drawArc(rectArc, startAngle, spanAngle);

    //绘制进度文字
    QFont font;
    font.setPixelSize(offset - 15);
    painter->setFont(font);
    QString strValue = QString("%1%").arg((int)value  * 100 / 360);
    painter->drawText(rectCircle, Qt::AlignCenter, strValue);

    painter->restore();
}

void ProgressButton::progress()
{
    if (0 == status) {
        tempWidth -= 5;
        if (tempWidth < this->height() / 2) {
            tempWidth = this->height() / 2;
            status = 1;
        }
    } else if (1 == status) {
        value += 1.0;
        if (value >= 360) {
            value = 360.0;
            status = 2;
        }
    } else if (2 == status) {
        tempWidth += 5;
        if (tempWidth > this->width()) {
            tempWidth = this->width();
            timer->stop();
        }
    }

    this->update();
}

int ProgressButton::getLineWidth() const
{
    return this->lineWidth;
}

QColor ProgressButton::getLineColor() const
{
    return this->lineColor;
}

int ProgressButton::getBorderWidth() const
{
    return this->borderWidth;
}

QColor ProgressButton::getBorderColor() const
{
    return this->borderColor;
}

int ProgressButton::getBorderRadius() const
{
    return this->borderRadius;
}

QColor ProgressButton::getBgColor() const
{
    return this->bgColor;
}

QSize ProgressButton::sizeHint() const
{
    return QSize(200, 80);
}

QSize ProgressButton::minimumSizeHint() const
{
    return QSize(30, 15);
}

void ProgressButton::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        this->update();
    }
}

void ProgressButton::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void ProgressButton::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        this->update();
    }
}

void ProgressButton::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        this->update();
    }
}

void ProgressButton::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        this->update();
    }
}

void ProgressButton::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}
