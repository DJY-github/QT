#pragma execution_character_set("utf-8")

#include "slidertip.h"
#include "navlabel.h"
#include "qevent.h"
#include "qdebug.h"

SliderTip::SliderTip(QWidget *parent) : QSlider(parent)
{
    borderRadius = 5;
    arrowSize = 5;
    arrowStyle = ArrowStyle_Bottom;

    background = QColor(100, 184, 255);
    foreground = QColor(255, 255, 255);

    labTipWidth = 50;
    labTipHeight = 30;
    labTipFont = this->font();

    showTime = false;
    clickEnable = true;
    unit = "";

    labTip = new NavLabel;
    labTip->setBorderRadius(borderRadius);
    labTip->setArrowSize(arrowSize);
    labTip->setArrowPosition((NavLabel::ArrowPosition)arrowStyle);
    labTip->setBackground(background);
    labTip->setForeground(foreground);
    labTip->resize(labTipWidth, labTipHeight);
    labTip->setFont(labTipFont);

    labTip->setFocusPolicy(Qt::NoFocus);
    labTip->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    labTip->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setOrientation(Qt::Horizontal);
}

SliderTip::~SliderTip()
{
    labTip->deleteLater();
}

void SliderTip::mousePressEvent(QMouseEvent *e)
{
    //限定必须是鼠标左键按下
    if (e->button() != Qt::LeftButton) {
        return;
    }

    if (clickEnable) {
        //获取鼠标的位置
        double pos, value;
        if (orientation() == Qt::Horizontal) {
            pos = e->pos().x() / (double)width();
            value = pos * (maximum() - minimum()) + minimum();
        } else {
            pos = e->pos().y() / (double)height();
            value = maximum() - pos * (maximum() - minimum()) + minimum();
        }

        setValue(value + 0.5);

        //发送自定义的鼠标单击信号
        emit clicked();
    }

    mouseMoveEvent(e);
    labTip->setVisible(true);
    QSlider::mousePressEvent(e);
}

void SliderTip::mouseReleaseEvent(QMouseEvent *e)
{
    labTip->setVisible(false);
    QSlider::mouseReleaseEvent(e);
}

void SliderTip::mouseMoveEvent(QMouseEvent *e)
{
    //限定必须是鼠标左键按下
    if (e->button() & Qt::RightButton) {
        return;
    }

    //过滤掉控件外坐标,横向的限制X轴,纵向的限制Y轴
    QPoint pos = e->pos();
    int x = pos.x();
    int y = pos.y();

    if (orientation() == Qt::Horizontal) {
        if (x < 0 || x > width()) {
            return;
        }

        x = QCursor::pos().x();
        y = mapToGlobal(this->pos()).y();
        x = x - labTipWidth / 2 + this->x();
        y = y - (arrowStyle == ArrowStyle_Top ? -height() : labTipHeight);
    } else {
        if (y < 0 || y > height()) {
            return;
        }

        x = mapToGlobal(this->pos()).x();
        y = QCursor::pos().y();
        x = x - (arrowStyle == ArrowStyle_Left ? -width() : labTipWidth);
        y = y - labTipHeight / 2 + this->y();
    }

    QString str = QString("%1").arg(value());

    if (showTime) {
        uint length = value() / 1000;
        str = (QString("%1:%2").arg(length / 60, 2, 10, QChar('0')).arg(length % 60, 2, 10, QChar('0')));
    }

    labTip->setText(QString("%1%2").arg(str).arg(unit));
    labTip->move(this->mapFromParent(QPoint(x, y)));
    QSlider::mouseMoveEvent(e);
}

int SliderTip::getBorderRadius() const
{
    return this->borderRadius;
}

int SliderTip::getArrowSize() const
{
    return this->arrowSize;
}

SliderTip::ArrowStyle SliderTip::getArrowStyle() const
{
    return this->arrowStyle;
}

QColor SliderTip::getBackground() const
{
    return this->background;
}

QColor SliderTip::getForeground() const
{
    return this->foreground;
}

int SliderTip::getLabTipWidth() const
{
    return this->labTipWidth;
}

int SliderTip::getLabTipHeight() const
{
    return this->labTipHeight;
}

QFont SliderTip::getLabTipFont() const
{
    return this->labTipFont;
}

bool SliderTip::getShowTime() const
{
    return this->showTime;
}

bool SliderTip::getClickEnable() const
{
    return this->clickEnable;
}

QString SliderTip::getUnit() const
{
    return this->unit;
}

void SliderTip::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        labTip->setBorderRadius(borderRadius);
    }
}

void SliderTip::setArrowSize(int arrowSize)
{
    if (this->arrowSize != arrowSize) {
        this->arrowSize = arrowSize;
        labTip->setArrowSize(arrowSize);
    }
}

void SliderTip::setArrowStyle(const SliderTip::ArrowStyle &arrowStyle)
{
    if (this->arrowStyle != arrowStyle) {
        this->arrowStyle = arrowStyle;
        labTip->setArrowPosition((NavLabel::ArrowPosition)arrowStyle);
    }
}

void SliderTip::setBackground(const QColor &background)
{
    if (this->background != background) {
        this->background = background;
        labTip->setBackground(background);
    }
}

void SliderTip::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground) {
        this->foreground = foreground;
        labTip->setForeground(foreground);
    }
}

void SliderTip::setLabTipWidth(int labTipWidth)
{
    if (this->labTipWidth != labTipWidth) {
        this->labTipWidth = labTipWidth;
        labTip->resize(labTipWidth, labTipHeight);
    }
}

void SliderTip::setLabTipHeight(int labTipHeight)
{
    if (this->labTipHeight != labTipHeight) {
        this->labTipHeight = labTipHeight;
        labTip->resize(labTipWidth, labTipHeight);
    }
}

void SliderTip::setLabTipFont(const QFont &labTipFont)
{
    if (this->labTipFont != labTipFont) {
        this->labTipFont = labTipFont;
        labTip->setFont(labTipFont);
    }
}

void SliderTip::setShowTime(bool showTime)
{
    if (this->showTime != showTime) {
        this->showTime = showTime;
    }
}

void SliderTip::setClickEnable(bool clickEnable)
{
    if (this->clickEnable != clickEnable) {
        this->clickEnable = clickEnable;
    }
}

void SliderTip::setUnit(const QString &unit)
{
    if (this->unit != unit) {
        this->unit = unit;
    }
}

