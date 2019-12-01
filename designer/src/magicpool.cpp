#include "magicpool.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

MagicPool::MagicPool(QWidget *parent) : QWidget(parent)
{
    maxRadius = 35;
    borderWidth = 5;
    borderColor = QColor(34, 163, 169);
    bgColor = QColor(34, 163, 169, 0);

    startDraw = false;
    currentRadius = 5;

    //启动定时器绘制圆
    timerUpdate = new QTimer(this);
    timerUpdate->setInterval(20);
    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(updateValue()));
}

MagicPool::~MagicPool()
{
    if (timerUpdate->isActive()) {
        timerUpdate->stop();
    }    
}

void MagicPool::mousePressEvent(QMouseEvent *e)
{
    posPress = e->pos();
    startDraw = true;
    currentRadius = 5;
    timerUpdate->start();
}

void MagicPool::paintEvent(QPaintEvent *)
{
    if(startDraw) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen pen;
        pen.setWidth(borderWidth);
        pen.setColor(borderColor);
        painter.setPen(pen);
        painter.setBrush(bgColor);
        painter.drawEllipse(posPress, currentRadius, currentRadius);
    }
}

void MagicPool::updateValue()
{
    //不断更新圆半径,产生动态绘制圆大小
    currentRadius += 2;
    if(currentRadius >= maxRadius) {
        currentRadius = 5;
        startDraw = false;
        timerUpdate->stop();
    }

    update();
}

int MagicPool::getMaxRadius() const
{
    return this->maxRadius;
}

int MagicPool::getBorderWidth() const
{
    return this->borderWidth;
}

QColor MagicPool::getBorderColor() const
{
    return this->borderColor;
}

QColor MagicPool::getBgColor() const
{
    return this->bgColor;
}

QSize MagicPool::sizeHint() const
{
    return QSize(100, 100);
}

QSize MagicPool::minimumSizeHint() const
{
    return QSize(20, 20);
}

void MagicPool::setMaxRadius(int maxRadius)
{
    if (this->maxRadius != maxRadius) {
        this->maxRadius = maxRadius;
        update();
    }
}

void MagicPool::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        update();
    }
}

void MagicPool::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        update();
    }
}

void MagicPool::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}
