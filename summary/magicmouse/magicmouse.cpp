#pragma execution_character_set("utf-8")

#include "magicmouse.h"
#include "qpainter.h"
#include "qdebug.h"

MagicMouse::MagicMouse(QWidget *parent) : QWidget(parent)
{
    angle = 0;
    bodyColor = QColor(29, 89, 115);
    eyeColor = QColor(30, 30, 30);
    eyeballColor = QColor(255, 255, 255);
    noseColor = QColor(30, 30, 30);
    earColor = QColor(86, 190, 193);
    tailColor = QColor(168, 126, 166);
}

void MagicMouse::paintEvent(QPaintEvent *e)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 100.0, side / 100.0);
    painter.rotate(angle);

    //绘制椭圆身体
    painter.setPen(Qt::NoPen);
    painter.setBrush(bodyColor);
    painter.drawEllipse(-20, -40, 40, 65);

    //绘制圆形眼睛
    int eyeSize = 14;
    int eyeY = -38;
    painter.setBrush(eyeColor);
    painter.drawEllipse(-16, eyeY, eyeSize, eyeSize);
    painter.drawEllipse(2, eyeY, eyeSize, eyeSize);

    //绘制两个眼珠
    int eyeballSize = 8;
    int eyeballY = -38;
    painter.setBrush(eyeballColor);
    painter.drawEllipse(-14, eyeballY, eyeballSize, eyeballSize);
    painter.drawEllipse(6, eyeballY, eyeballSize, eyeballSize);

    //绘制鼻子
    int noseSize = 8;
    int noseY = -45;
    painter.setBrush(noseColor);
    painter.drawEllipse(-4, noseY, noseSize, noseSize);

    //绘制圆形大耳朵
    int earSize = 26;
    int earY = -28;
    painter.setBrush(earColor);
    painter.drawEllipse(-27, earY, earSize, earSize);
    painter.drawEllipse(1, earY, earSize, earSize);

    //绘制尾巴
    int tailX = 5;
    int tailY = 25;
    QPainterPath path(QPointF(0, tailY));
    path.cubicTo(-tailX, tailY + 2, -tailX, tailY + 2, 0, tailY + 5);
    path.cubicTo(tailX, tailY + 7, tailX, tailY + 7, 0, tailY + 10);
    path.cubicTo(-tailX, tailY + 12, -tailX, tailY + 22, 0, tailY + 15);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(tailColor);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
}

int MagicMouse::getAngle() const
{
    return this->angle;
}

QColor MagicMouse::getBodyColor() const
{
    return this->bodyColor;
}

QColor MagicMouse::getEyeColor() const
{
    return this->eyeColor;
}

QColor MagicMouse::getEyeballColor() const
{
    return this->eyeballColor;
}

QColor MagicMouse::getNoseColor() const
{
    return this->noseColor;
}

QColor MagicMouse::getEarColor() const
{
    return this->earColor;
}

QColor MagicMouse::getTailColor() const
{
    return this->tailColor;
}

QSize MagicMouse::sizeHint() const
{
    return QSize(200, 200);
}

QSize MagicMouse::minimumSizeHint() const
{
    return QSize(30, 30);
}

void MagicMouse::setAngle(int angle)
{
    if (this->angle != angle) {
        this->angle = angle;
        update();
    }
}

void MagicMouse::setBodyColor(const QColor &bodyColor)
{
    if (this->bodyColor != bodyColor) {
        this->bodyColor = bodyColor;
        update();
    }
}

void MagicMouse::setEyeColor(const QColor &eyeColor)
{
    if (this->eyeColor != eyeColor) {
        this->eyeColor = eyeColor;
        update();
    }
}

void MagicMouse::setEyeballColor(const QColor &eyeballColor)
{
    if (this->eyeballColor != eyeballColor) {
        this->eyeballColor = eyeballColor;
        update();
    }
}

void MagicMouse::setNoseColor(const QColor &noseColor)
{
    if (this->noseColor != noseColor) {
        this->noseColor = noseColor;
        update();
    }
}

void MagicMouse::setEarColor(const QColor &earColor)
{
    if (this->earColor != earColor) {
        this->earColor = earColor;
        update();
    }
}

void MagicMouse::setTailColor(const QColor &tailColor)
{
    if (this->tailColor != tailColor) {
        this->tailColor = tailColor;
        update();
    }
}
