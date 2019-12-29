#pragma execution_character_set("utf-8")

#include "customring.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

CustomRing::CustomRing(QWidget *parent) : QWidget(parent)
{
    showTitle = true;
    titleHeight = 18;
    title = "环形图";

    showLegend = true;
    legendHeight = 50;

    bgColor = QColor(52, 73, 94);
    textColor = QColor(255, 255, 255);
    highColor = QColor(241, 196, 15);
    flagColor = QColor(0, 192, 133);

    outCircleColor = QColor(44, 62, 80);
    midCircleColor = QColor(12, 28, 40);
    inCircleColor = QColor(12, 28, 40);

    //饼图颜色集合
    outPieColors << QColor(0, 176, 180) << QColor(255, 192, 0) << QColor(0, 113, 193) << QColor(72, 103, 149) << QColor(185, 87, 86)
                 << QColor(0, 177, 125) << QColor(214, 77, 84) << QColor(71, 164, 233) << QColor(34, 163, 169) << QColor(40, 45, 48)
                 << QColor(162, 121, 197) << QColor(72, 202, 245) << QColor(0, 150, 121) << QColor(111, 9, 176) << QColor(250, 170, 20);
    //倒过来设置
    for (int i = outPieColors.count() - 1; i >= 0; i--) {
        inPieColors << outPieColors.at(i);
    }

    //设置鼠标跟踪识别悬停高亮
    this->setMouseTracking(true);
    //设置启用父类的样式表
    this->setAttribute(Qt::WA_StyledBackground, true);
}

CustomRing::~CustomRing()
{
}

void CustomRing::mouseMoveEvent(QMouseEvent *event)
{
    //通过绘制路径的contains方法判断鼠标是否在对应区域内
    bool contains = false;
    for (int i = 0; i < inPieInfo.size(); i++) {
        if (inPieInfo.at(i).path.contains(event->pos())) {
            inPieInfo[i].offset = 5;
            contains = true;
        } else {
            if (inPieInfo.at(i).offset != 0) {
                contains = true;
            }

            inPieInfo[i].offset = 0;
        }
    }

    //优先绘制内圆偏移
    if (contains) {
        for (int i = 0; i < outPieInfo.size(); i++) {
            outPieInfo[i].offset = 0;
        }

        update();
        return;
    }

    for (int i = 0; i < outPieInfo.size(); i++) {
        if (outPieInfo.at(i).path.contains(event->pos())) {
            outPieInfo[i].offset = 5;
            contains = true;
        } else {
            if (outPieInfo.at(i).offset != 0) {
                contains = true;
            }

            outPieInfo[i].offset = 0;
        }
    }

    if (contains) {
        update();
    }
}

void CustomRing::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    int titleHeight = showTitle ? this->titleHeight : 0;
    int legendHeight = showLegend ? this->legendHeight : 0;
    QRect rect(0, titleHeight, this->width(), this->height() - titleHeight - legendHeight);
    int side = qMin(rect.width(), rect.height());
    qreal scale = side / 200.0;

    //绘制背景
    drawBg(&painter);

    //平移坐标轴中心,等比例缩放
    painter.save();
    painter.translate(rect.center());
    painter.scale(scale, scale);

    //绘制外圆背景
    drawOutCircle(&painter);
    //绘制外层饼图
    drawOutPie(&painter, scale, rect.center());
    //绘制中间圆
    drawMidCircle(&painter);
    //绘制里层饼图
    drawInPie(&painter, scale, rect.center());
    //绘制里边圆
    drawInCircle(&painter);

    painter.restore();

    //重新等比例缩放,绘制文字,文字放在后面绘制是为了不被圆遮挡
    painter.scale(scale, scale);

    //绘制标题
    if (showTitle) {
        drawTitle(&painter);
    }

    //绘制图例文字
    if (showLegend) {
        drawLegendText(&painter, scale);
    }
}

void CustomRing::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawRoundedRect(this->rect(), 5, 5);
    painter->restore();
}

void CustomRing::drawOutCircle(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(outCircleColor);
    painter->drawEllipse(QPoint(0, 0), radius, radius);
    painter->restore();
}

void CustomRing::drawMidCircle(QPainter *painter)
{
    int radius = 50;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(midCircleColor);
    painter->drawEllipse(QPoint(0, 0), radius, radius);
    painter->restore();
}

void CustomRing::drawInCircle(QPainter *painter)
{
    int radius = 10;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(inCircleColor);
    painter->drawEllipse(QPoint(0, 0), radius, radius);
    painter->restore();
}

void CustomRing::drawOutPie(QPainter *painter, qreal scale, QPoint center)
{
    int radius = 75;
    int startAngle = 0;
    painter->save();

    //根据用户数据绘制圆
    for (int i = 0; i < outPieInfo.size(); i++) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(outPieInfo.at(i).color);
        int angle = outPieInfo.at(i).percent * 16 * 3.6;
        QPainterPath path;
        int pathInfactRaius = radius + outPieInfo.at(i).offset;
        int pathScaleRadius = scale * pathInfactRaius;
        path.arcTo(-pathScaleRadius, -pathScaleRadius, 2 * pathScaleRadius, 2 * pathScaleRadius, startAngle / 16, angle / 16);
        path.translate(center);
        painter->drawPie(-pathInfactRaius, -pathInfactRaius, 2 * pathInfactRaius, 2 * pathInfactRaius, startAngle, angle);
        startAngle += angle;
        outPieInfo[i].path = path;
    }

    painter->restore();
}

void CustomRing::drawInPie(QPainter *painter, qreal scale, QPoint center)
{
    int radius = 35;
    int startAngle = 0;
    painter->save();

    //根据用户数据绘制圆
    for (int i = 0; i < inPieInfo.size(); i++) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(inPieInfo.at(i).color);
        int angle = inPieInfo.at(i).percent * 16 * 3.6;
        QPainterPath path;
        int pathInfactRaius = radius + inPieInfo.at(i).offset;
        int pathScaleRadius = scale * pathInfactRaius;
        path.arcTo(-pathScaleRadius, -pathScaleRadius, 2 * pathScaleRadius, 2 * pathScaleRadius, startAngle / 16, angle / 16);
        path.translate(center);
        painter->drawPie(-pathInfactRaius, -pathInfactRaius, 2 * pathInfactRaius, 2 * pathInfactRaius, startAngle, angle);
        startAngle += angle;
        inPieInfo[i].path = path;
    }

    painter->restore();
}

void CustomRing::drawTitle(QPainter *painter)
{
    painter->save();

    //先绘制左侧标识
    painter->setPen(Qt::NoPen);
    painter->setBrush(flagColor);
    painter->drawRect(10, 10, 3, titleHeight);

    //设置字体
    QFont font;
    font.setPointSize(11);
    painter->setFont(font);

    //再绘制右侧文字
    QRect textRect(18, 10, 120, titleHeight);
    painter->setPen(textColor);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, title);

    painter->restore();
}

void CustomRing::drawLegendText(QPainter *painter, qreal scale)
{
    int rectWidth = 12;
    int rectRadius = 2;
    painter->save();

    QFont font;
    font.setPointSize(10);
    painter->setFont(font);

    //绘制左侧图例区域文字
    int fonthegiht = painter->fontMetrics().height() + 2;
    int textHeight = fonthegiht * scale;
    int textPosy = qRound((this->height() - textHeight) * 1.0 / scale);
    for (int i = 0; i < outPieInfo.size(); i++) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(outPieInfo.at(i).color);
        painter->drawRoundedRect(10, textPosy, rectWidth, rectWidth, rectRadius, rectRadius);
        painter->restore();

        //在鼠标移动的事件中已经设置好offset
        if (outPieInfo.at(i).offset > 0) {
            painter->setPen(highColor);
            font.setBold(true);
            painter->setFont(font);
        } else {
            painter->setPen(textColor);
            font.setBold(false);
            painter->setFont(font);
        }

        QString str = QString("%1：%2%").arg(outPieInfo.at(i).text).arg(outPieInfo.at(i).percent);
        painter->drawText(28, textPosy - 2, 120, 14, Qt::AlignLeft | Qt::AlignVCenter, str);
        textPosy = textPosy - fonthegiht;
    }

    font.setPointSize(10);
    font.setBold(false);
    painter->setFont(font);

    //获取此刻文本最大宽度,计算右侧绘制区域
    int maxwidth = 0;
    for (int i = 0; i < inPieInfo.size(); i++) {
        maxwidth = qMax(painter->fontMetrics().width(inPieInfo.at(i).text), maxwidth);
    }

    //绘制右侧图例区域文字
    textHeight = fonthegiht * scale;
    textPosy = qRound((this->height() - textHeight) * 1.0 / scale);
    int textPosx = qRound(this->width() * 1.0 / scale - maxwidth - 70);
    for (int i = 0; i < inPieInfo.size(); i++) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(inPieInfo.at(i).color);
        painter->drawRoundedRect(textPosx, textPosy, rectWidth, rectWidth, rectRadius, rectRadius);
        painter->restore();

        //在鼠标移动的事件中已经设置好offset
        if (inPieInfo.at(i).offset > 0) {
            painter->setPen(highColor);
            font.setBold(true);
            painter->setFont(font);
        } else {
            painter->setPen(textColor);
            font.setBold(false);
            painter->setFont(font);
        }

        QString str = QString("%1：%2%").arg(inPieInfo.at(i).text).arg(inPieInfo.at(i).percent);
        painter->drawText(textPosx + 18, textPosy - 2, 120, 14, Qt::AlignLeft | Qt::AlignVCenter, str);
        textPosy = textPosy - fonthegiht;
    }

    painter->restore();
}

bool CustomRing::getShowTitle() const
{
    return this->showTitle;
}

int CustomRing::getTitleHeight() const
{
    return this->titleHeight;
}

QString CustomRing::getTitle() const
{
    return this->title;
}

bool CustomRing::getShowLegend() const
{
    return this->showLegend;
}

int CustomRing::getLegendHeight() const
{
    return this->legendHeight;
}

QColor CustomRing::getBgColor() const
{
    return this->bgColor;
}

QColor CustomRing::getTextColor() const
{
    return this->textColor;
}

QColor CustomRing::getHighColor() const
{
    return this->highColor;
}

QColor CustomRing::getFlagColor() const
{
    return this->flagColor;
}

QColor CustomRing::getOutCircleColor() const
{
    return this->outCircleColor;
}

QColor CustomRing::getMidCircleColor() const
{
    return this->midCircleColor;
}

QColor CustomRing::getInCircleColor() const
{
    return this->inCircleColor;
}

QString CustomRing::getOutPieInfos() const
{
    return this->outPieInfos;
}

QString CustomRing::getInPieInfos() const
{
    return this->inPieInfos;
}

QSize CustomRing::sizeHint() const
{
    return QSize(300, 300);
}

QSize CustomRing::minimumSizeHint() const
{
    return QSize(30, 30);
}

void CustomRing::setShowTitle(bool showTitle)
{
    if (this->showTitle != showTitle) {
        this->showTitle = showTitle;
        this->update();
    }
}

void CustomRing::setTitleHeight(int titleHeight)
{
    if (this->titleHeight != titleHeight) {
        this->titleHeight = titleHeight;
        this->update();
    }
}

void CustomRing::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        this->update();
    }
}

void CustomRing::setShowLegend(bool showLegend)
{
    if (this->showLegend != showLegend) {
        this->showLegend = showLegend;
        this->update();
    }
}

void CustomRing::setLegendHeight(int legendHeight)
{
    if (this->legendHeight != legendHeight) {
        this->legendHeight = legendHeight;
        this->update();
    }
}

void CustomRing::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void CustomRing::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void CustomRing::setHighColor(const QColor &highColor)
{
    if (this->highColor != highColor) {
        this->highColor = highColor;
        this->update();
    }
}

void CustomRing::setFlagColor(const QColor &flagColor)
{
    if (this->flagColor != flagColor) {
        this->flagColor = flagColor;
        this->update();
    }
}

void CustomRing::setOutCircleColor(const QColor &outCircleColor)
{
    if (this->outCircleColor != outCircleColor) {
        this->outCircleColor = outCircleColor;
        this->update();
    }
}

void CustomRing::setMidCircleColor(const QColor &midCircleColor)
{
    if (this->midCircleColor != midCircleColor) {
        this->midCircleColor = midCircleColor;
        this->update();
    }
}

void CustomRing::setInCircleColor(const QColor &inCircleColor)
{
    if (this->inCircleColor != inCircleColor) {
        this->inCircleColor = inCircleColor;
        this->update();
    }
}

void CustomRing::setOutPieInfos(const QString &outPieInfos)
{
    if (this->outPieInfos != outPieInfos) {
        //转为结构体数据,格式:文字,百分比|文字,百分比
        outPieInfo.clear();
        QStringList list = outPieInfos.split("|");
        int count = list.count();
        for (int i = 0; i < count; i++) {
            QStringList l = list.at(i).split(",");
            if (l.count() == 2) {
                CustomRing::RingData data;
                if (outPieColors.count() > i) {
                    data.color = outPieColors.at(i);
                } else {
                    data.color = QColor(0, 176, 180);
                }

                data.text = l.at(0);
                data.percent = l.at(1).toInt();
                outPieInfo.append(data);
            }
        }

        this->outPieInfos = outPieInfos;
        this->update();
    }
}

void CustomRing::setInPieInfos(const QString &inPieInfos)
{
    if (this->inPieInfos != inPieInfos) {
        //转为结构体数据,格式:文字,百分比|文字,百分比
        inPieInfo.clear();
        QStringList list = inPieInfos.split("|");
        int count = list.count();
        for (int i = 0; i < count; i++) {
            QStringList l = list.at(i).split(",");
            if (l.count() == 2) {
                CustomRing::RingData data;
                if (inPieColors.count() > i) {
                    data.color = inPieColors.at(i);
                } else {
                    data.color = QColor(0, 176, 180);
                }

                data.text = l.at(0);
                data.percent = l.at(1).toInt();
                inPieInfo.append(data);
            }
        }

        this->inPieInfos = inPieInfos;
        this->update();
    }
}

void CustomRing::setOutPieColors(const QList<QColor> &outPieColors)
{
    this->outPieColors = outPieColors;
    this->update();
}

void CustomRing::setInPieColors(const QList<QColor> &inPieColors)
{
    this->inPieColors = inPieColors;
    this->update();
}

void CustomRing::clearOutPie()
{
    outPieInfo.clear();
    this->update();
}

void CustomRing::clearInPie()
{
    inPieInfo.clear();
    this->update();
}

void CustomRing::appendOutPie(const RingData &data)
{
    outPieInfo.append(data);
    this->update();
}

void CustomRing::appendInPie(const RingData &data)
{
    inPieInfo.append(data);
    this->update();
}
