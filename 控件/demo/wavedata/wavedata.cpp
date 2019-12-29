#pragma execution_character_set("utf-8")

#include "wavedata.h"
#include "qpainter.h"
#include "qevent.h"
#include "smoothcurvecreator.h"
#include "qfile.h"
#include "qdatetime.h"
#include "qdebug.h"

WaveData::WaveData(QWidget *parent) : QWidget(parent)
{
    deep = 0.5;
    showLine = false;
    lineWidth = 5;
    lineColor = QColor(255, 107, 107);
    foreground = QColor(100, 184, 255);
    background = QColor(255, 255, 255);
    waveStyle = WaveStyle_Line;

    length = 100;
    position = 0;
}

void WaveData::mousePressEvent(QMouseEvent *e)
{
    if (!showLine || data.count() <= 0) {
        return;
    }

    //计算当前按下处的位置,切换到当前位置
    int x = e->pos().x();
    position = ((double)x / width()) * length;
    update();
    emit positionChanged(position);
}

void WaveData::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制数据
    drawData(&painter);
    //绘制当前位置线条
    drawLine(&painter);
}

void WaveData::drawBg(QPainter *painter)
{
    painter->save();
    painter->fillRect(this->rect(), background);
    painter->restore();
}

void WaveData::drawData(QPainter *painter)
{
    if (data.count() == 0) {
        return;
    }

    painter->save();

    //获取最大值最小值
    float max = data.at(0);
    float min = data.at(0);
    int count = data.count();

    for (int i = 1; i < count; i++) {
        if (max < data.at(i)) {
            max = data.at(i);
        }

        if (min > data.at(i)) {
            min = data.at(i);
        }
    }

    //转化成当前屏幕的内的坐标大小
    max += deep;
    min -= deep;

    //自动转换数据到屏幕坐标位置
    QVector<QPointF> points;
    for (int i = 0; i < count; i++) {
        double x = i * width() / count;
        double y = height() - (((data.at(i) - min) / (max - min)) * height());
        points.append(QPointF(x, y));
    }

    //绘制不同的风格
    if (waveStyle == WaveStyle_Line) {
        painter->setPen(foreground);
        for (int i = 0; i < count - 1; i++) {
            painter->drawLine(points.at(i), points.at(i + 1));
        }
    } else if (waveStyle == WaveStyle_Smooth) {
        painter->setPen(foreground);
        QPainterPath path = SmoothCurveCreator::createSmoothCurve(points);
        painter->drawPath(path);
    } else if (waveStyle == WaveStyle_Bar) {
        double penWidth = width() / (count * 1.6);
        QPen pen;
        pen.setColor(foreground);
        pen.setWidthF(penWidth);
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pen);

        for (int i = 0; i < count; i++) {
            QPointF point = points.at(i);
            double x = point.x() + penWidth / 1.2;
            painter->drawLine(QPointF(x, point.y()), QPointF(x, height()));
        }
    }

    painter->restore();
}

void WaveData::drawLine(QPainter *painter)
{
    if (!showLine || position > length || data.count() <= 0) {
        return;
    }

    painter->save();

    QPen pen;
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
    painter->setPen(pen);

    //计算当前位置对应的坐标
    int x = ((double)position / length) * width();
    painter->drawLine(x, 0, x, height());

    painter->restore();
}

double WaveData::getDeep() const
{
    return this->deep;
}

bool WaveData::getShowLine() const
{
    return this->showLine;
}

int WaveData::getLineWidth() const
{
    return this->lineWidth;
}

QColor WaveData::getLineColor() const
{
    return this->lineColor;
}

QColor WaveData::getForeground() const
{
    return this->foreground;
}

QColor WaveData::getBackground() const
{
    return this->background;
}

WaveData::WaveStyle WaveData::getWaveStyle() const
{
    return this->waveStyle;
}

QSize WaveData::sizeHint() const
{
    return QSize(500, 300);
}

QSize WaveData::minimumSizeHint() const
{
    return QSize(50, 30);
}

void WaveData::setDeep(double deep)
{
    if (this->deep != deep) {
        this->deep = deep;
        update();
    }
}

void WaveData::setShowLine(bool showLine)
{
    if (this->showLine != showLine) {
        this->showLine = showLine;
        update();
    }
}

void WaveData::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        update();
    }
}

void WaveData::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void WaveData::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground) {
        this->foreground = foreground;
        update();
    }
}

void WaveData::setBackground(const QColor &background)
{
    if (this->background != background) {
        this->background = background;
        update();
    }
}

void WaveData::setWaveStyle(const WaveData::WaveStyle &waveStyle)
{
    if (this->waveStyle != waveStyle) {
        this->waveStyle = waveStyle;
        update();
    }
}

void WaveData::setLength(int length)
{
    if (this->length != length) {
        this->length = length;
        this->position = 0;
        update();
    }
}

void WaveData::setPosition(int position)
{
    if (this->position != position && position <= length) {
        this->position = position;
        update();
    }
}

void WaveData::setData(const QVector<float> &data)
{
    this->data = data;
    update();
}

void WaveData::clearData()
{
    this->data.clear();
    update();
}
