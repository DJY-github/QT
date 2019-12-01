#pragma execution_character_set("utf-8")

#include "gaugelpm.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

GaugeLpm::GaugeLpm(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    title = "FLOW RATE";
    unit = "LPM";

    bgColor = QColor(61, 60, 65, 0);
    percentColor = QColor(80, 140, 241);
    textColor = QColor(250, 250, 250);

    mousePress = false;
    inCenter = false;
    lastPoint = QPointF();

    setFont(QFont("Arial", 8));
}

GaugeLpm::~GaugeLpm()
{

}

void GaugeLpm::mousePressEvent(QMouseEvent *e)
{
    mousePress = true;
    lastPoint = e->pos();
    update();
    emit clicked();
}

void GaugeLpm::mouseReleaseEvent(QMouseEvent *)
{
    mousePress = false;
    update();
}

double GaugeLpm::twoPtDistance(const QPointF &pt1, const QPointF &pt2)
{
    double offsetX = pt2.x() - pt1.x();
    double offsetY = pt2.y() - pt1.y();
    return qSqrt((offsetX * offsetX) + (offsetY * offsetY));
}

void GaugeLpm::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //计算当前按下点到中心点的距离,如果小于内圆的半径则认为在内圆中
    QPointF center = this->rect().center();
    double centerSize = (double)side / ((double)100 / 75);
    double offset = twoPtDistance(lastPoint, center);
    inCenter = (offset <= centerSize / 2);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    //为什么要这样处理?因为这样处理可以很巧妙的实现任意分辨率大小自适应
    QPainter painter(this);
    painter.fillRect(this->rect(), bgColor);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制最外边圆
    drawCircle(&painter, 99, QColor(120, 120, 120), QColor(30, 30, 30));

    //绘制轨道圆+圆边框,产生立体感
    drawCircle(&painter, 90, QColor(20, 20, 20), QColor(120, 120, 120));
    drawCircle(&painter, 89, QColor(40, 40, 40), QColor(40, 40, 40));

    //绘制进度
    drawPercent(&painter);

    //绘制中间圆+圆边框,产生立体感
    if (mousePress && inCenter) {
        drawCircle(&painter, 75, QColor(90, 90, 90), QColor(30, 30, 30));
        drawCircle(&painter, 74, QColor(50, 50, 50), QColor(50, 50, 50));
    } else {
        drawCircle(&painter, 75, QColor(250, 250, 250), QColor(250, 250, 250));
        drawCircle(&painter, 74, QColor(230, 230, 230), QColor(200, 200, 200));
    }

    //绘制里边圆+圆边框,产生立体感
    drawCircle(&painter, 65, QColor(25, 25, 25), QColor(30, 30, 30));
    drawCircle(&painter, 64, QColor(50, 50, 50), QColor(50, 50, 50));

    //绘制刻度
    drawLine(&painter);
    //绘制指示器
    drawPointer(&painter);
    //绘制文字(即当前值)+标题+单位
    drawText(&painter);
}

void GaugeLpm::drawCircle(QPainter *painter, int radius, const QColor &color1, const QColor &color2)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    //设置上下渐变颜色
    QLinearGradient linearGradient(0, -radius, 0, radius);
    linearGradient.setColorAt(0, color1);
    linearGradient.setColorAt(1, color2);
    painter->setBrush(linearGradient);

    //绘制圆
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeLpm::drawPercent(QPainter *painter)
{
    int radius = 89;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    //计算当前值范围角度
    double angleCurrent = 360.0 * ((value - minValue) / (maxValue - minValue));

    //绘制当前值饼圆
    painter->setBrush(percentColor);
    painter->drawPie(rect, (90 - angleCurrent) * 16, angleCurrent * 16);

    painter->restore();
}

void GaugeLpm::drawLine(QPainter *painter)
{
    int radius = 88;
    painter->save();
    painter->setPen(textColor);

    //线条长度
    int lineLen = 12;

    //绘制刻度线条1(左侧)
    painter->rotate(90 + 45);
    painter->drawLine(0, radius - lineLen, 0, radius);

    //绘制刻度线条2(右侧)
    painter->rotate(110);
    painter->drawLine(0, radius - lineLen, 0, radius);

    painter->restore();
}

void GaugeLpm::drawPointer(QPainter *painter)
{
    int radius = 8;
    int offset = 66;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush((mousePress && inCenter) ? textColor : QColor(30, 30, 30));

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);

    //绘制指示器1(左侧)
    painter->rotate(90 + 45);
    painter->drawConvexPolygon(pts);

    //绘制指示器2(右侧)
    painter->rotate(110);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeLpm::drawText(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(50);
    painter->setFont(font);

    //当前文字区域居中
    QRectF textRect(-radius, -radius, radius * 2, radius * 2);

    //保持数字在三位数,如果小于则精确到小数点后X位
    QString strValue;
    if (value >= 0 && value < 10) {
        strValue = QString("%1").arg((double)value, 0, 'f', 2);
    } else if (value >= 10 && value < 100) {
        strValue = QString("%1").arg((double)value, 0, 'f', 1);
    } else {
        strValue = QString("%1").arg((double)value, 0, 'f', 0);
    }

    painter->drawText(textRect, Qt::AlignCenter, strValue);

    //重新设置字体大小
    font.setPixelSize(12);
    painter->setFont(font);

    //绘制标题
    QRectF titleRect(-radius, -radius, radius * 2, radius * 1.35);
    painter->drawText(titleRect, Qt::AlignCenter, title);

    //绘制单位
    QRectF unitRect(0, 0, radius * 0.5, radius * 0.6);
    painter->drawText(unitRect, Qt::AlignRight | Qt::AlignVCenter, unit);

    painter->restore();
}

double GaugeLpm::getMinValue() const
{
    return this->minValue;
}

double GaugeLpm::getMaxValue() const
{
    return this->maxValue;
}

double GaugeLpm::getValue() const
{
    return this->value;
}

QString GaugeLpm::getTitle() const
{
    return this->title;
}

QString GaugeLpm::getUnit() const
{
    return this->unit;
}

QColor GaugeLpm::getBgColor() const
{
    return this->bgColor;
}

QColor GaugeLpm::getPercentColor() const
{
    return this->percentColor;
}

QColor GaugeLpm::getTextColor() const
{
    return this->textColor;
}

QSize GaugeLpm::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeLpm::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeLpm::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (value < minValue || value > maxValue) {
        setValue(value);
    }

    update();
}

void GaugeLpm::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeLpm::setMinValue(double minValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeLpm::setMaxValue(double maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeLpm::setValue(double value)
{
    //值和当前值一致则无需处理
    if (value == this->value) {
        return;
    }

    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    this->value = value;
    update();

    emit valueChanged(value);
}

void GaugeLpm::setValue(int value)
{
    setValue((double)value);
}

void GaugeLpm::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        update();
    }
}

void GaugeLpm::setUnit(const QString &unit)
{
    if (this->unit != unit) {
        this->unit = unit;
        update();
    }
}

void GaugeLpm::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void GaugeLpm::setPercentColor(const QColor &percentColor)
{
    if (this->percentColor != percentColor) {
        this->percentColor = percentColor;
        update();
    }
}

void GaugeLpm::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}
