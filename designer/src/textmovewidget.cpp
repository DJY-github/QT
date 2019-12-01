#pragma execution_character_set("utf-8")

#include "textmovewidget.h"
#include "qdatetime.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qlabel.h"
#include "qdebug.h"

TextMoveWidget::TextMoveWidget(QWidget *parent) : QWidget(parent)
{
    step = 2;
    interval = 20;
    sleep = 2;

    mouseHoverStop = false;
    moveStyle = MoveStyle_LeftAndRight;

    mouseHover = false;
    moveRight = true;
    initX = 0;
    initY = 0;

    labText = new QLabel(this);
    labText->setAlignment(Qt::AlignVCenter);
    //labText->setFrameShape(QLabel::Box);
    labText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    lastTime = QDateTime::fromString("1970-01-01 00:00:00", "yyyy-MM-dd HH:mm:ss");
    timer = new QTimer(this);
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePos()));
    timer->start();

    setText("0123456789");
    setTextSize(12);
    setForeground(QColor(100, 184, 255));
    setBackground(QColor(22, 22, 22));
}

TextMoveWidget::~TextMoveWidget()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void TextMoveWidget::resizeEvent(QResizeEvent *)
{
    initY = (height() - labText->height()) / 2;
}

void TextMoveWidget::enterEvent(QEvent *)
{
    mouseHover = true;
    if (mouseHoverStop) {
        QFont font = labText->font();
        font.setUnderline(true);
        labText->setFont(font);
        this->setCursor(Qt::PointingHandCursor);
    }
}

void TextMoveWidget::leaveEvent(QEvent *)
{
    mouseHover = false;
    if (mouseHoverStop) {
        QFont font = labText->font();
        font.setUnderline(false);
        labText->setFont(font);
        this->setCursor(Qt::ArrowCursor);
    }
}

void TextMoveWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), background);

    //居中绘制静态文本
    if (!staticText.isEmpty()) {
        painter.setPen(this->foreground);
        painter.drawText(this->rect(), Qt::AlignCenter, staticText);
    }
}

void TextMoveWidget::updatePos()
{
    if (mouseHoverStop && mouseHover) {
        return;
    }

    //判断设置静态文本的时间,未超过静态停留时间则返回
    QDateTime now = QDateTime::currentDateTime();
    int timeout = lastTime.secsTo(now);
    if (timeout < sleep) {
        return;
    }  else if (timeout == sleep && !staticText.isEmpty()) {
        staticText.clear();
        this->update();
    }

    labText->setVisible(true);
    int textWidth = this->fontMetrics().width(text);
    if (moveStyle == MoveStyle_LeftAndRight) {
        if (textWidth <= width()) {
            if (initX + textWidth > width()) {
                moveRight = false;
            } else if (initX <= 0) {
                moveRight = true;
            }
        } else {
            if (initX == 10) {
                moveRight = false;
            } else if (initX <= width() - textWidth - 10) {
                moveRight = true;
            }
        }

        if (moveRight) {
            initX += step;
        } else {
            initX -= step;
        }

        labText->move(initX, initY);
    } else if (moveStyle == MoveStyle_LeftToRight) {
        if (initX > width()) {
            initX = -textWidth;
        }

        initX += step;
        labText->move(initX, initY);
    } else if (moveStyle == MoveStyle_RightToLeft) {
        if (initX < -textWidth) {
            initX = width();
        }

        initX -= step;
        labText->move(initX, initY);
    }
}

int TextMoveWidget::getStep() const
{
    return this->step;
}

int TextMoveWidget::getInterval() const
{
    return this->interval;
}

int TextMoveWidget::getSleep() const
{
    return this->sleep;
}

QString TextMoveWidget::getStaticText() const
{
    return this->staticText;
}

QString TextMoveWidget::getText() const
{
    return this->text;
}

int TextMoveWidget::getTextSize() const
{
    return this->textSize;
}

QColor TextMoveWidget::getForeground() const
{
    return this->foreground;
}

QColor TextMoveWidget::getBackground() const
{
    return this->background;
}

bool TextMoveWidget::getMouseHoverStop() const
{
    return this->mouseHoverStop;
}

TextMoveWidget::MoveStyle TextMoveWidget::getMoveStyle() const
{
    return this->moveStyle;
}

QSize TextMoveWidget::sizeHint() const
{
    return QSize(200, 30);
}

QSize TextMoveWidget::minimumSizeHint() const
{
    return QSize(30, 10);
}

void TextMoveWidget::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
    }
}

void TextMoveWidget::setInterval(int interval)
{
    if (this->interval != interval) {
        this->interval = interval;
        timer->setInterval(interval);
    }
}

void TextMoveWidget::setSleep(int sleep)
{
    if (this->sleep != sleep) {
        this->sleep = sleep;
    }
}

void TextMoveWidget::setText(const QString &text)
{
    if (this->text != text) {
        this->text = text;
        labText->setText(text);

        //自动拉伸标签载体尺寸
        int textWidth = fontMetrics().width(text);
        int textHeight = fontMetrics().height();
        labText->resize(QSize(textWidth + 15, textHeight));

        if (moveStyle == MoveStyle_LeftAndRight) {
            initX = 0;
        } else if (moveStyle == MoveStyle_LeftToRight) {
            initX = -labText->width();
        } else if (moveStyle == MoveStyle_RightToLeft) {
            initX = width();
        }
    }
}

void TextMoveWidget::setTextSize(int textSize)
{
    if (this->textSize != textSize) {
        QFont font;
        font.setPixelSize(textSize);
        this->setFont(font);

        this->textSize = textSize;
        labText->setStyleSheet(QString("color:%1;font-size:%2px;").arg(foreground.name()).arg(textSize));

        //自动拉伸标签载体尺寸
        int textWidth = fontMetrics().width(text);
        int textHeight = fontMetrics().height();
        labText->resize(QSize(textWidth + 15, textHeight));
    }
}

void TextMoveWidget::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground) {
        this->foreground = foreground;
        labText->setStyleSheet(QString("color:%1;font-size:%2px;").arg(foreground.name()).arg(textSize));
    }
}

void TextMoveWidget::setBackground(const QColor &background)
{
    if (this->background != background) {
        this->background = background;
        this->update();
    }
}

void TextMoveWidget::setMouseHoverStop(bool mouseHoverStop)
{
    if (this->mouseHoverStop != mouseHoverStop) {
        this->mouseHoverStop = mouseHoverStop;
    }
}

void TextMoveWidget::setMoveStyle(const TextMoveWidget::MoveStyle &moveStyle)
{
    if (this->moveStyle != moveStyle) {
        this->moveStyle = moveStyle;
    }
}

void TextMoveWidget::setStaticText(const QString &staticText)
{
    labText->setVisible(false);
    lastTime = QDateTime::currentDateTime();
    this->staticText = staticText;
    this->update();
}
