#pragma execution_character_set("utf-8")

#include "imagepower.h"
#include "qpainter.h"
#include "qdebug.h"

ImagePower::ImagePower(QWidget *parent) : QWidget(parent)
{
    imageValue = 0;
    setValue(4);
}

void ImagePower::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform);
    QImage img = image.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //按照比例自动居中绘制
    int pixX = rect().center().x() - img.width() / 2;
    int pixY = rect().center().y() - img.height() / 2;
    QPoint point(pixX, pixY);
    painter.drawImage(point, img);
}

QImage ImagePower::getImage() const
{
    return this->image;
}

int ImagePower::getImageValue() const
{
    return this->imageValue;
}

int ImagePower::getValue() const
{
    return this->value;
}

QSize ImagePower::sizeHint() const
{
    return QSize(245, 140);
}

QSize ImagePower::minimumSizeHint() const
{
    return QSize(24, 14);
}

void ImagePower::setImage(const QImage &image)
{
    if (this->image != image) {
        this->image = image;
        update();
    }
}

void ImagePower::setImageValue(int imageValue)
{
    if (this->imageValue != imageValue) {
        this->imageValue = imageValue;
    }
}

void ImagePower::setValue(int value)
{
    if (value >= 0 && value <= 5 && this->value != value) {
        this->value = value;
        image = QImage(QString(":/image/power_%1.png").arg(value));
        update();
    }
}
