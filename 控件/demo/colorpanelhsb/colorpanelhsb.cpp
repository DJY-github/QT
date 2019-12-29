#pragma execution_character_set("utf-8")

#include "colorpanelhsb.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

ColorPanelHSB::ColorPanelHSB(QWidget *parent) : QWidget(parent)
{
    percent = 100;
    borderWidth = 10;
    borderColor = QColor(0, 0, 0, 50);
    cursorColor = QColor(0, 0, 0);

    color = QColor(255, 0, 0);
    hue = 0;
    sat = 100;

    lastPos = QPoint(borderWidth, borderWidth);
}

void ColorPanelHSB::showEvent(QShowEvent *)
{
    int width = this->width();
    int height = this->height();

    //首次显示记住当前背景截图,用于获取颜色值
    bgPix = QPixmap(width, height);
    bgPix.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&bgPix);

    QColor colorStart, colorCenter, colorEnd;
    for(int i = 0; i < width; i++) {
        colorStart.setHslF(i / double(width), 1, 0);
        colorCenter.setHslF(i / double(width), 1, 0.5);
        colorEnd.setHslF(i / double(width), 1, 1);

        QLinearGradient linearGradient;
        linearGradient.setStart(QPointF(i, -height));
        linearGradient.setFinalStop(QPointF(i, height));
        linearGradient.setColorAt(0.0, colorStart);
        linearGradient.setColorAt(0.5, colorCenter);
        linearGradient.setColorAt(1.0, colorEnd);

        painter.setPen(QPen(linearGradient, 1));
        painter.drawLine(QPointF(i, 0), QPointF(i, height));
    }

    painter.end();
}

void ColorPanelHSB::resizeEvent(QResizeEvent *)
{
    showEvent(NULL);
}

void ColorPanelHSB::mousePressEvent(QMouseEvent *e)
{
    mouseMoveEvent(e);
}

void ColorPanelHSB::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->pos().x();
    int y = e->pos().y();

    //矫正X轴的偏差
    if (x <= borderWidth) {
        x = borderWidth;
    } else if (x >= width() - borderWidth) {
        x = width() - borderWidth;
    }

    //矫正Y轴的偏差
    if (y <= borderWidth) {
        y = borderWidth;
    } else if (y >= height() - borderWidth) {
        y = height() - borderWidth;
    }

    //指针必须在范围内
    lastPos = QPoint(x, y);

    //获取当前坐标处的颜色值
    color = bgPix.toImage().pixel(lastPos);

    //X坐标所在360分比为hue值
    hue = ((double)(x - borderWidth) / (width() - borderWidth * 2)) * 360;
    //Y坐标所在高度的100分比sat值
    sat = 100 - ((double)(y - borderWidth) / (height() - borderWidth * 2) * 100);

    update();
    emit colorChanged(color, hue, sat);
}

void ColorPanelHSB::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景颜色
    drawBg(&painter);
    //绘制按下出的形状
    drawCursor(&painter);
    //绘制边框
    drawBorder(&painter);
}

void ColorPanelHSB::drawBg(QPainter *painter)
{
    painter->save();

    if (!bgPix.isNull()) {
        painter->drawPixmap(0, 0, bgPix);
    }

    painter->restore();
}

void ColorPanelHSB::drawCursor(QPainter *painter)
{
    painter->save();
    painter->setPen(cursorColor);

    QString text = "+";

    //根据右侧的百分比显示字体大小
    QFont textFont;
    int size = 20 + (35 * (double)percent / 100);
    textFont.setPixelSize(size);

    //计算文字的宽度高度,自动移到鼠标按下处的中心点
    QFontMetrics fm(textFont);
    int textWidth = fm.width(text);
    int textHeight = fm.height();
    QPoint textPoint = lastPos - QPoint(textWidth / 2, -(textHeight / 4));

    QPainterPath path;
    path.addText(textPoint, textFont, text);
    painter->drawPath(path);

    painter->restore();
}

void ColorPanelHSB::drawBorder(QPainter *painter)
{
    painter->save();

    int width = this->width();
    int height = this->height();
    int offset = borderWidth;

    QPen pen;
    pen.setWidth(offset);
    pen.setColor(borderColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::MiterJoin);

    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(offset / 2, offset / 2, width - offset, height - offset);

    painter->restore();
}

int ColorPanelHSB::getPercent() const
{
    return this->percent;
}

QColor ColorPanelHSB::getBorderColor() const
{
    return this->borderColor;
}

QColor ColorPanelHSB::getCursorColor() const
{
    return this->cursorColor;
}

QColor ColorPanelHSB::getColor() const
{
    return this->color;
}

double ColorPanelHSB::getHue() const
{
    return this->hue;
}

double ColorPanelHSB::getSat() const
{
    return this->sat;
}

QSize ColorPanelHSB::sizeHint() const
{
    return QSize(500, 350);
}

QSize ColorPanelHSB::minimumSizeHint() const
{
    return QSize(100, 60);
}

void ColorPanelHSB::setPercent(int percent)
{
    if (this->percent != percent) {
        this->percent = percent;
        update();
    }
}

void ColorPanelHSB::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        update();
    }
}

void ColorPanelHSB::setCursorColor(const QColor &cursorColor)
{
    if (this->cursorColor != cursorColor) {
        this->cursorColor = cursorColor;
        update();
    }
}

