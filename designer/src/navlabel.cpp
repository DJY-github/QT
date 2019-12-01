#pragma execution_character_set("utf-8")

#include "navlabel.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

NavLabel::NavLabel(QWidget *parent) : QLabel(parent)
{
    borderRadius = 5;
    background = QColor(100, 184, 255);
    foreground = QColor(255, 255, 255);

    showArrow = true;
    arrowSize = 5;
    arrowPosition = ArrowPosition_Right;

    showTriangle = false;
    triangleLen = 5;
    trianglePosition = TrianglePosition_Left;
    triangleColor = QColor(255, 255, 255);

    bgRect = this->geometry();
    setFont(QFont("Microsoft Yahei", 10));
}

void NavLabel::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}

void NavLabel::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制文字
    drawText(&painter);
    //绘制倒三角
    drawTriangle(&painter);
}

void NavLabel::drawBg(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int endX = width - arrowSize;
    int endY = height - arrowSize;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(background);

    QPolygon pts;
    if (arrowPosition == ArrowPosition_Right) {
        bgRect = QRect(0, 0, endX, height);
        pts.setPoints(3, endX, height / 2 - arrowSize, endX, height / 2 + arrowSize, width, height / 2);
    } else if (arrowPosition == ArrowPosition_Left) {
        bgRect = QRect(arrowSize, 0, width - arrowSize, height);
        pts.setPoints(3, arrowSize, height / 2 - arrowSize, arrowSize, height / 2 + arrowSize, 0, height / 2);
    } else if (arrowPosition == ArrowPosition_Bottom) {
        bgRect = QRect(0, 0, width, endY);
        pts.setPoints(3, width / 2 - arrowSize, endY, width / 2 + arrowSize, endY, width / 2, height);
    } else if (arrowPosition == ArrowPosition_Top) {
        bgRect = QRect(0, arrowSize, width, height - arrowSize);
        pts.setPoints(3, width / 2 - arrowSize, arrowSize, width / 2 + arrowSize, arrowSize, width / 2, 0);
    }

    //绘制圆角矩形和三角箭头
    if (!showArrow) {
        bgRect = this->rect();
        painter->drawRoundedRect(bgRect, borderRadius, borderRadius);
    } else {
        painter->drawRoundedRect(bgRect, borderRadius, borderRadius);
        painter->drawPolygon(pts);
    }

    painter->restore();
}

void NavLabel::drawText(QPainter *painter)
{
    painter->save();
    painter->setPen(foreground);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(bgRect, Qt::AlignCenter, this->text());
    painter->restore();
}

void NavLabel::drawTriangle(QPainter *painter)
{
    if (!showTriangle) {
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(triangleColor);

    //绘制在右侧中间,根据设定的倒三角的边长设定三个点位置
    int width = this->width();
    int height = this->height();
    int midWidth = width / 2;
    int midHeight = height / 2;

    QPolygon pts;
    if (trianglePosition == TrianglePosition_Left) {
        pts.setPoints(3, triangleLen, midHeight, 0, midHeight - triangleLen, 0, midHeight + triangleLen);
    } else if (trianglePosition == TrianglePosition_Right) {
        pts.setPoints(3, width - triangleLen, midHeight, width, midHeight - triangleLen, width, midHeight + triangleLen);
    } else if (trianglePosition == TrianglePosition_Top) {
        pts.setPoints(3, midWidth, triangleLen, midWidth - triangleLen, 0, midWidth + triangleLen, 0);
    } else if (trianglePosition == TrianglePosition_Bottom) {
        pts.setPoints(3, midWidth, height - triangleLen, midWidth - triangleLen, height, midWidth + triangleLen, height);
    }

    painter->drawPolygon(pts);

    painter->restore();
}

int NavLabel::getBorderRadius() const
{
    return this->borderRadius;
}

QColor NavLabel::getBackground() const
{
    return this->background;
}

QColor NavLabel::getForeground() const
{
    return this->foreground;
}

bool NavLabel::getShowArrow() const
{
    return this->showArrow;
}

int NavLabel::getArrowSize() const
{
    return this->arrowSize;
}

NavLabel::ArrowPosition NavLabel::getArrowPosition() const
{
    return this->arrowPosition;
}

bool NavLabel::getShowTriangle() const
{
    return this->showTriangle;
}

int NavLabel::getTriangleLen() const
{
    return this->triangleLen;
}

NavLabel::TrianglePosition NavLabel::getTrianglePosition() const
{
    return this->trianglePosition;
}

QColor NavLabel::getTriangleColor() const
{
    return this->triangleColor;
}

QSize NavLabel::sizeHint() const
{
    return QSize(100, 30);
}

QSize NavLabel::minimumSizeHint() const
{
    return QSize(20, 10);
}

void NavLabel::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        update();
    }
}

void NavLabel::setShowArrow(bool showArrow)
{
    if (this->showArrow != showArrow) {
        this->showArrow = showArrow;
        update();
    }
}

void NavLabel::setArrowSize(int arrowSize)
{
    if (this->arrowSize != arrowSize) {
        this->arrowSize = arrowSize;
        update();
    }
}

void NavLabel::setArrowPosition(const NavLabel::ArrowPosition &arrowPosition)
{
    if (this->arrowPosition != arrowPosition) {
        this->arrowPosition = arrowPosition;
        update();
    }
}

void NavLabel::setShowTriangle(bool showTriangle)
{
    if (this->showTriangle != showTriangle) {
        this->showTriangle = showTriangle;
        update();
    }
}

void NavLabel::setTriangleLen(int triangleLen)
{
    if (this->triangleLen != triangleLen) {
        this->triangleLen = triangleLen;
        update();
    }
}

void NavLabel::setTrianglePosition(const NavLabel::TrianglePosition &trianglePosition)
{
    if (this->trianglePosition != trianglePosition) {
        this->trianglePosition = trianglePosition;
        update();
    }
}

void NavLabel::setTriangleColor(const QColor &triangleColor)
{
    if (this->triangleColor != triangleColor) {
        this->triangleColor = triangleColor;
        update();
    }
}

void NavLabel::setBackground(const QColor &background)
{
    if (this->background != background) {
        this->background = background;
        update();
    }
}

void NavLabel::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground) {
        this->foreground = foreground;
        update();
    }
}
