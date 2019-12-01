#pragma execution_character_set("utf-8")

#include "gaugecloud.h"
#include "qfontdatabase.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"
#include "qpushbutton.h"
GaugeCloud::GaugeCloud(QWidget *parent) : QWidget(parent)
{
    bgColor = QColor(25, 31, 37);
    baseColor = QColor(63, 67, 76);
    arcColor = QColor(41, 45, 54);
    borderColor = QColor(34, 163, 169);
    textColor = QColor(210, 210, 210);
    enterColor = QColor(14, 153, 160);
    pressColor = QColor(255, 255, 255);

    iconText = "0xf0d7";
    centerText = "0xf021";
    cloudStyle = CloudStyle_Black;

    enter = false;
    pressed = false;

    autoRepeat = true;
    autoRepeatDelay = 500;
    autoRepeatInterval = 200;

    //启动定时器判断长按
    timer = new QTimer(this);
    timer->setInterval(autoRepeatInterval);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkPressed()));

    //判断图形字体是否存在,不存在则加入
    QFontDatabase fontDb;
    if (!fontDb.families().contains("FontAwesome")) {
        int fontId = fontDb.addApplicationFont(":/image/fontawesome-webfont.ttf");
        QStringList fontName = fontDb.applicationFontFamilies(fontId);
        if (fontName.count() == 0) {
            qDebug() << "load fontawesome-webfont.ttf error";
        }
    }

    if (fontDb.families().contains("FontAwesome")) {
        iconFont = QFont("FontAwesome");
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
        iconFont.setHintingPreference(QFont::PreferNoHinting);
#endif
    }

    setFont(iconFont);
    setMouseTracking(true);
}

GaugeCloud::~GaugeCloud()
{
}

void GaugeCloud::enterEvent(QEvent *)
{
    enter = true;
    update();
}

void GaugeCloud::leaveEvent(QEvent *)
{
    enter = false;
    update();
}

void GaugeCloud::mousePressEvent(QMouseEvent *)
{
    pressed = true;
    update();
}

void GaugeCloud::mouseReleaseEvent(QMouseEvent *)
{
    timer->stop();
    pressed = false;
    update();
    emit mouseReleased(position);
}

void GaugeCloud::mouseMoveEvent(QMouseEvent *e)
{
    lastPoint = e->pos();
    update();
}

double GaugeCloud::twoPtDistance(const QPointF &pt1, const QPointF &pt2)
{
    double offsetX = pt2.x() - pt1.x();
    double offsetY = pt2.y() - pt1.y();
    return qSqrt((offsetX * offsetX) + (offsetY * offsetY));
}

void GaugeCloud::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //以中心点为基准,分别计算八方位区域和中间区域
    QPointF center = this->rect().center();
    double centerSize = (double)side / ((double)100 / 30);
    double iconSize = (double)side / ((double)100 / 10);
    double offset1 = 3.6;
    double offset2 = 2.65;

    //计算当前按下点到中心点的距离,如果小于内圆的半径则认为在内圆中
    double offset = twoPtDistance(lastPoint, this->rect().center());
    inCenter = (offset <= centerSize / 2);

    //中间区域
    centerRect = QRectF(center.x() - centerSize / 2, center.y() - centerSize / 2, centerSize, centerSize);
    //左侧图标区域
    leftRect = QRectF(center.x() - iconSize * offset1, center.y() - iconSize / 2, iconSize, iconSize);
    //上侧图标区域
    topRect = QRectF(center.x() - iconSize / 2, center.y() - iconSize * offset1, iconSize, iconSize);
    //右侧图标区域
    rightRect = QRectF(center.x() + iconSize * (offset1 - 1), center.y() - iconSize / 2, iconSize, iconSize);
    //下侧图标区域
    bottomRect = QRectF(center.x() - iconSize / 2, center.y() + iconSize * (offset1 - 1), iconSize, iconSize);
    //左上角图标区域
    leftTopRect = QRectF(center.x() - iconSize * offset2, center.y() - iconSize * offset2, iconSize, iconSize);
    //右上角图标区域
    rightTopRect = QRectF(center.x() + iconSize * (offset2 - 1), center.y() - iconSize * offset2, iconSize, iconSize);
    //左下角图标区域
    leftBottomRect = QRectF(center.x() - iconSize * offset2, center.y() + iconSize * (offset2 - 1), iconSize, iconSize);
    //右下角图标区域
    rightBottomRect = QRectF(center.x() + iconSize * (offset2 - 1), center.y() + iconSize * (offset2 - 1), iconSize, iconSize);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    if (cloudStyle == CloudStyle_Black || cloudStyle == CloudStyle_Custom) {
        //绘制外圆背景
        drawCircle(&painter, 99, bgColor);
        //绘制圆弧
        drawArc(&painter);
        //绘制中间圆盘背景
        drawCircle(&painter, 83, baseColor);
        //绘制内圆背景
        drawCircle(&painter, 40, arcColor);
        //绘制内圆边框
        drawCircle(&painter, 33, borderColor);
        //绘制内圆
        drawCircle(&painter, 30, inCenter ? bgColor : baseColor);
    } else if (cloudStyle == CloudStyle_White) {
        //绘制外圆背景
        drawCircle(&painter, 99, QColor(249, 249, 249));

        //设置圆锥渐变
        QConicalGradient gradient(0, 0, 100);
        gradient.setColorAt(0, QColor(34, 163, 169));
        gradient.setColorAt(0.4, QColor(240, 201, 136));
        gradient.setColorAt(0.7, QColor(211, 77, 37));
        gradient.setColorAt(1, QColor(34, 163, 169));

        //绘制彩色外圆
        drawCircle(&painter, 90, gradient);
        //绘制中间圆盘背景
        drawCircle(&painter, 83, QColor(245, 245, 245));
        //绘制内圆背景
        drawCircle(&painter, 33, QColor(208, 208, 208));
        //绘制内圆边框
        drawCircle(&painter, 32, QColor(208, 208, 208));
        //绘制内圆
        drawCircle(&painter, 30, inCenter ? QColor(255, 255, 255) : QColor(245, 245, 245));
    } else if (cloudStyle == CloudStyle_Blue) {
        //设置圆锥渐变
        QConicalGradient gradient(0, 0, 100);
        gradient.setColorAt(0, QColor(79, 163, 219));
        gradient.setColorAt(0.4, QColor(227, 183, 106));
        gradient.setColorAt(0.7, QColor(217, 178, 109));
        gradient.setColorAt(1, QColor(79, 163, 219));

        //绘制色彩外圆
        drawCircle(&painter, 99, gradient);
        //绘制中间圆盘背景
        drawCircle(&painter, 91, QColor(31, 66, 98));
        //绘制内圆背景
        drawCircle(&painter, 33, QColor(23, 54, 81));
        //绘制内圆边框
        drawCircle(&painter, 30, QColor(150, 150, 150));
        //绘制内圆
        drawCircle(&painter, 30, inCenter ? QColor(35, 82, 133) : QColor(34, 73, 115));
    } else if (cloudStyle == CloudStyle_Purple) {
        //设置圆锥渐变
        QConicalGradient gradient(0, 0, 100);
        gradient.setColorAt(0, QColor(87, 87, 155));
        gradient.setColorAt(0.4, QColor(129, 82, 130));
        gradient.setColorAt(0.7, QColor(54, 89, 166));
        gradient.setColorAt(1, QColor(87, 87, 155));

        //绘制色彩外圆
        drawCircle(&painter, 99, gradient);
        //绘制中间圆盘背景
        drawCircle(&painter, 91, QColor(55, 55, 92));
        //绘制内圆背景
        drawCircle(&painter, 33, QColor(49, 48, 82));
        //绘制内圆边框
        drawCircle(&painter, 30, QColor(82, 78, 131));
        //绘制内圆
        drawCircle(&painter, 30, inCenter ? QColor(85, 81, 137) : QColor(62, 59, 103));
    }

    //绘制八方位+中间图标
    drawText(&painter);

#if 0
    //重置坐标系,并绘制八方位区域及中间区域,判断是否正确
    painter.resetMatrix();
    painter.resetTransform();
    painter.setPen(Qt::white);
    painter.drawRect(centerRect);
    painter.drawRect(leftRect);
    painter.drawRect(topRect);
    painter.drawRect(rightRect);
    painter.drawRect(bottomRect);
    painter.drawRect(leftTopRect);
    painter.drawRect(rightTopRect);
    painter.drawRect(leftBottomRect);
    painter.drawRect(rightBottomRect);
#endif
}

void GaugeCloud::drawCircle(QPainter *painter, int radius, const QBrush &brush)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(brush);

    //绘制圆
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugeCloud::drawArc(QPainter *painter)
{
    int radius = 91;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen;
    pen.setWidthF(10);
    pen.setColor(arcColor);
    painter->setPen(pen);

    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    painter->drawArc(rect, 0 * 16, 360 * 16);

    painter->restore();
}

void GaugeCloud::drawText(QPainter *painter)
{
    bool ok;
    int radius = 100;
    painter->save();

    //判断当前按下坐标是否在中心区域,按下则文本不同颜色
    if (inCenter) {
        if (pressed) {
            position = 8;
            if (autoRepeat) {
                QTimer::singleShot(autoRepeatDelay, timer, SLOT(start()));
            }

            emit mousePressed(position);
        }

        painter->setPen(pressed ? pressColor : enterColor);
    } else {
        painter->setPen(textColor);
    }

    QFont font;
    font.setPixelSize(30);
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
    font.setHintingPreference(QFont::PreferNoHinting);
#endif
    painter->setFont(font);

    //绘制中间图标
    QRectF centerRect(-radius, -radius, radius * 2, radius * 2);
    QString centerText = this->centerText.replace("0x", "");
    QChar centerChar = QChar(centerText.toInt(&ok, 16));
    painter->drawText(centerRect, Qt::AlignCenter, centerChar);

    //绘制八方位图标
    radius = 70;
    int offset = 15;
    int steps = 8;
    double angleStep = 360.0 / steps;

    font.setPixelSize(28);
    painter->setFont(font);

    //从下侧图标开始绘制,顺时针旋转
    QRect iconRect(-offset / 2, radius - offset, offset, offset);
    QString iconText = this->iconText.replace("0x", "");
    QChar iconChar = QChar(iconText.toInt(&ok, 16));
    for (int i = 0; i < steps; i++) {
        //判断鼠标按下的是哪个区域
        bool contains = false;
        if (bottomRect.contains(lastPoint) && i == 0) {
            contains = true;
        } else if (leftBottomRect.contains(lastPoint) && i == 1) {
            contains = true;
        } else if (leftRect.contains(lastPoint) && i == 2) {
            contains = true;
        } else if (leftTopRect.contains(lastPoint) && i == 3) {
            contains = true;
        } else if (topRect.contains(lastPoint) && i == 4) {
            contains = true;
        } else if (rightTopRect.contains(lastPoint) && i == 5) {
            contains = true;
        } else if (rightRect.contains(lastPoint) && i == 6) {
            contains = true;
        } else if (rightBottomRect.contains(lastPoint) && i == 7) {
            contains = true;
        }

        if (contains) {
            if (pressed) {
                position = i;
                if (autoRepeat) {
                    QTimer::singleShot(autoRepeatDelay, timer, SLOT(start()));
                }

                emit mousePressed(position);
            }

            painter->setPen(pressed ? pressColor : enterColor);
        } else {
            painter->setPen(textColor);
        }

        painter->drawText(iconRect, Qt::AlignCenter, iconChar);
        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugeCloud::checkPressed()
{
    if (pressed) {
        emit mousePressed(position);
    } else {
        timer->stop();
    }
}

QColor GaugeCloud::getBgColor() const
{
    return this->bgColor;
}

QColor GaugeCloud::getBaseColor() const
{
    return this->baseColor;
}

QColor GaugeCloud::getArcColor() const
{
    return this->arcColor;
}

QColor GaugeCloud::getBorderColor() const
{
    return this->borderColor;
}

QColor GaugeCloud::getTextColor() const
{
    return this->textColor;
}

QColor GaugeCloud::getEnterColor() const
{
    return this->enterColor;
}

QColor GaugeCloud::getPressColor() const
{
    return this->pressColor;
}

QString GaugeCloud::getIconText() const
{
    return this->iconText;
}

QString GaugeCloud::getCenterText() const
{
    return this->centerText;
}

GaugeCloud::CloudStyle GaugeCloud::getCloudStyle() const
{
    return this->cloudStyle;
}

bool GaugeCloud::getAutoRepeat() const
{
    return this->autoRepeat;
}

int GaugeCloud::getAutoRepeatDelay() const
{
    return this->autoRepeatDelay;
}

int GaugeCloud::getAutoRepeatInterval() const
{
    return this->autoRepeatInterval;
}

QSize GaugeCloud::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeCloud::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugeCloud::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void GaugeCloud::setBaseColor(const QColor &baseColor)
{
    if (this->baseColor != baseColor) {
        this->baseColor = baseColor;
        update();
    }
}

void GaugeCloud::setArcColor(const QColor &arcColor)
{
    if (this->arcColor != arcColor) {
        this->arcColor = arcColor;
        update();
    }
}

void GaugeCloud::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        update();
    }
}

void GaugeCloud::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeCloud::setEnterColor(const QColor &enterColor)
{
    if (this->enterColor != enterColor) {
        this->enterColor = enterColor;
        update();
    }
}

void GaugeCloud::setPressColor(const QColor &pressColor)
{
    if (this->pressColor != pressColor) {
        this->pressColor = pressColor;
        update();
    }
}

void GaugeCloud::setIconText(const QString &iconText)
{
    if (this->iconText != iconText) {
        this->iconText = iconText;
        update();
    }
}

void GaugeCloud::setCenterText(const QString &centerText)
{
    if (this->centerText != centerText) {
        this->centerText = centerText;
        update();
    }
}

void GaugeCloud::setCloudStyle(const GaugeCloud::CloudStyle &cloudStyle)
{
    if (this->cloudStyle != cloudStyle) {
        this->cloudStyle = cloudStyle;
        if (cloudStyle == CloudStyle_Black) {
            bgColor = QColor(25, 31, 37);
            baseColor = QColor(63, 67, 76);
            arcColor = QColor(41, 45, 54);
            borderColor = QColor(34, 163, 169);
            textColor = QColor(210, 210, 210);
            enterColor = QColor(14, 153, 160);
            pressColor = QColor(255, 255, 255);
        } else if (cloudStyle == CloudStyle_White) {
            textColor = QColor(150, 150, 150);
            pressColor = QColor(50, 50, 50);
        } else if (cloudStyle == CloudStyle_Blue) {
            textColor = QColor(75, 165, 221);
            pressColor = QColor(67, 193, 251);
        } else if (cloudStyle == CloudStyle_Purple) {
            textColor = QColor(146, 144, 198);
            pressColor = QColor(160, 160, 198);
        }

        update();
    }
}

void GaugeCloud::setAutoRepeat(bool autoRepeat)
{
    if (this->autoRepeat != autoRepeat) {
        this->autoRepeat = autoRepeat;
    }
}

void GaugeCloud::setAutoRepeatDelay(int autoRepeatDelay)
{
    if (this->autoRepeatDelay != autoRepeatDelay) {
        this->autoRepeatDelay = autoRepeatDelay;
    }
}

void GaugeCloud::setAutoRepeatInterval(int autoRepeatInterval)
{
    if (this->autoRepeatInterval != autoRepeatInterval) {
        this->autoRepeatInterval = autoRepeatInterval;
        timer->setInterval(autoRepeatInterval);
    }
}
