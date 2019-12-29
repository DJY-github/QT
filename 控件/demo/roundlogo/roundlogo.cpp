#pragma execution_character_set("utf-8")

#include "roundlogo.h"

#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

RoundLogo::RoundLogo(QWidget *parent) : QWidget(parent)
{
    speed = 5;
    bgColor = QColor(255, 255, 255);
    colors << QColor("#F1B45B") << QColor("#F2765C") << QColor("#6D59EF") << QColor("#5C9EF2")
           << QColor("#5CE6F3") << QColor("#5DF25A") << QColor("#B8F458") << QColor("#F1DC5C");

    value = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start(speed);

    setFont(QFont("Arial", 9));
}

RoundLogo::~RoundLogo()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void RoundLogo::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景
    drawBg(&painter);
    //绘制logo
    drawLogo(&painter);
}

void RoundLogo::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);

    int radius = 99;
    QPainterPath bigPath;
    bigPath.addEllipse(QRectF(-radius, -radius, radius * 2, radius * 2));

    radius = 37;
    QPainterPath smallPath;
    smallPath.addEllipse(QRectF(-radius, -radius, radius * 2, radius * 2));

    //两个圆,大圆减去小圆形成一个空心圆环
    painter->drawPath(bigPath - smallPath);

    painter->restore();
}

void RoundLogo::drawLogo(QPainter *painter)
{
    //基准长度
    double base_len = 99;
    //x方向移动长度
    double x_move_len = 15;
    //y方向移动长度
    double y_move_len = -x_move_len / (qSqrt(2) - 1);
    //间距
    double offset = 3;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->rotate(value);

    QPointF centerPoint = QPointF(0, 0);
    QPointF tempPoint = QPoint(-(base_len - x_move_len) - offset, y_move_len - offset);
    double dis = TwoPtDistance(centerPoint, tempPoint);

    //绘制3角形路径
    QPolygonF polygonF;
    //左边点
    polygonF.append(QPoint(-(base_len - x_move_len) - offset, y_move_len - offset));
    //顶点
    polygonF.append(QPoint(-(base_len - x_move_len) - offset, y_move_len - base_len  - offset));
    //右边点
    polygonF.append(QPoint(x_move_len - offset, y_move_len - offset));

    QPainterPath painterPath;
    painterPath.addPolygon(polygonF);

    //绘制切除三角形圆角路径
    QPainterPath painterPath2;
    painterPath2.addEllipse(QPoint(0, 0), dis, dis);
    QPainterPath painterPath3 = painterPath.intersected(painterPath2) ;

    //绘制8个不规则形状,可以自行调整旋转角度来控制数量
    int count = colors.count();
    double deg = 360.0 / count;
    for (int i = 0; i < count; i++) {
        painter->setBrush(colors.at(i));
        painter->drawPath(painterPath3);
        if (i < count - 1) {
            painter->rotate(deg);
        }
    }

    painter->restore();
}

double RoundLogo::TwoPtDistance(const QPointF &pt1, const QPointF &pt2)
{
    double a2 = (pt2.x() - pt1.x()) * (pt2.x() - pt1.x());
    double b2 = (pt2.y() - pt1.y()) * (pt2.y() - pt1.y());
    return qSqrt(a2 + b2);
}

void RoundLogo::updateValue()
{
    value++;
    value = value % 360;
    this->update();
}

int RoundLogo::getSpeed() const
{
    return this->speed;
}

QColor RoundLogo::getBgColor() const
{
    return this->bgColor;
}

QSize RoundLogo::sizeHint() const
{
    return QSize(200, 200);
}

QSize RoundLogo::minimumSizeHint() const
{
    return QSize(50, 50);
}

void RoundLogo::setSpeed(int speed)
{
    if (this->speed != speed) {
        this->speed = speed;
        timer->setInterval(speed);
    }
}

void RoundLogo::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void RoundLogo::setColors(const QList<QColor> &colors)
{
    this->colors = colors;
    this->update();
}

void RoundLogo::start()
{
    timer->start();
}

void RoundLogo::stop()
{
    timer->stop();
}
