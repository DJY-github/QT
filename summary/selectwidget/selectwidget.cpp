#pragma execution_character_set("utf-8")

#include "selectwidget.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

SelectWidget::SelectWidget(QWidget *parent) : QWidget(parent)
{
    drawPoint = false;
    padding = 5;
    borderWidth = 1;
    pointSize = 8;
    pointColor = QColor(34, 163, 168);
    pointStyle = PointStyle_Rect;

    pressed = false;
    pressedLeft = false;
    pressedRight = false;
    pressedTop = false;
    pressedBottom = false;
    pressedLeftTop = false;
    pressedRightTop = false;
    pressedLeftBottom = false;
    pressedRightBottom = false;

    widget = 0;

    //设置鼠标追踪为真,并绑定事件过滤器,可以获取焦点用于按键移动位置
    this->setMouseTracking(true);
    //安装事件过滤器,识别鼠标拖动和拉伸大小
    this->installEventFilter(this);
    //设置焦点策略,以便鼠标按下获取焦点并手柄可见
    this->setFocusPolicy(Qt::StrongFocus);
}

bool SelectWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Left) {
            this->move(this->pos() - QPoint(1, 0));
        } else if (keyEvent->key() == Qt::Key_Right) {
            this->move(this->pos() + QPoint(1, 0));
        } else if (keyEvent->key() == Qt::Key_Up) {
            this->move(this->pos() - QPoint(0, 1));
        } else if (keyEvent->key() == Qt::Key_Down) {
            this->move(this->pos() + QPoint(0, 1));
        } else if (keyEvent->key() == Qt::Key_Delete) {
            emit widgetDelete(widget);
            widget->deleteLater();
            this->deleteLater();
            widget = 0;
        }

        //重新设置附带窗体的位置和大小
        if (widget != 0) {
            widget->setGeometry(this->x() + padding, this->y() + padding, this->width() - padding * 2, this->height() - padding * 2);
        }

        return QWidget::eventFilter(watched, event);
    }

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (mouseEvent->type() == QEvent::MouseButtonPress) {
        //记住当前控件坐标和宽高以及鼠标按下的坐标
        rectX = this->x();
        rectY = this->y();
        rectW = this->width();
        rectH = this->height();
        lastPos = mouseEvent->pos();

        //判断按下的手柄的区域位置
        if (rectLeft.contains(lastPos)) {
            pressedLeft = true;
        } else if (rectRight.contains(lastPos)) {
            pressedRight = true;
        } else if (rectTop.contains(lastPos)) {
            pressedTop = true;
        } else if (rectBottom.contains(lastPos)) {
            pressedBottom = true;
        } else if (rectLeftTop.contains(lastPos)) {
            pressedLeftTop = true;
        } else if (rectRightTop.contains(lastPos)) {
            pressedRightTop = true;
        } else if (rectLeftBottom.contains(lastPos)) {
            pressedLeftBottom = true;
        } else if (rectRightBottom.contains(lastPos)) {
            pressedRightBottom = true;
        } else {
            pressed = true;
        }

        if (widget != 0) {
            emit widgetPressed(widget);
        }
    } else if (mouseEvent->type() == QEvent::MouseMove) {
        //根据当前鼠标位置,计算XY轴移动了多少
        QPoint pos = mouseEvent->pos();
        int dx = pos.x() - lastPos.x();
        int dy = pos.y() - lastPos.y();

        //根据按下处的位置判断是否是移动控件还是拉伸控件
        if (pressed) {
            this->move(this->x() + dx, this->y() + dy);
        } else if (pressedLeft) {
            int resizeW = this->width() - dx;
            if (this->minimumWidth() <= resizeW) {
                this->setGeometry(this->x() + dx, rectY, resizeW, rectH);
            }
        } else if (pressedRight) {
            this->setGeometry(rectX, rectY, rectW + dx, rectH);
        } else if (pressedTop) {
            int resizeH = this->height() - dy;
            if (this->minimumHeight() <= resizeH) {
                this->setGeometry(rectX, this->y() + dy, rectW, resizeH);
            }
        } else if (pressedBottom) {
            this->setGeometry(rectX, rectY, rectW, rectH + dy);
        } else if (pressedLeftTop) {
            int resizeW = this->width() - dx;
            int resizeH = this->height() - dy;
            if (this->minimumWidth() <= resizeW) {
                this->setGeometry(this->x() + dx, this->y(), resizeW, resizeH);
            }
            if (this->minimumHeight() <= resizeH) {
                this->setGeometry(this->x(), this->y() + dy, resizeW, resizeH);
            }
        } else if (pressedRightTop) {
            int resizeW = rectW + dx;
            int resizeH = this->height() - dy;
            if (this->minimumHeight() <= resizeH) {
                this->setGeometry(this->x(), this->y() + dy, resizeW, resizeH);
            }
        } else if (pressedLeftBottom) {
            int resizeW = this->width() - dx;
            int resizeH = rectH + dy;
            if (this->minimumWidth() <= resizeW) {
                this->setGeometry(this->x() + dx, this->y(), resizeW, resizeH);
            }
            if (this->minimumHeight() <= resizeH) {
                this->setGeometry(this->x(), this->y(), resizeW, resizeH);
            }
        } else if (pressedRightBottom) {
            int resizeW = rectW + dx;
            int resizeH = rectH + dy;
            this->setGeometry(this->x(), this->y(), resizeW, resizeH);
        }

        //重新设置附带窗体的位置和大小
        if (widget != 0) {
            widget->setGeometry(this->x() + padding, this->y() + padding, this->width() - padding * 2, this->height() - padding * 2);
        }
    } else if (mouseEvent->type() == QEvent::MouseButtonRelease) {
        pressed = false;
        pressedLeft = false;
        pressedRight = false;
        pressedTop = false;
        pressedBottom = false;
        pressedLeftTop = false;
        pressedRightTop = false;
        pressedLeftBottom = false;
        pressedRightBottom = false;

        if (widget != 0) {
            emit widgetRelease(widget);
        }
    }

    return QWidget::eventFilter(watched, event);
}

void SelectWidget::resizeEvent(QResizeEvent *)
{
    //重新计算八个描点的区域,描点区域的作用还有就是计算鼠标坐标是否在某一个区域内
    int width = this->width();
    int height = this->height();

    //左侧描点区域
    rectLeft = QRectF(0, height / 2 - pointSize / 2, pointSize, pointSize);
    //上侧描点区域
    rectTop = QRectF(width / 2 - pointSize / 2, 0, pointSize, pointSize);
    //右侧描点区域
    rectRight = QRectF(width - pointSize, height / 2 - pointSize / 2, pointSize, pointSize);
    //下侧描点区域
    rectBottom = QRectF(width / 2 - pointSize / 2, height - pointSize, pointSize, pointSize);

    //左上角描点区域
    rectLeftTop = QRectF(0, 0, pointSize, pointSize);
    //右上角描点区域
    rectRightTop = QRectF(width - pointSize, 0, pointSize, pointSize);
    //左下角描点区域
    rectLeftBottom = QRectF(0, height - pointSize, pointSize, pointSize);
    //右下角描点区域
    rectRightBottom = QRectF(width - pointSize, height - pointSize, pointSize, pointSize);
}

void SelectWidget::mouseMoveEvent(QMouseEvent *e)
{
    //计算当前鼠标位置是否在某个区域内,自动更新鼠标形状
    QPoint p = e->pos();
    if (rectLeft.contains(p)) {
        this->setCursor(Qt::SizeHorCursor);
    } else if (rectTop.contains(p)) {
        this->setCursor(Qt::SizeVerCursor);
    } else if (rectRight.contains(p)) {
        this->setCursor(Qt::SizeHorCursor);
    } else if (rectBottom.contains(p)) {
        this->setCursor(Qt::SizeVerCursor);
    } else if (rectLeftTop.contains(p)) {
        this->setCursor(Qt::SizeFDiagCursor);
    } else if (rectRightTop.contains(p)) {
        this->setCursor(Qt::SizeBDiagCursor);
    } else if (rectLeftBottom.contains(p)) {
        this->setCursor(Qt::SizeBDiagCursor);
    } else if (rectRightBottom.contains(p)) {
        this->setCursor(Qt::SizeFDiagCursor);
    } else {
        this->setCursor(Qt::ArrowCursor);
    }
}

void SelectWidget::paintEvent(QPaintEvent *)
{
    if (!drawPoint) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(pointColor);

    if (pointStyle == PointStyle_Rect) {
        drawRect(&painter);
    } else if (pointStyle == PointStyle_Circle) {
        drawCircle(&painter);
    }

    if (borderWidth > 0) {
        drawBorder(&painter);
    }
}

void SelectWidget::drawRect(QPainter *painter)
{
    //逐个绘制 左上角点+顶边中间点+右上角点+左边中间点+右边中间点+左下角点+底边中间点+右下角点
    painter->save();
    painter->drawRect(rectLeft);
    painter->drawRect(rectRight);
    painter->drawRect(rectTop);
    painter->drawRect(rectBottom);
    painter->drawRect(rectLeftTop);
    painter->drawRect(rectRightTop);
    painter->drawRect(rectLeftBottom);
    painter->drawRect(rectRightBottom);
    painter->restore();
}

void SelectWidget::drawCircle(QPainter *painter)
{
    //逐个绘制 左上角点+顶边中间点+右上角点+左边中间点+右边中间点+左下角点+底边中间点+右下角点
    painter->save();
    painter->drawEllipse(rectLeft);
    painter->drawEllipse(rectRight);
    painter->drawEllipse(rectTop);
    painter->drawEllipse(rectBottom);
    painter->drawEllipse(rectLeftTop);
    painter->drawEllipse(rectRightTop);
    painter->drawEllipse(rectLeftBottom);
    painter->drawEllipse(rectRightBottom);
    painter->restore();
}

void SelectWidget::drawBorder(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setWidth(borderWidth);
    pen.setColor(pointColor);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    QRectF borderRect(pointSize / 2, pointSize / 2, width() - pointSize, height() - pointSize);
    painter->drawRect(borderRect);
    painter->restore();
}

bool SelectWidget::getDrawPoint() const
{
    return this->drawPoint;
}

int SelectWidget::getPadding() const
{
    return this->padding;
}

int SelectWidget::getBorderWidth() const
{
    return this->borderWidth;
}

int SelectWidget::getPointSize() const
{
    return this->pointSize;
}

QColor SelectWidget::getPointColor() const
{
    return this->pointColor;
}

SelectWidget::PointStyle SelectWidget::getPointStyle() const
{
    return this->pointStyle;
}

QWidget *SelectWidget::getWidget() const
{
    return widget;
}

QSize SelectWidget::sizeHint() const
{
    return QSize(200, 200);
}

QSize SelectWidget::minimumSizeHint() const
{
    return QSize(30, 30);
}

void SelectWidget::setDrawPoint(bool drawPoint)
{
    if (this->drawPoint != drawPoint) {
        this->drawPoint = drawPoint;
        update();
    }
}

void SelectWidget::setPadding(int padding)
{
    if (this->padding != padding) {
        this->padding = padding;
        update();
    }
}

void SelectWidget::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        update();
    }
}

void SelectWidget::setPointSize(int pointSize)
{
    if (this->pointSize != pointSize) {
        this->pointSize = pointSize;
        update();
    }
}

void SelectWidget::setPointColor(const QColor &pointColor)
{
    if (this->pointColor != pointColor) {
        this->pointColor = pointColor;
        update();
    }
}

void SelectWidget::setPointStyle(const SelectWidget::PointStyle &pointStyle)
{
    if (this->pointStyle != pointStyle) {
        this->pointStyle = pointStyle;
        update();
    }
}

void SelectWidget::setWidget(QWidget *widget)
{
    this->widget = widget;
    this->widget->setVisible(true);
    this->setVisible(true);

    //设置最小尺寸
    this->setMinimumSize(30, 30);
    //设置当前窗体大小为跟随窗体的大小增加部分
    this->resize(this->widget->size() + QSize(padding * 2, padding * 2));
    //将当前窗体移到偏移位置
    this->move(this->widget->pos() - QPoint(padding, padding));
}
