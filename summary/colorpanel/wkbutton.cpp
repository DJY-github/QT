#pragma execution_character_set("utf-8")

#include "wkbutton.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

WKButton::WKButton(QWidget *parent) : QWidget(parent)
{
    borderRadius = 5;
    borderWidth = 2;
    borderColor = QColor(180, 180, 180);

    showSuperText = false;
    superText = "1";
    superTextFont = this->font();
    superTextAlign = TextAlign_Top_Left;
    superTextColor = QColor(230, 230, 230);

    text = "";
    textFont = this->font();
    textAlign = TextAlign_Center_Center;
    textColor = QColor(230, 230, 230);

    normalColor = QColor(80, 80, 80);
    pressedColor = QColor(30, 30, 30);

    canMove = false;
    bgImage = QPixmap();
    colorMode = ColorMode_Normal;

    isPressed = false;

    this->installEventFilter(this);
}

void WKButton::mousePressEvent(QMouseEvent *)
{
    if (!isEnabled()) {
        return;
    }

    emit clicked();
}

bool WKButton::eventFilter(QObject *watched, QEvent *event)
{
    if (!isEnabled()) {
        return QWidget::eventFilter(watched, event);
    }

    static QPoint lastPoint;

    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        if (this->rect().contains(e->pos()) && (e->button() == Qt::LeftButton)) {
            lastPoint = e->pos();
            isPressed = true;
            update();
        }
    } else if (event->type() == QEvent::MouseMove && isPressed && canMove) {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        int dx = e->pos().x() - lastPoint.x();
        int dy = e->pos().y() - lastPoint.y();
        this->move(this->x() + dx, this->y() + dy);
        return true;
    } else if (event->type() == QEvent::MouseButtonRelease && isPressed) {
        isPressed = false;
        update();
    }

    return QWidget::eventFilter(watched, event);
}

void WKButton::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制文字
    drawText(&painter);
}

void WKButton::drawBg(QPainter *painter)
{
    painter->save();

    //设置边框颜色及宽度
    QPen pen;
    pen.setColor(borderColor);
    pen.setWidthF(borderWidth);
    painter->setPen(pen);

    //绘制区域要减去边框宽度
    QRect rect;
    rect.setX(borderWidth);
    rect.setY(borderWidth);
    rect.setWidth(width() - borderWidth * 2);
    rect.setHeight(height() - borderWidth * 2);

    //如果背景图片存在则显示背景图片,否则显示背景色
    if (!bgImage.isNull()) {
        //等比例缩放绘制
        QPixmap img = bgImage.scaled(rect.width(), rect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap((this->rect().width() - img.width()) / 2, (this->rect().height() - img.height()) / 2, img);
    } else {
        if (colorMode == ColorMode_Normal) {
            if (isPressed) {
                painter->setBrush(QBrush(pressedColor));
            } else {
                painter->setBrush(QBrush(normalColor));
            }
        } else if (colorMode == ColorMode_Replace) {
            QLinearGradient gradient(QPoint(0, 0), QPoint(0, height()));

            if (isPressed) {
                gradient.setColorAt(0.0, pressedColor);
                gradient.setColorAt(0.49, pressedColor);
                gradient.setColorAt(0.50, normalColor);
                gradient.setColorAt(1.0, normalColor);
            } else {
                gradient.setColorAt(0.0, normalColor);
                gradient.setColorAt(0.49, normalColor);
                gradient.setColorAt(0.50, pressedColor);
                gradient.setColorAt(1.0, pressedColor);
            }

            painter->setBrush(gradient);
        } else if (colorMode == ColorMode_Shade) {
            QLinearGradient gradient(QPoint(0, 0), QPoint(0, height()));

            if (isPressed) {
                gradient.setColorAt(0.0, pressedColor);
                gradient.setColorAt(1.0, normalColor);
            } else {
                gradient.setColorAt(0.0, normalColor);
                gradient.setColorAt(1.0, pressedColor);
            }

            painter->setBrush(gradient);
        }

        painter->drawRoundedRect(rect, borderRadius, borderRadius);
    }

    painter->restore();
}

void WKButton::drawText(QPainter *painter)
{
    if (!bgImage.isNull()) {
        return;
    }

    painter->save();

    //如果要显示角标,则重新计算显示文字的区域
    if (showSuperText) {
        int offset = 3;
        QRect rect;
        rect.setX(borderWidth * offset);
        rect.setY(borderWidth);
        rect.setWidth(width() - borderWidth * offset * 2);
        rect.setHeight(height() - borderWidth * 2);

        Qt::Alignment alignment = Qt::AlignCenter;
        if (superTextAlign == TextAlign_Top_Left) {
            alignment = Qt::AlignTop | Qt::AlignLeft;
        } else if (superTextAlign == TextAlign_Top_Center) {
            alignment = Qt::AlignTop | Qt::AlignHCenter;
        } else if (superTextAlign == TextAlign_Top_Right) {
            alignment = Qt::AlignTop | Qt::AlignRight;
        } else if (superTextAlign == TextAlign_Center_Left) {
            alignment = Qt::AlignLeft | Qt::AlignVCenter;
        } else if (superTextAlign == TextAlign_Center_Center) {
            alignment = Qt::AlignHCenter | Qt::AlignVCenter;
        } else if (superTextAlign == TextAlign_Center_Right) {
            alignment = Qt::AlignRight | Qt::AlignVCenter;
        } else if (superTextAlign == TextAlign_Bottom_Left) {
            alignment = Qt::AlignBottom | Qt::AlignLeft;
        } else if (superTextAlign == TextAlign_Bottom_Center) {
            alignment = Qt::AlignBottom | Qt::AlignHCenter;
        } else if (superTextAlign == TextAlign_Bottom_Right) {
            alignment = Qt::AlignBottom | Qt::AlignRight;
        }

        //绘制角标
        painter->setPen(superTextColor);
        painter->setFont(superTextFont);
        painter->drawText(rect, alignment, superText);
    }

    int offset = 5;
    QRect rect;
    rect.setX(borderWidth * offset);
    rect.setY(borderWidth);
    rect.setWidth(width() - borderWidth * offset * 2);
    rect.setHeight(height() - borderWidth * 2);

    Qt::Alignment alignment = Qt::AlignCenter;
    if (textAlign == TextAlign_Top_Left) {
        alignment = Qt::AlignTop | Qt::AlignLeft;
    } else if (textAlign == TextAlign_Top_Center) {
        alignment = Qt::AlignTop | Qt::AlignHCenter;
    } else if (textAlign == TextAlign_Top_Right) {
        alignment = Qt::AlignTop | Qt::AlignRight;
    } else if (textAlign == TextAlign_Center_Left) {
        alignment = Qt::AlignLeft | Qt::AlignVCenter;
    } else if (textAlign == TextAlign_Center_Center) {
        alignment = Qt::AlignHCenter | Qt::AlignVCenter;
    } else if (textAlign == TextAlign_Center_Right) {
        alignment = Qt::AlignRight | Qt::AlignVCenter;
    } else if (textAlign == TextAlign_Bottom_Left) {
        alignment = Qt::AlignBottom | Qt::AlignLeft;
    } else if (textAlign == TextAlign_Bottom_Center) {
        alignment = Qt::AlignBottom | Qt::AlignHCenter;
    } else if (textAlign == TextAlign_Bottom_Right) {
        alignment = Qt::AlignBottom | Qt::AlignRight;
    }

    painter->setPen(textColor);
    painter->setFont(textFont);
    painter->drawText(rect, alignment, text);

    painter->restore();
}

int WKButton::getBorderRadius() const
{
    return this->borderRadius;
}

int WKButton::getBorderWidth() const
{
    return this->borderWidth;
}

QColor WKButton::getBorderColor() const
{
    return this->borderColor;
}

bool WKButton::getShowSuperText() const
{
    return this->showSuperText;
}

QString WKButton::getSuperText() const
{
    return this->superText;
}

QFont WKButton::getSuperTextFont() const
{
    return this->superTextFont;
}

WKButton::TextAlign WKButton::getSuperTextAlign() const
{
    return this->superTextAlign;
}

QColor WKButton::getSuperTextColor() const
{
    return this->superTextColor;
}

QString WKButton::getText() const
{
    return this->text;
}

QFont WKButton::getTextFont() const
{
    return this->textFont;
}

WKButton::TextAlign WKButton::getTextAlign() const
{
    return this->textAlign;
}

QColor WKButton::getTextColor() const
{
    return this->textColor;
}

QColor WKButton::getNormalColor() const
{
    return this->normalColor;
}

QColor WKButton::getPressedColor() const
{
    return this->pressedColor;
}

bool WKButton::getCanMove() const
{
    return this->canMove;
}

QPixmap WKButton::getBgImage() const
{
    return this->bgImage;
}

WKButton::ColorMode WKButton::getColorMode() const
{
    return this->colorMode;
}

QSize WKButton::sizeHint() const
{
    return QSize(100, 50);
}

QSize WKButton::minimumSizeHint() const
{
    return QSize(30, 20);
}

void WKButton::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        update();
    }
}

void WKButton::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        update();
    }
}

void WKButton::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        update();
    }
}

void WKButton::setShowSuperText(bool showSuperText)
{
    if (this->showSuperText != showSuperText) {
        this->showSuperText = showSuperText;
        update();
    }
}

void WKButton::setSuperText(const QString &superText)
{
    if (this->superText != superText) {
        this->superText = superText;
        update();
    }
}

void WKButton::setSuperTextFont(const QFont &superTextFont)
{
    if (this->superTextFont != superTextFont) {
        this->superTextFont = superTextFont;
        update();
    }
}

void WKButton::setSuperTextAlign(const WKButton::TextAlign &superTextAlign)
{
    if (this->superTextAlign != superTextAlign) {
        this->superTextAlign = superTextAlign;
        update();
    }
}

void WKButton::setSuperTextColor(const QColor &superTextColor)
{
    if (this->superTextColor != superTextColor) {
        this->superTextColor = superTextColor;
        update();
    }
}

void WKButton::setText(const QString &text)
{
    if (this->text != text) {
        this->text = text;
        update();
    }
}

void WKButton::setTextFont(const QFont &textFont)
{
    if (this->textFont != textFont) {
        this->textFont = textFont;
        update();
    }
}

void WKButton::setTextAlign(const TextAlign &textAlign)
{
    if (this->textAlign != textAlign) {
        this->textAlign = textAlign;
        update();
    }
}

void WKButton::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void WKButton::setNormalColor(const QColor &normalColor)
{
    if (this->normalColor != normalColor) {
        this->normalColor = normalColor;
        update();
    }
}

void WKButton::setPressedColor(const QColor &pressedColor)
{
    if (this->pressedColor != pressedColor) {
        this->pressedColor = pressedColor;
        update();
    }
}

void WKButton::setCanMove(bool canMove)
{
    if (this->canMove != canMove) {
        this->canMove = canMove;
    }
}

void WKButton::setBgImage(const QPixmap &bgImage)
{
    this->bgImage = bgImage;
    update();
}

void WKButton::setColorMode(const WKButton::ColorMode &colorMode)
{
    if (this->colorMode != colorMode) {
        this->colorMode = colorMode;
        update();
    }
}
