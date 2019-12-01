#pragma execution_character_set("utf-8")

#include "magicfish.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

MagicFish::MagicFish(QWidget *parent) : QWidget(parent)
{
    headColor = QColor(244, 92, 71, 200);
    bodyColor = QColor(244, 92, 71, 220);
    finColor = QColor(244, 92, 71, 150);
    tailColor = QColor(244, 92, 71, 180);
    baseColor = QColor(244, 92, 71);

    finMove = false;
    speed = 30;
    wave = 1.0;

    currentAngle = 0.0;
    currentValue = 0;

    headLen = 10;
    finLen = headLen * 1.8;
    bodyLen = headLen * 5.2;
    tailLen = headLen * 0.8;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start(100);
}

MagicFish::~MagicFish()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void MagicFish::resizeEvent(QResizeEvent *)
{
    headLen = qMin(width(), height()) / 10.0;
    bodyLen = headLen * 5.2;
    finLen = headLen * 1.8;
    tailLen = headLen * 0.8;
}

void MagicFish::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPointF middlePos = QPointF(width() / 2, height() / 2);
    headPos = calcPoint(middlePos, bodyLen / 1.5, currentAngle);
    double angle = currentAngle + qSin(qDegreesToRadians(currentValue * 1.2 * wave)) * 2;
    QPointF pos = calcPoint(headPos, bodyLen, angle - 180);

    //绘制头部
    drawHead(&painter);

    //绘制鱼身
    drawBody(&painter, pos, angle);

    //绘制左侧鱼鳍
    QPointF leftPos = calcPoint(headPos, headLen * 0.9, angle + 110);
    drawFin(&painter, leftPos, true, angle);

    //绘制右侧鱼鳍
    QPointF rightPos = calcPoint(headPos, headLen * 0.9, angle - 110);
    drawFin(&painter, rightPos, false, angle);

    //绘制鱼尾
    drawTail(&painter, pos, angle);
}

void MagicFish::drawHead(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(headColor);
    //鱼头关节圆
    painter->drawEllipse(headPos, headLen, headLen);
    painter->restore();
}

void MagicFish::drawBody(QPainter *painter, const QPointF &pos, double angle)
{
    //计算身体部分四个点
    QPointF pos1 = calcPoint(headPos, headLen, angle - 80);
    QPointF pos2 = calcPoint(pos, headLen * 0.8, angle - 90);
    QPointF pos3 = calcPoint(pos, headLen * 0.8, angle + 90);
    QPointF pos4 = calcPoint(headPos, headLen, angle + 80);

    QPointF leftPos = calcPoint(headPos, bodyLen * 0.56, angle - 130);
    QPointF rightPos = calcPoint(headPos, bodyLen * 0.56, angle + 130);

    //计算绘制路径
    QPainterPath path;
    path.moveTo(pos1);
    path.quadTo(leftPos, pos2);
    path.lineTo(pos3);
    path.quadTo(rightPos, pos4);
    path.lineTo(pos1);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bodyColor);
    painter->drawPath(path);
    painter->restore();
}

void MagicFish::drawFin(QPainter *painter, const QPointF &pos, bool left, double angle)
{
    double controlAngle = 115;
    double finAngle = finMove ? qSin(qDegreesToRadians(currentValue * 16.1 * wave)) * 12.0 : 2;
    QPointF endPos = calcPoint(pos, finLen, left ? angle + finAngle + 180 : angle - finAngle - 180);
    QPointF controlPos = calcPoint(pos, finLen * 1.8, left ? angle + controlAngle + finAngle : angle - controlAngle - finAngle);

    //计算鱼鳍的路径
    QPainterPath path;
    path.moveTo(pos);
    path.quadTo(controlPos, endPos);
    path.lineTo(pos);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(finColor);
    painter->drawPath(path);
    painter->restore();
}

void MagicFish::drawTail(QPainter *painter, const QPointF &pos, double angle)
{
    double flag = 0.6;
    double length = tailLen * (flag + 1);
    double tailAngle = angle + qCos(qDegreesToRadians(currentValue * 1.5 * wave)) * 15;

    QPointF endPos = calcPoint(pos, length, tailAngle - 180);
    QPointF pos1 = calcPoint(pos, tailLen, tailAngle - 90);
    QPointF pos2 = calcPoint(endPos, tailLen * flag, tailAngle - 90);
    QPointF pos3 = calcPoint(endPos, tailLen * flag, tailAngle + 90);
    QPointF pos4 = calcPoint(pos, tailLen, tailAngle + 90);

    QPainterPath path;
    path.moveTo(pos1);
    path.lineTo(pos2);
    path.lineTo(pos3);
    path.lineTo(pos4);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(tailColor);
    //鱼尾关节大圆
    painter->drawEllipse(pos, tailLen, tailLen);
    //鱼尾关节小圆
    painter->drawEllipse(endPos, tailLen * flag, tailLen * flag);
    //鱼尾肉部分路径
    painter->drawPath(path);
    painter->restore();

    //绘制鱼尾关节
    drawTail1(painter, endPos, tailAngle);
}

void MagicFish::drawTail1(QPainter *painter, const QPointF &pos, double angle)
{
    double len = tailLen * 0.6;
    double flag = 0.4;
    double length = len * (flag + 2.7);
    double tailAngle = angle + qSin(qDegreesToRadians(currentValue * 1.7 * wave)) * 35;

    QPointF endPos = calcPoint(pos, length, tailAngle - 180);
    QPointF pos1 = calcPoint(pos, len, tailAngle - 90);
    QPointF pos2 = calcPoint(endPos, len * flag, tailAngle - 90);
    QPointF pos3 = calcPoint(endPos, len * flag, tailAngle + 90);
    QPointF pos4 = calcPoint(pos, len, tailAngle + 90);

    QPainterPath path;
    path.moveTo(pos1);
    path.lineTo(pos2);
    path.lineTo(pos3);
    path.lineTo(pos4);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(tailColor);
    painter->drawPath(path);
    painter->restore();

    //绘制鱼尾鱼鳍
    drawTail2(painter, pos, tailAngle);
}

void MagicFish::drawTail2(QPainter *painter, const QPointF &pos, double angle)
{
    double len = tailLen * 0.6;
    double flag = 0.4;
    double length = len * (flag + 2.7);
    double tailWidth = qAbs(qSin(qDegreesToRadians(currentValue * 1.9 * wave)) * len + headLen / 5.0 * 3.0);
    QPointF endPos1 = calcPoint(pos, length, angle - 180);
    QPointF endPos2 = calcPoint(pos, length - 10, angle - 180);

    QPointF pos1 = calcPoint(endPos1, tailWidth, angle - 90);
    QPointF pos2 = calcPoint(endPos1, tailWidth, angle + 90);
    QPointF pos3 = calcPoint(endPos2, tailWidth - headLen / 1.5, angle - 90);
    QPointF pos4 = calcPoint(endPos2, tailWidth - headLen / 1.5, angle + 90);

    QPainterPath path1;
    path1.moveTo(pos);
    path1.lineTo(pos3);
    path1.lineTo(pos4);
    path1.lineTo(pos);

    QPainterPath path2;
    path2.moveTo(pos);
    path2.lineTo(pos1);
    path2.lineTo(pos2);
    path2.lineTo(pos);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(tailColor);
    painter->drawPath(path1);
    painter->drawPath(path2);
    painter->restore();
}

QPointF MagicFish::calcPoint(const QPointF &pos, double len, double angle)
{
    double x = qCos(qDegreesToRadians(angle)) * len;
    double y = qSin(qDegreesToRadians(angle - 180)) * len;
    return QPointF(pos + QPointF(x, y));
}

double MagicFish::qDegreesToRadians(double degrees)
{
    return degrees * double(M_PI / 180);
}

double MagicFish::qRadiansToDegrees(double radians)
{
    return radians * double(180 / M_PI);
}

void MagicFish::updateValue()
{
    //值会一直递增,需要判断是否越界
    if (currentValue >= (INT_MAX - speed)) {
        currentValue = 0;
    }

    currentValue = (currentValue + speed) % 54000;
    update();
}

QColor MagicFish::getHeadColor() const
{
    return this->headColor;
}

QColor MagicFish::getBodyColor() const
{
    return this->bodyColor;
}

QColor MagicFish::getFinColor() const
{
    return this->finColor;
}

QColor MagicFish::getTailColor() const
{
    return this->tailColor;
}

QColor MagicFish::getBaseColor() const
{
    return this->baseColor;
}

bool MagicFish::getFinMove() const
{
    return this->finMove;
}

int MagicFish::getSpeed() const
{
    return this->speed;
}

double MagicFish::getWave() const
{
    return this->wave;
}

double MagicFish::getCurrentAngle() const
{
    return this->currentAngle;
}

double MagicFish::getHeadLen() const
{
    return this->headLen;
}

QPointF MagicFish::getHeadPos() const
{
    return this->headPos;
}

QSize MagicFish::sizeHint() const
{
    return QSize(200, 200);
}

QSize MagicFish::minimumSizeHint() const
{
    return QSize(20, 20);
}

void MagicFish::setHeadColor(const QColor &headColor)
{
    if (this->headColor != headColor) {
        this->headColor = headColor;
        update();
    }
}

void MagicFish::setBodyColor(const QColor &bodyColor)
{
    if (this->bodyColor != bodyColor) {
        this->bodyColor = bodyColor;
        update();
    }
}

void MagicFish::setFinColor(const QColor &finColor)
{
    if (this->finColor != finColor) {
        this->finColor = finColor;
        update();
    }
}

void MagicFish::setTailColor(const QColor &tailColor)
{
    if (this->tailColor != tailColor) {
        this->tailColor = tailColor;
        update();
    }
}

void MagicFish::setBaseColor(const QColor &baseColor)
{
    if (this->baseColor != baseColor) {
        this->baseColor = baseColor;

        //根据基准颜色设置其他颜色
        this->baseColor.setAlpha(200);
        headColor = this->baseColor;
        this->baseColor.setAlpha(220);
        bodyColor = this->baseColor;
        this->baseColor.setAlpha(150);
        finColor = this->baseColor;
        this->baseColor.setAlpha(180);
        tailColor = this->baseColor;

        update();
    }
}

void MagicFish::setFinMove(bool finMove)
{
    if (this->finMove != finMove) {
        this->finMove = finMove;
        update();
    }
}

void MagicFish::setSpeed(int speed)
{
    if (this->speed != speed) {
        this->speed = speed;
        update();
    }
}

void MagicFish::setWave(double wave)
{
    if (this->wave != wave) {
        this->wave = wave;
        update();
    }
}

void MagicFish::setCurrentAngle(double currentAngle)
{
    if (this->currentAngle != currentAngle) {
        this->currentAngle = currentAngle;
        update();
    }
}

void MagicFish::setCurrentAngle(int currentAngle)
{
    setCurrentAngle((double)currentAngle);
}

void MagicFish::setHeadLen(int headLen)
{
    if (this->headLen != headLen) {
        this->headLen = headLen;
        this->finLen = headLen * 1.8;
        this->bodyLen = headLen * 5.2;
        this->tailLen = headLen * 0.8;
        update();
    }
}
