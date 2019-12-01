#pragma execution_character_set("utf-8")

#include "custompie.h"
#include "qpainter.h"
#include "qmath.h"
#include "qdebug.h"

CustomPie::CustomPie(QWidget *parent) : QWidget(parent)
{
    explodedIndex = -1;
    explodedAll = false;

    showPercent = false;
    holeSize = 0.0;

    textColor = QColor(255, 255, 255);
    borderColor = QColor(255, 0, 0);

    //备用颜色集合
    colors << QColor(0, 176, 180) << QColor(255, 192, 0) << QColor(0, 113, 193) << QColor(72, 103, 149) << QColor(185, 87, 86)
           << QColor(0, 177, 125) << QColor(214, 77, 84) << QColor(71, 164, 233) << QColor(34, 163, 169) << QColor(40, 45, 48)
           << QColor(162, 121, 197) << QColor(72, 202, 245) << QColor(0, 150, 121) << QColor(111, 9, 176) << QColor(250, 170, 20);
}

CustomPie::~CustomPie()
{
}

void CustomPie::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制饼图
    drawPie(&painter);
}

void CustomPie::drawPie(QPainter *painter)
{
    painter->save();

    int radius = 93;
    QRect rect(-radius, -radius, radius * 2, radius * 2);

    double startAngle = 0;
    double sum = getSumValue();

    //逐个取出值并绘制饼图区域和对应的文字
    int count = labels.count();
    for (int i = 0; i < count; ++i) {
        //取出值并计算当前值占比面积
        double value = values.at(i);
        double arcLength = value / sum * 360;
        double percent = value / sum * 100;
        QRect pieRect = rect;

        //如果当前区域展开则需要设置边框
        painter->setPen(Qt::NoPen);
        if (explodedIndex == i || explodedAll) {
            painter->setPen(borderColor);
            QPoint center = pieRect.center();
            int mid = startAngle + arcLength / 2;
            center += getOffsetPoint(mid);
            pieRect.moveCenter(center);
        }

        //从颜色集合中取出颜色
        painter->setBrush(colors.at(i));
        painter->drawPie(pieRect, startAngle * 16, arcLength * 16);

        QString strValue = labels.at(i);
        if (showPercent && percent > 7) {
            strValue = QString("%1%2%3%").arg(strValue).arg(strValue.isEmpty() ? "" : "\n").arg(QString::number(percent, 'f', 0));
        }

        int mid = startAngle + arcLength / 2;
        int offset = 60;
        if (percent >= 50) {
            offset = 45;
        } else if (percent >= 30) {
            offset = 55;
        } else if (percent >= 15) {
            offset = 60;
        }

        QPoint p = getOffsetPoint(mid, offset);
        QRect textRect;
        textRect.setX(p.x() - 40);
        textRect.setY(p.y() - 30);
        textRect.setWidth(80);
        textRect.setHeight(60);
        painter->setPen(Qt::black);
        //painter->drawRect(textRect);

        QFont font;
        font.setPixelSize(strValue.isEmpty() ? 20 : 17);
        painter->setFont(font);

        painter->setPen(textColor);
        painter->drawText(textRect, Qt::AlignCenter, strValue);
        startAngle += arcLength;
    }

    painter->restore();
}

double CustomPie::getSumValue()
{
    double sum = 0;
    for (int i = 0; i < values.count(); i++) {
        sum += values.at(i);
    }

    if (sum == 0.0) {
        sum = 1;
    }

    return sum;
}

QPoint CustomPie::getOffsetPoint(double angel, int offset)
{
    int wl = 0;
    int hl = 0;
    double ang = (angel) * M_PI / 180;
    wl = offset * qCos(ang);
    hl = offset * qSin(ang);

    if (angel > 90 && angel < 270) {
        wl = qAbs(wl) * -1;
    } else {
        wl = qAbs(wl);
    }

    if (angel < 180) {
        hl = qAbs(hl) * -1;
    } else {
        hl = qAbs(hl);
    }

    return QPoint(wl, hl);
}

QColor CustomPie::getTextColor() const
{
    return this->textColor;
}

QColor CustomPie::getBorderColor() const
{
    return this->borderColor;
}

QSize CustomPie::sizeHint() const
{
    return QSize(200, 200);
}

QSize CustomPie::minimumSizeHint() const
{
    return QSize(20, 20);
}

void CustomPie::setExplodedAll(bool explodedAll)
{
    if (this->explodedAll != explodedAll) {
        this->explodedAll = explodedAll;
        this->update();
    }
}

void CustomPie::setExplodedIndex(int explodedIndex)
{
    if (this->explodedIndex != explodedIndex) {
        this->explodedIndex = explodedIndex;
        this->update();
    }
}

void CustomPie::setDefaultColor(bool defaultColor)
{

}

void CustomPie::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void CustomPie::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        this->update();
    }
}

void CustomPie::setColors(const QList<QColor> &colors)
{
    this->colors = colors;
    this->update();
}

void CustomPie::initPie()
{

}

void CustomPie::appendPie(const QString &label, double value, const QString &tip)
{
    labels << label;
    values << value;
}

void CustomPie::setDataPie()
{

}

void CustomPie::loadPercent()
{
    showPercent = true;
    this->update();
}

void CustomPie::clearPie()
{
    labels.clear();
    values.clear();
}

void CustomPie::setHoleSize(double holeSize)
{
    if (this->holeSize != holeSize) {
        this->holeSize = holeSize;
        this->update();
    }
}
