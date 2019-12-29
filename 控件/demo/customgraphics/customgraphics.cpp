#pragma execution_character_set("utf-8")

#include "customgraphics.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmath.h"
#include "qdebug.h"

CustomGraphics::CustomGraphics(QWidget *parent) : QWidget(parent)
{
    selectDotVisible = true;
    dotRadius = 4;
    lineWidth = 2;

    dotColor = QColor(14, 153, 160);
    lineColor = QColor(34, 163, 169);
    polygonColor = QColor(162, 121, 197);
    selectColor = QColor(214, 77, 84);

    pressed = false;
    selectedEllipseIndex = -1;
    selectedIndex = -1;

    setMouseTracking(true);
}

void CustomGraphics::mousePressEvent(QMouseEvent *e)
{
    QPoint p = e->pos();
    pressed = true;
    lastPoint = this->mapToGlobal(p);

    //连线模式下不选中
    if(tempPoints.isEmpty()) {
        //如果选中了,检测是否点到点上
        bool selectedPot = false;
        selectedEllipseIndex = -1;
        if (selectedIndex != -1) {
            for(int i = tempPolygons.at(selectedIndex).pos.size() - 1; i >= 0; --i) {
                if(length(p, tempPolygons.at(selectedIndex).pos[i]) <= 36) {
                    selectedPot = true;
                    selectedEllipseIndex = i;
                    ellipsePos = tempPolygons.at(selectedIndex).pos[i];
                    break;
                }
            }
        }

        //当前选中了点则不用重绘
        if(selectedPot) {
            return;
        }

        //判断是否选中一个
        selectedIndex = -1;
        for(int i = tempPolygons.size() - 1; i >= 0; --i) {
            tempPolygons[i].selected = checkPoint(tempPolygons.at(i).pos, p.x(), p.y());
            if(tempPolygons.at(i).selected) {
                //防止重叠部分
                if(selectedIndex == -1) {
                    selectedIndex = i;
                    pressedPolygon = tempPolygons.at(i);
                } else {
                    tempPolygons[i].selected = false;
                }
            }
        }

        this->update();
    }
}

void CustomGraphics::mouseMoveEvent(QMouseEvent *e)
{
    tempPoint = e->pos();
    if(pressed && selectedIndex != -1) {
        //整体偏移坐标
        QPoint delta = this->mapToGlobal(tempPoint) - lastPoint;
        int len = tempPolygons.at(selectedIndex).pos.size();

        if(selectedEllipseIndex != -1) { //移动点
            tempPolygons[selectedIndex].pos[selectedEllipseIndex] = ellipsePos + delta;
        } else if(selectedIndex != -1) { //移动面
            for(int i = 0; i < len; ++i) {
                tempPolygons[selectedIndex].pos[i] = pressedPolygon.pos.at(i) + delta;
            }
        }
    }

    this->update();
}

void CustomGraphics::mouseReleaseEvent(QMouseEvent *e)
{
    //鼠标右键清空临时的
    if (e->button() == Qt::RightButton) {
        clearTemp();
        return;
    }

    //检测再次点击与最后个点 - 还没写
    pressed = false;
    if(selectedIndex != -1) {
        return;
    }

    QPoint point = e->pos();
    if(tempPoints.count() > 0) {
        qreal len = (qPow(tempPoints.first().x() - point.x() , 2.0) + qPow(tempPoints.first().y() - point.y() , 2.0) );
        if(len < 100) {
            //完成一个多边形
            if(tempPoints.size() >= 3) {
                Polygon pol;
                pol.pos = tempPoints.toVector();
                pol.selected = false;
                tempPolygons.append(pol);
            }

            tempPoints.clear();
            this->update();
            return;
        }
    }

    tempPoints.append(point);
    this->update();
}

void CustomGraphics::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);

    //绘制多边形
    foreach(const Polygon &p, tempPolygons) {
        drawPolygon(&painter, p);
    }

    //绘制点集合
    drawLines(&painter, tempPoints, false);
}

void CustomGraphics::drawPolygon(QPainter *p, const Polygon &v)
{
    p->save();

    //绘制多边形
    p->setPen(QPen(lineColor, lineWidth));
    v.selected ? p->setBrush(selectColor) : p->setBrush(polygonColor);
    p->drawPolygon(v.pos.data(), v.pos.size());

    //绘制圆点
    if(selectDotVisible && v.selected) {
        p->setPen(Qt::NoPen);
        p->setBrush(dotColor);
        foreach(const QPoint &point, v.pos) {
            p->drawEllipse(point, dotRadius, dotRadius);
        }
    }

    p->restore();
}

void CustomGraphics::drawLines(QPainter *p, const QList<QPoint> &list, bool isFirst)
{
    p->save();

    int count = list.count();
    if (count > 0) {
        //绘制点集合
        p->setPen(Qt::NoPen);
        p->setBrush(dotColor);
        for(int i = 0; i < count; ++i) {
            p->drawEllipse(list.at(i), dotRadius, dotRadius);
        }

        //绘制线条集合
        p->setPen(QPen(lineColor, lineWidth));
        p->setBrush(Qt::NoBrush);
        for(int i = 0; i < count - 1; ++i) {
            p->drawLine(list.at(i), list.at(i + 1));
        }

        //绘制最后一条线条
        p->drawLine(list.last(), isFirst ? list.first() : tempPoint);
    }

    p->restore();
}

double CustomGraphics::length(const QPoint &p1, const QPoint &p2)
{
    //平方和
    return qPow(p1.x() - p2.x(), 2.0) + qPow(p1.y() - p2.y(), 2.0);
}

bool CustomGraphics::checkPoint(const QVector<QPoint> &points, int testx, int testy)
{
    //最少保证3个点
    const int count = points.size();
    if(count < 3) {
        return false;
    }

    QList<int> vertx, verty;
    for(int i = 0; i < count; ++i) {
        vertx << points.at(i).x();
        verty << points.at(i).y();
    }

    //核心算法,计算坐标是否在多边形内部
    int i = 0, j, c = 0;
    for (i = 0, j = count - 1; i < count; j = i++) {
        bool b1 = (verty.at(i) > testy) != (verty.at(j) > testy);
        bool b2 = (testx < (vertx.at(j) - vertx.at(i)) * (testy - verty.at(i)) / (verty.at(j) - verty.at(i)) + vertx.at(i));
        if (b1 && b2) {
            c = !c;
        }
    }

    return c;
}

bool CustomGraphics::getSelectDotVisible() const
{
    return this->selectDotVisible;
}

int CustomGraphics::getDotRadius() const
{
    return this->dotRadius;
}

int CustomGraphics::getLineWidth() const
{
    return this->lineWidth;
}

QColor CustomGraphics::getDotColor() const
{
    return this->dotColor;
}

QColor CustomGraphics::getLineColor() const
{
    return this->lineColor;
}

QColor CustomGraphics::getPolygonColor() const
{
    return this->polygonColor;
}

QColor CustomGraphics::getSelectColor() const
{
    return this->selectColor;
}

QSize CustomGraphics::sizeHint() const
{
    return QSize(200, 100);
}

QSize CustomGraphics::minimumSizeHint() const
{
    return QSize(20, 10);
}

void CustomGraphics::setSelectDotVisible(bool selectDotVisible)
{
    if (this->selectDotVisible != selectDotVisible) {
        this->selectDotVisible = selectDotVisible;
        this->update();
    }
}

void CustomGraphics::setDotRadius(int dotRadius)
{
    if (this->dotRadius != dotRadius) {
        this->dotRadius = dotRadius;
        this->update();
    }
}

void CustomGraphics::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        this->update();
    }
}

void CustomGraphics::setDotColor(const QColor &dotColor)
{
    if (this->dotColor != dotColor) {
        this->dotColor = dotColor;
        this->update();
    }
}

void CustomGraphics::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void CustomGraphics::setPolygonColor(const QColor &polygonColor)
{
    if (this->polygonColor != polygonColor) {
        this->polygonColor = polygonColor;
        this->update();
    }
}

void CustomGraphics::setSelectColor(const QColor &selectColor)
{
    if (this->selectColor != selectColor) {
        this->selectColor = selectColor;
        this->update();
    }
}

void CustomGraphics::clearTemp()
{
    tempPoints.clear();
    update();
}

void CustomGraphics::clearAll()
{
    tempPolygons.clear();
    clearTemp();
}
