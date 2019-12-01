#include "tiledbg.h"
#include "qpainter.h"
#include "qdebug.h"

TiledBg::TiledBg(QWidget *parent) : QWidget(parent)
{
    color1 = QColor(255, 255, 255);
    color2 = QColor(220, 220, 220);
    bgPix = QPixmap(64, 64);
    drawBg();
}

void TiledBg::drawBg()
{
    bgPix.fill(color1);
    QPainter painter(&bgPix);
    painter.fillRect(0, 0, 32, 32, color2);
    painter.fillRect(32, 32, 32, 32, color2);
    painter.end();
    update();
}

void TiledBg::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawTiledPixmap(this->rect(), bgPix);
}

QColor TiledBg::getColor1() const
{
    return this->color1;
}

QColor TiledBg::getColor2() const
{
    return this->color2;
}

QPixmap TiledBg::getBgPix() const
{
    return this->bgPix;
}

QSize TiledBg::sizeHint() const
{
    return QSize(100,100);
}

QSize TiledBg::minimumSizeHint() const
{
    return QSize(20,20);
}

void TiledBg::setColor1(const QColor &color1)
{
    if (this->color1 != color1) {
        this->color1 = color1;
        drawBg();
    }
}

void TiledBg::setColor2(const QColor &color2)
{
    if (this->color2 != color2) {
        this->color2 = color2;
        drawBg();
    }
}

void TiledBg::setBgPix(const QPixmap &bgPix)
{
    this->bgPix = bgPix;
    update();
}
