#pragma execution_character_set("utf-8")

#include "videoplayback.h"
#include "qpainter.h"
#include "qevent.h"
#include "qlayout.h"
#include "qlabel.h"
#include "qdebug.h"

//顶部时间控件
VideoTime::VideoTime(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 60;
    value = 0;
    longStep = 10;
    shortStep = 1;

    textColor = QColor(255, 255, 255);
    bgColor = QColor(60, 60, 60);
}

void VideoTime::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制标尺
    drawRuler(&painter);
}

void VideoTime::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawRect(rect());
    painter->restore();
}

void VideoTime::drawRuler(QPainter *painter)
{
    painter->save();
    painter->setPen(textColor);

    double initX = 0;

    //绘制横向标尺下部分底部线
    double initBottomY = height();
    QPointF lineBottomLeftPot = QPointF(initX, initBottomY);
    QPointF lineBottomRightPot = QPointF(width() - initX, initBottomY);
    painter->drawLine(lineBottomLeftPot, lineBottomRightPot);

    //计算每一格移动多少
    double increment = width() / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 6;

    //根据范围值绘制刻度值及刻度值 长线条需要移动10像素 短线条需要移动5像素
    for (int i = minValue; i <= maxValue; i = i + shortStep) {
        if (i % longStep == 0) {
            QPointF topPot = QPointF(initX, initBottomY);
            QPointF bottomPot = QPointF(initX, initBottomY - longLineLen);
            painter->drawLine(topPot, bottomPot);

            //第一个值和最后一个值不要绘制
            if (i == minValue || i == maxValue) {
                initX += increment * shortStep;
                continue;
            }

            QString strValue = QString("08:%1").arg(i);
            double textWidth = fontMetrics().width(strValue);
            QPointF textPot = QPointF(initX - textWidth / 2, initBottomY - longLineLen - 3);
            painter->drawText(textPot, strValue);
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 10;
            } else {
                shortLineLen = 6;
            }

            QPointF topPot = QPointF(initX, initBottomY);
            QPointF bottomPot = QPointF(initX, initBottomY - shortLineLen);
            painter->drawLine(topPot, bottomPot);
        }

        initX += increment * shortStep;
    }

    painter->restore();
}

void VideoTime::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void VideoTime::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

//通道控件
VideoCh::VideoCh(QWidget *parent) : QWidget(parent)
{
    chColor = QColor(240, 240, 240);
    dataColor = QColor(77, 206, 247);
}

void VideoCh::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制数据
    drawData(&painter);
}

void VideoCh::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(chColor);
    painter->drawRect(rect());
    painter->restore();
}

void VideoCh::drawData(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(dataColor);

    //逐个绘制有数据
    for (int i = 0; i < datas.count(); i++) {
        VideoData data = datas.at(i);
        painter->drawRect(QRect(data.startX, 0, data.length, height()));
    }

    painter->restore();
}

void VideoCh::setChColor(const QColor &chColor)
{
    if (this->chColor != chColor) {
        this->chColor = chColor;
        this->update();
    }
}

void VideoCh::setDataColor(const QColor &dataColor)
{
    if (this->dataColor != dataColor) {
        this->dataColor = dataColor;
        this->update();
    }
}

void VideoCh::setDatas(const QList<VideoData> &datas)
{
    this->datas = datas;
    this->update();
}


//完整控件
VideoPlayback::VideoPlayback(QWidget *parent) : QWidget(parent)
{
    margin = 0;
    spacing = 0;
    labWidth = 49;

    textCh1 = "通道";
    textCh2 = "通道";
    textCh3 = "通道";
    textCh4 = "通道";

    lineWidth = 2;
    lineColor = QColor(214, 77, 84);
    textColor = QColor(230, 230, 231);
    bgColor = QColor(60, 60, 61);

    videoTextColor = QColor(255, 255, 255);
    videoBgColor = QColor(60, 60, 60);
    videoChColor = QColor(240, 240, 240);
    videoDataColor = QColor(77, 206, 247);

    this->initControl();
    this->setMargin(2);
    this->setSpacing(2);
    this->setLabWidth(50);
    this->setTextCh("通道 1", "通道 2", "通道 3", "通道 4");
    this->setTextColor(QColor(230, 230, 230));
    this->setBgColor(QColor(60, 60, 60));
}

bool VideoPlayback::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == labFlow) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            pressPos = mouseEvent->pos();
            labFlow->update();
        } else if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            pressPos = mouseEvent->pos();
            labFlow->update();
        } else if (event->type() == QEvent::Paint) {
            QPainter painter;
            painter.begin(labFlow);
            painter.setPen(QPen(lineColor, lineWidth));
            QPoint pointTop(pressPos.x(), 0);
            QPoint pointBottom(pressPos.x(), height());
            painter.drawLine(pointTop, pointBottom);
            painter.end();
        }
    }

    return QWidget::eventFilter(watched, event);
}

void VideoPlayback::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), bgColor);
}

void VideoPlayback::resizeEvent(QResizeEvent *)
{
    labFlow->resize(this->size());
}

int VideoPlayback::getMargin() const
{
    return this->margin;
}

int VideoPlayback::getSpacing() const
{
    return this->spacing;
}

int VideoPlayback::getLabWidth() const
{
    return this->labWidth;
}

QString VideoPlayback::getTextCh1() const
{
    return this->textCh1;
}

QString VideoPlayback::getTextCh2() const
{
    return this->textCh2;
}

QString VideoPlayback::getTextCh3() const
{
    return this->textCh3;
}

QString VideoPlayback::getTextCh4() const
{
    return this->textCh4;
}

int VideoPlayback::getLineWidth() const
{
    return this->lineWidth;
}

QColor VideoPlayback::getLineColor() const
{
    return this->lineColor;
}

QColor VideoPlayback::getTextColor() const
{
    return this->textColor;
}

QColor VideoPlayback::getBgColor() const
{
    return this->bgColor;
}

QColor VideoPlayback::getVideoTextColor() const
{
    return this->videoTextColor;
}

QColor VideoPlayback::getVideoBgColor() const
{
    return this->videoBgColor;
}

QColor VideoPlayback::getVideoChColor() const
{
    return this->videoChColor;
}

QColor VideoPlayback::getVideoDataColor() const
{
    return this->videoDataColor;
}

QSize VideoPlayback::sizeHint() const
{
    return QSize(500, 110);
}

QSize VideoPlayback::minimumSizeHint() const
{
    return QSize(100, 50);
}

void VideoPlayback::initControl()
{
    //表格布局,左侧为标签显示文字标识,右侧顶部为时间控件,下面为4个通道的控件
    layout = new QGridLayout;
    this->setLayout(layout);

    labTime = new QLabel;
    layout->addWidget(labTime, 0, 0);
    videoTime = new VideoTime;
    videoTime->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(videoTime, 0, 1);

    labCh1 = new QLabel;
    labCh1->setAlignment(Qt::AlignCenter);
    layout->addWidget(labCh1, 1, 0);
    videoCh1 = new VideoCh;
    videoCh1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(videoCh1, 1, 1);

    labCh2 = new QLabel;
    labCh2->setAlignment(Qt::AlignCenter);
    layout->addWidget(labCh2, 2, 0);
    videoCh2 = new VideoCh;
    videoCh2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(videoCh2, 2, 1);

    labCh3 = new QLabel;
    labCh3->setAlignment(Qt::AlignCenter);
    layout->addWidget(labCh3, 3, 0);
    videoCh3 = new VideoCh;
    videoCh3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(videoCh3, 3, 1);

    labCh4 = new QLabel;
    labCh4->setAlignment(Qt::AlignCenter);
    layout->addWidget(labCh4, 4, 0);
    videoCh4 = new VideoCh;
    videoCh4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(videoCh4, 4, 1);

    //这里还可以自行添加需要的控件,比如在顶部时间的左侧放置自定义的部件
    //其实可以采取绘制的办法绘制文字等,但是不方便添加自定义部件

    //悬浮标签,用于绘制按下的线条
    labFlow = new QLabel(this);
    labFlow->installEventFilter(this);
}

void VideoPlayback::setMargin(int margin)
{
    if (this->margin != margin) {
        this->margin = margin;
        layout->setMargin(margin);
    }
}

void VideoPlayback::setSpacing(int spacing)
{
    if (this->spacing != spacing) {
        this->spacing = spacing;
        layout->setSpacing(spacing);
    }
}

void VideoPlayback::setLabWidth(int labWidth)
{
    if (this->labWidth != labWidth) {
        this->labWidth = labWidth;
        labTime->setFixedWidth(labWidth);
        labCh1->setFixedWidth(labWidth);
        labCh2->setFixedWidth(labWidth);
        labCh3->setFixedWidth(labWidth);
        labCh4->setFixedWidth(labWidth);
    }
}

void VideoPlayback::setTextCh1(const QString &textCh1)
{
    if (this->textCh1 != textCh1) {
        this->textCh1 = textCh1;
        labCh1->setText(textCh1);
    }
}

void VideoPlayback::setTextCh2(const QString &textCh2)
{
    if (this->textCh2 != textCh2) {
        this->textCh2 = textCh2;
        labCh2->setText(textCh2);
    }
}

void VideoPlayback::setTextCh3(const QString &textCh3)
{
    if (this->textCh3 != textCh3) {
        this->textCh3 = textCh3;
        labCh3->setText(textCh3);
    }
}

void VideoPlayback::setTextCh4(const QString &textCh4)
{
    if (this->textCh4 != textCh4) {
        this->textCh4 = textCh4;
        labCh4->setText(textCh4);
    }
}

void VideoPlayback::setTextCh(const QString &textCh1, const QString &textCh2, const QString &textCh3, const QString &textCh4)
{
    setTextCh1(textCh1);
    setTextCh2(textCh2);
    setTextCh3(textCh3);
    setTextCh4(textCh4);
}

void VideoPlayback::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        labFlow->update();
    }
}

void VideoPlayback::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        labFlow->update();
    }
}

void VideoPlayback::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        QString qss = QString("color:%1").arg(textColor.name());
        labCh1->setStyleSheet(qss);
        labCh2->setStyleSheet(qss);
        labCh3->setStyleSheet(qss);
        labCh4->setStyleSheet(qss);
    }
}

void VideoPlayback::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void VideoPlayback::setVideoTextColor(const QColor &videoTextColor)
{
    if (this->videoTextColor != videoTextColor) {
        this->videoTextColor = videoTextColor;
        videoTime->setTextColor(videoTextColor);
    }
}

void VideoPlayback::setVideoBgColor(const QColor &videoBgColor)
{
    if (this->videoBgColor != videoBgColor) {
        this->videoBgColor = videoBgColor;
        videoTime->setBgColor(videoBgColor);
    }
}

void VideoPlayback::setVideoChColor(const QColor &videoChColor)
{
    if (this->videoChColor != videoChColor) {
        this->videoChColor = videoChColor;
        videoCh1->setChColor(videoChColor);
        videoCh2->setChColor(videoChColor);
        videoCh3->setChColor(videoChColor);
        videoCh4->setChColor(videoChColor);
    }
}

void VideoPlayback::setVideoDataColor(const QColor &videoDataColor)
{
    if (this->videoDataColor != videoDataColor) {
        this->videoDataColor = videoDataColor;
        videoCh1->setDataColor(videoDataColor);
        videoCh2->setDataColor(videoDataColor);
        videoCh3->setDataColor(videoDataColor);
        videoCh4->setDataColor(videoDataColor);
    }
}

void VideoPlayback::setDatas1(const QList<VideoCh::VideoData> &datas)
{
    videoCh1->setDatas(datas);
}

void VideoPlayback::setDatas2(const QList<VideoCh::VideoData> &datas)
{
    videoCh2->setDatas(datas);
}

void VideoPlayback::setDatas3(const QList<VideoCh::VideoData> &datas)
{
    videoCh3->setDatas(datas);
}

void VideoPlayback::setDatas4(const QList<VideoCh::VideoData> &datas)
{
    videoCh4->setDatas(datas);
}
