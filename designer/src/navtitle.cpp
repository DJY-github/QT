#pragma execution_character_set("utf-8")

#include "navtitle.h"
#include "qfontdatabase.h"
#include "qpainter.h"
#include "qevent.h"
#include "qdebug.h"

NavTitle::NavTitle(QWidget *parent) : QWidget(parent)
{
    leftIcon = 0xf0e8;
    rightIcon1 = 0;
    rightIcon2 = 0;
    rightIcon3 = 0;
    rightIcon4 = 0;
    rightIcon5 = 0xf00d;

    padding = 8;
    iconSize = 20;
    textCenter = false;
    text = "";

    bgColor = QColor("#40444D");
    textColor = QColor("#FAF6F7");
    borderColor = QColor("#32363F");

    iconNormalColor = QColor("#FAF6F7");
    iconHoverColor = QColor("#22A3A9");
    iconPressColor = QColor("#0E99A0");

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

    pressed = false;
    setMouseTracking(true);
}

void NavTitle::resizeEvent(QResizeEvent *)
{
    //重新计算图标位置区域
    leftRect = QRect(padding, 0, iconSize, this->height());
    rightRect1 = QRect(this->width() - (iconSize * 5) - padding, 0, iconSize, this->height());
    rightRect2 = QRect(this->width() - (iconSize * 4) - padding, 0, iconSize, this->height());
    rightRect3 = QRect(this->width() - (iconSize * 3) - padding, 0, iconSize, this->height());
    rightRect4 = QRect(this->width() - (iconSize * 2) - padding, 0, iconSize, this->height());
    rightRect5 = QRect(this->width() - (iconSize * 1) - padding, 0, iconSize, this->height());
}

void NavTitle::leaveEvent(QEvent *)
{
    pressed = false;
    lastPoint = QPoint(-1, -1);
    update();
}

void NavTitle::mousePressEvent(QMouseEvent *e)
{
    pressed = true;
    lastPoint = e->pos();
    update();

    if (leftRect.contains(lastPoint)) {
        emit mousePressed(1);
    } else if (rightRect1.contains(lastPoint)) {
        emit mousePressed(2);
    } else if (rightRect2.contains(lastPoint)) {
        emit mousePressed(3);
    } else if (rightRect3.contains(lastPoint)) {
        emit mousePressed(4);
    } else if (rightRect4.contains(lastPoint)) {
        emit mousePressed(5);
    } else if (rightRect5.contains(lastPoint)) {
        emit mousePressed(6);
    } else {
        emit mousePressed(0);
    }
}

void NavTitle::mouseMoveEvent(QMouseEvent *e)
{
    lastPoint = e->pos();
    update();
}

void NavTitle::mouseReleaseEvent(QMouseEvent *e)
{
    pressed = false;
    update();

    if (leftRect.contains(lastPoint)) {
        emit mouseReleased(1);
    } else if (rightRect1.contains(lastPoint)) {
        emit mouseReleased(2);
    } else if (rightRect2.contains(lastPoint)) {
        emit mouseReleased(3);
    } else if (rightRect3.contains(lastPoint)) {
        emit mouseReleased(4);
    } else if (rightRect4.contains(lastPoint)) {
        emit mouseReleased(5);
    } else if (rightRect5.contains(lastPoint)) {
        emit mouseReleased(6);
    } else {
        emit mouseReleased(0);
    }
}

void NavTitle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景+边框
    painter.setPen(Qt::NoPen);
    painter.setBrush(bgColor);
    painter.drawRect(this->rect());

    QFont font;
    font.setPixelSize(15);
    painter.setFont(font);

    //绘制文字
    if (!text.isEmpty()) {
        painter.setPen(textColor);
        QRect textRect(iconSize + (padding * 1.5), 0, this->width(), this->height());
        if (textCenter) {
            painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignVCenter, text);
        } else {
            painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
        }
    }

    font = iconFont;
    font.setPixelSize(iconSize - 5);
    painter.setFont(font);

    //绘制左侧图标
    if (leftIcon != 0) {
        painter.drawText(leftRect, Qt::AlignHCenter | Qt::AlignVCenter, QChar(leftIcon));
    }

    //绘制右侧图标1
    drawIcon(&painter, rightRect1, rightIcon1);
    //绘制右侧图标2
    drawIcon(&painter, rightRect2, rightIcon2);
    //绘制右侧图标3
    drawIcon(&painter, rightRect3, rightIcon3);
    //绘制右侧图标4
    drawIcon(&painter, rightRect4, rightIcon4);
    //绘制右侧图标5
    drawIcon(&painter, rightRect5, rightIcon5);
}

void NavTitle::drawIcon(QPainter *painter, const QRect &rect, int icon)
{
    if (icon != 0) {
        if (rect.contains(lastPoint)) {
            painter->setPen(pressed ? iconPressColor : iconHoverColor);
        } else {
            painter->setPen(iconNormalColor);
        }

        painter->drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, QChar(icon));
    }
}

int NavTitle::getLeftIcon() const
{
    return this->leftIcon;
}

int NavTitle::getRightIcon1() const
{
    return this->rightIcon1;
}

int NavTitle::getRightIcon2() const
{
    return this->rightIcon2;
}

int NavTitle::getRightIcon3() const
{
    return this->rightIcon3;
}

int NavTitle::getRightIcon4() const
{
    return this->rightIcon4;
}

int NavTitle::getRightIcon5() const
{
    return this->rightIcon5;
}

int NavTitle::getPadding() const
{
    return this->padding;
}

int NavTitle::getIconSize() const
{
    return this->iconSize;
}

bool NavTitle::getTextCenter() const
{
    return this->textCenter;
}

QString NavTitle::getText() const
{
    return this->text;
}

QColor NavTitle::getBgColor() const
{
    return this->bgColor;
}

QColor NavTitle::getTextColor() const
{
    return this->textColor;
}

QColor NavTitle::getBorderColor() const
{
    return this->borderColor;
}

QColor NavTitle::getIconNormalColor() const
{
    return this->iconNormalColor;
}

QColor NavTitle::getIconHoverColor() const
{
    return this->iconHoverColor;
}

QColor NavTitle::getIconPressColor() const
{
    return this->iconPressColor;
}

QSize NavTitle::sizeHint() const
{
    return QSize(100, 25);
}

QSize NavTitle::minimumSizeHint() const
{
    return QSize(50, 15);
}

void NavTitle::setLeftIcon(int leftIcon)
{
    if (this->leftIcon != leftIcon) {
        this->leftIcon = leftIcon;
        update();
    }
}

void NavTitle::setRightIcon1(int rightIcon1)
{
    if (this->rightIcon1 != rightIcon1) {
        this->rightIcon1 = rightIcon1;
        update();
    }
}

void NavTitle::setRightIcon2(int rightIcon2)
{
    if (this->rightIcon2 != rightIcon2) {
        this->rightIcon2 = rightIcon2;
        update();
    }
}

void NavTitle::setRightIcon3(int rightIcon3)
{
    if (this->rightIcon3 != rightIcon3) {
        this->rightIcon3 = rightIcon3;
        update();
    }
}

void NavTitle::setRightIcon4(int rightIcon4)
{
    if (this->rightIcon4 != rightIcon4) {
        this->rightIcon4 = rightIcon4;
        update();
    }
}

void NavTitle::setRightIcon5(int rightIcon5)
{
    if (this->rightIcon5 != rightIcon5) {
        this->rightIcon5 = rightIcon5;
        update();
    }
}

void NavTitle::setPadding(int padding)
{
    if (this->padding != padding) {
        this->padding = padding;
        update();
    }
}

void NavTitle::setIconSize(int iconSize)
{
    if (this->iconSize != iconSize) {
        this->iconSize = iconSize;
        update();
    }
}

void NavTitle::setTextCenter(bool textCenter)
{
    if (this->textCenter != textCenter) {
        this->textCenter = textCenter;
        update();
    }
}

void NavTitle::setText(const QString &text)
{
    if (this->text != text) {
        this->text = text;
        update();
    }
}

void NavTitle::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void NavTitle::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void NavTitle::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        update();
    }
}

void NavTitle::setIconNormalColor(const QColor &iconNormalColor)
{
    if (this->iconNormalColor != iconNormalColor) {
        this->iconNormalColor = iconNormalColor;
        update();
    }
}

void NavTitle::setIconHoverColor(const QColor &iconHoverColor)
{
    if (this->iconHoverColor != iconHoverColor) {
        this->iconHoverColor = iconHoverColor;
        update();
    }
}

void NavTitle::setIconPressColor(const QColor &iconPressColor)
{
    if (this->iconPressColor != iconPressColor) {
        this->iconPressColor = iconPressColor;
        update();
    }
}
