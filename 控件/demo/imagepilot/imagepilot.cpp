#pragma execution_character_set("utf-8")

#include "imagepilot.h"
#include "qpainter.h"
#include "qdebug.h"

ImagePilot::ImagePilot(QWidget *parent) : QWidget(parent)
{
    pilotStyle = PilotStyle_Blue;
    imgFile = ":/image/pilot_blue.png";
}

void ImagePilot::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform);
    QImage img(imgFile);
    img = img.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //按照比例自动居中绘制
    int pixX = rect().center().x() - img.width() / 2;
    int pixY = rect().center().y() - img.height() / 2;
    QPoint point(pixX, pixY);
    painter.drawImage(point, img);
}

ImagePilot::PilotStyle ImagePilot::getPilotStyle() const
{
    return this->pilotStyle;
}

QString ImagePilot::getImgFile() const
{
    return this->imgFile;
}

QSize ImagePilot::sizeHint() const
{
    return QSize(200, 180);
}

QSize ImagePilot::minimumSizeHint() const
{
    return QSize(40, 36);
}

void ImagePilot::setPilotStyle(const ImagePilot::PilotStyle &pilotStyle)
{
    if (this->pilotStyle != pilotStyle) {
        this->pilotStyle = pilotStyle;

        if (pilotStyle == PilotStyle_Blue) {
            imgFile = ":/image/pilot_blue.png";
        } else if (pilotStyle == PilotStyle_Gray) {
            imgFile = ":/image/pilot_gray.png";
        } else if (pilotStyle == PilotStyle_Green) {
            imgFile = ":/image/pilot_green.png";
        } else if (pilotStyle == PilotStyle_Red) {
            imgFile = ":/image/pilot_red.png";
        } else if (pilotStyle == PilotStyle_Yellow) {
            imgFile = ":/image/pilot_yellow.png";
        }

        update();
    }
}

void ImagePilot::setImage(const QString &imgFile)
{
    if (this->imgFile != imgFile) {
        this->imgFile = imgFile;
        update();
    }
}
