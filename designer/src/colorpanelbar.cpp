#pragma execution_character_set("utf-8")

#include "colorpanelbar.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

ColorPanelBar::ColorPanelBar(QWidget *parent) : QWidget(parent)
{
    borderWidth = 2;
    borderRadius = 0;
    borderColor = QColor(255, 0, 0);

    autoHeight = true;
    percentHeight = 25;
    percentBorder = 2;
    percentRadius = 0;
    percentColor = QColor(240, 240, 240);

    topColor = QColor(255, 0, 0);
    bottomColor = QColor(0, 0, 0);
    disableColor = QColor(50, 50, 50);

    showOverlay = false;
    overlayColor = QColor(30, 30, 30);

    staticMode = true;
    outMode = false;
    hsbMode = false;
    showValue = false;

    minValue = 0.0;
    maxValue = 360.0;
    value = 360.0;
    percent = value / (maxValue - minValue) * 100;
    color = topColor;

    isPressed = false;
}

void ColorPanelBar::showEvent(QShowEvent *)
{
    //首次显示记住当前背景截图,用于获取颜色值
    bgPix = QPixmap(width(), height());
    bgPix.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&bgPix);

    QLinearGradient linearGradient;

    if (hsbMode) {
        //起始坐标和结束坐标换个位置可改变颜色顺序
        linearGradient.setStart(QPoint(bgRect.x(), bgRect.height()));
        linearGradient.setFinalStop(QPoint(bgRect.x(), bgRect.y()));

        //由下往上,饱和度百分值由0增加到1.0
        double step = 1.0 / 16;
        for (double i = 0; i <= 1.0; i += step) {
            linearGradient.setColorAt(i, QColor::fromHsvF(i, 1, 1, 1));
        }
    } else {
        linearGradient.setStart(QPointF(0, 0));
        linearGradient.setFinalStop(QPointF(0, height()));
        linearGradient.setColorAt(0.0, topColor);
        linearGradient.setColorAt(1.0, bottomColor);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(linearGradient);

    QRect rect(borderWidth / 2, borderWidth / 2, width() - borderWidth, height() - borderWidth);
    painter.drawRect(rect);
    painter.end();

    initColor();
}

void ColorPanelBar::resizeEvent(QResizeEvent *)
{
    if (autoHeight) {
        percentHeight = height() / 13;
    }

    rightHeight = height() - percentHeight - borderWidth * 2 - percentBorder * 2;
    if (outMode) {
        bgRect = QRect(borderWidth / 2, borderWidth / 2 + percentHeight / 2, width() - borderWidth, height() - borderWidth - percentHeight);
    } else {
        bgRect = QRect(borderWidth / 2, borderWidth / 2, width() - borderWidth, height() - borderWidth);
    }

    showEvent(NULL);
}

void ColorPanelBar::mousePressEvent(QMouseEvent *e)
{
    isPressed = true;
    mouseMoveEvent(e);    
}

void ColorPanelBar::mouseReleaseEvent(QMouseEvent *e)
{
    isPressed = false;
    mouseMoveEvent(e);
}

void ColorPanelBar::mouseMoveEvent(QMouseEvent *e)
{
    int y = e->pos().y();

    //Y轴必须是在高度范围内
    int topY = (y - percentHeight / 2);
    if (topY >= 0 && topY <= rightHeight && y < height()) {
        //自动计算纵坐标,转换成当前百分比
        percent = (1 - ((double)(y - percentHeight / 2) / rightHeight)) * 100;
        //计算当前百分比对应的当前值
        value = percent / 100 * (maxValue - minValue);
        //计算当前背景图片对应百分比处中心点像素
        initColor();
    } else if (topY <= 0) {
        value = maxValue;
        percent = 100.0;
        color = topColor;
    } else if (topY >= rightHeight) {
        value = minValue;
        percent = 0.0;
        color = bottomColor;
    }

    update();
    emit colorChanged(color, value, percent);
}

void ColorPanelBar::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景颜色
    drawBg(&painter);
    //绘制遮住颜色
    drawOverlay(&painter);
    //绘制百分比选中框
    drawPercent(&painter);
}

void ColorPanelBar::drawBg(QPainter *painter)
{
    painter->save();

    //不可用背景灰色
    if (isEnabled()) {
        QLinearGradient linearGradient;

        if (hsbMode) {
            //起始坐标和结束坐标换个位置可改变颜色顺序
            linearGradient.setStart(QPoint(bgRect.x(), bgRect.height()));
            linearGradient.setFinalStop(QPoint(bgRect.x(), bgRect.y()));

            //由下往上,饱和度百分值由0增加到1.0
            double step = 1.0 / 16;
            for (double i = 0; i <= 1.0; i += step) {
                linearGradient.setColorAt(i, QColor::fromHsvF(i, 1, 1, 1));
            }

            painter->setPen(Qt::NoPen);
        } else {
            linearGradient.setStart(QPointF(0, 0));
            linearGradient.setFinalStop(QPointF(0, height()));
            linearGradient.setColorAt(0.0, topColor);
            linearGradient.setColorAt(1.0, bottomColor);

            QPen pen;
            pen.setWidthF(borderWidth);
            pen.setColor(borderColor);
            pen.setCapStyle(Qt::RoundCap);
            pen.setJoinStyle(Qt::RoundJoin);
            painter->setPen(pen);
        }

        painter->setBrush(linearGradient);
    } else {
        painter->setPen(Qt::NoPen);
        painter->setBrush(disableColor);
    }

    painter->drawRoundedRect(bgRect, borderRadius, borderRadius);

    painter->restore();
}

void ColorPanelBar::drawOverlay(QPainter *painter)
{
    //如果没有启用绘制遮住颜色或者当前不可用则不用绘制
    if (!showOverlay || !isEnabled()) {
        return;
    }

    painter->save();

    //根据当前百分比计算高度
    int width = bgRect.width() - borderWidth;
    int height = bgRect.height() - borderWidth;
    height = height - ((double)percent / 100) * height;

    QRect overlayRect;
    if (outMode) {
        overlayRect = QRect(borderWidth, borderWidth + percentHeight / 2, width , height);
    } else {
        overlayRect = QRect(borderWidth, borderWidth, width , height);
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(overlayColor);
    painter->drawRect(overlayRect);

    painter->restore();
}

void ColorPanelBar::drawPercent(QPainter *painter)
{
    painter->save();

    //百分比选择框的区域要小于边框宽度,同时偏移一点,是的看起来美观
    int offset = borderWidth + 2;
    int y = rightHeight * (1 - percent / 100);

    //禁用状态颜色要变暗
    QPen pen;
    pen.setWidthF(percentBorder);
    pen.setColor(isEnabled() ? percentColor : disableColor.light(100));

    painter->setPen(pen);
    painter->setBrush(QColor(0, 0, 0, 50));

    QRect rect(offset, y + offset, width() - offset * 2, percentHeight);
    painter->drawRoundedRect(rect, percentRadius, percentRadius);

    QFont textFont;
    textFont.setPixelSize(rect.width() / 3);
    painter->setFont(textFont);

    if (showValue) {
        painter->drawText(rect, Qt::AlignCenter, QString("%1").arg(QString::number(value, 'f', 0)));
    } else {
        painter->drawText(rect, Qt::AlignCenter, QString("%1%").arg(QString::number(percent, 'f', 0)));
    }

    painter->restore();
}

void ColorPanelBar::initColor()
{
    int height = this->height();
    int posY = height - ((percent / 100) * height) + 1;
    if (posY >= height) {
        posY = height - 1;
    }

    color = bgPix.toImage().pixel(bgRect.width() / 2, posY);
}

int ColorPanelBar::getBorderWidth() const
{
    return this->borderWidth;
}

int ColorPanelBar::getBorderRadius() const
{
    return this->borderRadius;
}

QColor ColorPanelBar::getBorderColor() const
{
    return this->borderColor;
}

bool ColorPanelBar::getAutoHeight() const
{
    return this->autoHeight;
}

int ColorPanelBar::getPercentHeight() const
{
    return this->percentHeight;
}

int ColorPanelBar::getPercentBorder() const
{
    return this->percentBorder;
}

int ColorPanelBar::getPercentRadius() const
{
    return this->percentRadius;
}

QColor ColorPanelBar::getPercentColor() const
{
    return this->percentColor;
}

QColor ColorPanelBar::getTopColor() const
{
    return this->topColor;
}

QColor ColorPanelBar::getBottomColor() const
{
    return this->bottomColor;
}

QColor ColorPanelBar::getDisableColor() const
{
    return this->disableColor;
}

bool ColorPanelBar::getShowOverlay() const
{
    return this->showOverlay;
}

QColor ColorPanelBar::getOverlayColor() const
{
    return this->overlayColor;
}

bool ColorPanelBar::getStaticMode() const
{
    return this->staticMode;
}

bool ColorPanelBar::getOutMode() const
{
    return this->outMode;
}

bool ColorPanelBar::getHSBMode() const
{
    return this->hsbMode;
}

bool ColorPanelBar::getShowValue() const
{
    return this->showValue;
}

double ColorPanelBar::getMinValue() const
{
    return this->minValue;
}

double ColorPanelBar::getMaxValue() const
{
    return this->maxValue;
}

double ColorPanelBar::getValue() const
{
    return this->value;
}

double ColorPanelBar::getPercent() const
{
    return this->percent;
}

QColor ColorPanelBar::getColor() const
{
    return this->color;
}

QSize ColorPanelBar::sizeHint() const
{
    return QSize(50, 200);
}

QSize ColorPanelBar::minimumSizeHint() const
{
    return QSize(30, 120);
}

void ColorPanelBar::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        resizeEvent(NULL);
        update();
    }
}

void ColorPanelBar::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        update();
    }
}

void ColorPanelBar::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        update();
    }
}

void ColorPanelBar::setAutoHeight(bool autoHeight)
{
    if (this->autoHeight != autoHeight) {
        this->autoHeight = autoHeight;
        update();
    }
}

void ColorPanelBar::setPercentHeight(int percentHeight)
{
    if (this->percentHeight != percentHeight) {
        this->percentHeight = percentHeight;
        resizeEvent(NULL);
        update();
    }
}

void ColorPanelBar::setPercentBorder(int percentBorder)
{
    if (this->percentBorder != percentBorder) {
        this->percentBorder = percentBorder;
        resizeEvent(NULL);
        update();
    }
}

void ColorPanelBar::setPercentRadius(int percentRadius)
{
    if (this->percentRadius != percentRadius) {
        this->percentRadius = percentRadius;
        update();
    }
}

void ColorPanelBar::setPercentColor(const QColor &percentColor)
{
    if (this->percentColor != percentColor) {
        this->percentColor = percentColor;
        update();
    }
}

void ColorPanelBar::setTopColor(const QColor &topColor)
{
    if (this->topColor != topColor) {
        this->topColor = topColor;
        update();

        //非静态模式重新采样
        if (!staticMode) {
            showEvent(NULL);
        }
    }
}

void ColorPanelBar::setBottomColor(const QColor &bottomColor)
{
    if (this->bottomColor != bottomColor) {
        this->bottomColor = bottomColor;
        update();

        //非静态模式重新采样
        if (!staticMode) {
            showEvent(NULL);
        }
    }
}

void ColorPanelBar::setDisableColor(const QColor &disableColor)
{
    if (this->disableColor != disableColor) {
        this->disableColor = disableColor;
        update();
    }
}

void ColorPanelBar::setShowOverlay(bool showOverlay)
{
    if (this->showOverlay != showOverlay) {
        this->showOverlay = showOverlay;
        update();
    }
}

void ColorPanelBar::setOverlayColor(const QColor &overlayColor)
{
    if (this->overlayColor != overlayColor) {
        this->overlayColor = overlayColor;
        update();
    }
}

void ColorPanelBar::setStaticMode(bool staticMode)
{
    if (this->staticMode != staticMode) {
        this->staticMode = staticMode;
        update();
    }
}

void ColorPanelBar::setOutMode(bool outMode)
{
    if (this->outMode != outMode) {
        this->outMode = outMode;
        update();
    }
}

void ColorPanelBar::setHSBMode(bool hsbMode)
{
    if (this->hsbMode != hsbMode) {
        this->hsbMode = hsbMode;
        update();
    }
}

void ColorPanelBar::setShowValue(bool showValue)
{
    if (this->showValue != showValue) {
        this->showValue = showValue;
        update();
    }
}

void ColorPanelBar::setMinValue(double minValue)
{
    if (this->minValue != minValue) {
        this->minValue = minValue;
        percent = value / (maxValue - minValue) * 100;
        update();
    }
}

void ColorPanelBar::setMinValue(int minValue)
{
    setMinValue((double)minValue);
}

void ColorPanelBar::setMaxValue(double maxValue)
{
    if (this->maxValue != maxValue) {
        this->maxValue = maxValue;
        percent = value / (maxValue - minValue) * 100;
        update();
    }
}

void ColorPanelBar::setMaxValue(int maxValue)
{
    setMaxValue(maxValue);
}

void ColorPanelBar::setValue(double value)
{
    if (this->value != value && value >= minValue && value <= maxValue) {
        this->value = value;
        percent = value / (maxValue - minValue) * 100;
        update();
    }
}

void ColorPanelBar::setValue(int value)
{
    setValue((double)value);
}

void ColorPanelBar::setPercent(double percent)
{
    if (this->percent != percent) {
        this->percent = percent;
        value = percent / 100 * (maxValue - minValue);
        update();
    }
}

void ColorPanelBar::setPercent(int percent)
{
    setPercent((double)percent);
}
