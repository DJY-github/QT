#pragma execution_character_set("utf-8")

#include "colorpanelfader.h"
#include "colorpanelbar.h"
#include "qpainter.h"
#include "qevent.h"
#include "qlayout.h"
#include "qdebug.h"

ColorPanelFader::ColorPanelFader(QWidget *parent) : QWidget(parent)
{
    barSpace = 6;
    groupSpace = 20;
    bgColor = QColor(70, 70, 70);

    spacer1 = new QSpacerItem(groupSpace, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
    spacer2 = new QSpacerItem(groupSpace, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);

    layout = new QHBoxLayout;
    this->setLayout(layout);

    QList<QColor> topColors;
    QList<QColor> bottomColors;
    topColors << Qt::red << Qt::red << Qt::red << Qt::cyan << Qt::magenta << Qt::yellow << Qt::red << Qt::green << Qt::blue;
    bottomColors << Qt::red << Qt::white << Qt::black << Qt::cyan << Qt::magenta << Qt::yellow << Qt::black << Qt::black << Qt::black;

    for (int i = 0; i < 9; i++) {
        ColorPanelBar *item = new ColorPanelBar;
        connect(item, SIGNAL(colorChanged(QColor, double, double)),
                this, SLOT(colorChanged(QColor, double, double)));

        item->installEventFilter(this);
        item->setObjectName("colorPanelBar" + QString::number(i));
        item->setBorderColor(topColors.at(i));
        item->setTopColor(topColors.at(i));
        item->setBottomColor(bottomColors.at(i));
        item->setOutMode(true);

        if (i > 2) {
            item->setShowOverlay(true);
        }

        if (i == 3) {
            layout->addItem(spacer1);
        } else if (i == 6) {
            layout->addItem(spacer2);
        }

        layout->addWidget(item);
        items << item;
    }

    //初始化默认颜色值
    items.at(0)->setHSBMode(true);
    items.at(0)->setShowValue(true);
    items.at(1)->setStaticMode(false);
    items.at(2)->setStaticMode(false);
    items.at(3)->setPercent(0);
    items.at(7)->setPercent(0);
    items.at(8)->setPercent(0);
}

bool ColorPanelFader::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        ColorPanelBar *item = (ColorPanelBar *)watched;
        int index = items.indexOf(item);
        if (index >= 6) {
            items.at(0)->setEnabled(false);
            items.at(1)->setEnabled(false);
            items.at(2)->setEnabled(false);
            items.at(3)->setEnabled(false);
            items.at(4)->setEnabled(false);
            items.at(5)->setEnabled(false);
        } else if (index >= 3) {
            items.at(0)->setEnabled(false);
            items.at(1)->setEnabled(false);
            items.at(2)->setEnabled(false);
            items.at(6)->setEnabled(false);
            items.at(7)->setEnabled(false);
            items.at(8)->setEnabled(false);
        } else if (index >= 0) {
            items.at(3)->setEnabled(false);
            items.at(4)->setEnabled(false);
            items.at(5)->setEnabled(false);
            items.at(6)->setEnabled(false);
            items.at(7)->setEnabled(false);
            items.at(8)->setEnabled(false);
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        ColorPanelBar *item = (ColorPanelBar *)watched;
        int index = items.indexOf(item);
        if (index >= 6) {
            items.at(0)->setEnabled(true);
            items.at(1)->setEnabled(true);
            items.at(2)->setEnabled(true);
            items.at(3)->setEnabled(true);
            items.at(4)->setEnabled(true);
            items.at(5)->setEnabled(true);
        } else if (index >= 3) {
            items.at(0)->setEnabled(true);
            items.at(1)->setEnabled(true);
            items.at(2)->setEnabled(true);
            items.at(6)->setEnabled(true);
            items.at(7)->setEnabled(true);
            items.at(8)->setEnabled(true);
        } else if (index >= 0) {
            items.at(3)->setEnabled(true);
            items.at(4)->setEnabled(true);
            items.at(5)->setEnabled(true);
            items.at(6)->setEnabled(true);
            items.at(7)->setEnabled(true);
            items.at(8)->setEnabled(true);
        }
    }

    return QWidget::eventFilter(watched, event);
}

void ColorPanelFader::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), bgColor);
}

void ColorPanelFader::colorChanged(const QColor &color, double value, double percent)
{
    ColorPanelBar *item = (ColorPanelBar *)sender();
    int index = items.indexOf(item);

    if (index == 0) {
        //获取当前HSB处的颜色值
        items.at(1)->setTopColor(color);
        items.at(2)->setTopColor(color);
        items.at(1)->setBorderColor(color);
        items.at(2)->setBorderColor(color);
    } else if (index == 1) {
        items.at(2)->setTopColor(color);
        items.at(2)->setBorderColor(color);
    } else if (index == 2) {
        items.at(1)->setTopColor(color);
        items.at(1)->setBorderColor(color);
    } else if (index == 3) {
        items.at(6)->setPercent(100 - percent);
    } else if (index == 4) {
        items.at(7)->setPercent(100 - percent);
    } else if (index == 5) {
        items.at(8)->setPercent(100 - percent);
    } else if (index == 6) {
        items.at(3)->setPercent(100 - percent);
    } else if (index == 7) {
        items.at(4)->setPercent(100 - percent);
    } else if (index == 8) {
        items.at(5)->setPercent(100 - percent);
    }

    //如果是HSB变化则CMY和RGB变化
    if (index < 3) {
        double hue = items.at(0)->getPercent() / 100;
        double sat = items.at(1)->getPercent() / 100;
        double bright = items.at(2)->getPercent() / 100;

        //组合HSB当前值,然后转为CMY和RGB计算百分比进行设置
        QColor color = QColor::fromHsvF(hue, sat, bright);
        double percentRed = color.redF() * 100;
        double percentGreen = color.greenF() * 100;
        double percentBlue = color.blueF() * 100;

        items.at(3)->setPercent(100 - percentRed);
        items.at(4)->setPercent(100 - percentGreen);
        items.at(5)->setPercent(100 - percentBlue);
        items.at(6)->setPercent(percentRed);
        items.at(7)->setPercent(percentGreen);
        items.at(8)->setPercent(percentBlue);
    }

    //根据百分比获取颜色值
    double red = items.at(6)->getPercent() / 100;
    double green = items.at(7)->getPercent() / 100;
    double blue = items.at(8)->getPercent() / 100;
    QColor currentColor = QColor::fromRgbF(red, green, blue);
    emit colorChanged(currentColor, items.at(0)->getValue(), items.at(1)->getPercent(), items.at(2)->getPercent());

    //如果是CMY或者RGB变化则HSB变化
    if (index >= 3) {
        //hue活出现负数=白色,要矫正
        double percentHue = currentColor.hueF() * 100;
        if (percentHue < 0) {
            percentHue = 0;
        }

        double percentSat = currentColor.saturationF() * 100;
        double percentBright = currentColor.lightnessF() * 100;

        //计算当前值所占百分比
        items.at(0)->setPercent(percentHue);
        items.at(1)->setPercent(percentSat);
        items.at(2)->setPercent(percentBright);

        items.at(1)->setTopColor(currentColor);
        items.at(2)->setTopColor(currentColor);
        items.at(1)->setBorderColor(currentColor);
        items.at(2)->setBorderColor(currentColor);
    }
}

int ColorPanelFader::getBarSpace() const
{
    return this->barSpace;
}

int ColorPanelFader::getGroupSpace() const
{
    return this->groupSpace;
}

QColor ColorPanelFader::getBgColor() const
{
    return this->bgColor;
}

QSize ColorPanelFader::sizeHint() const
{
    return QSize(500, 350);
}

QSize ColorPanelFader::minimumSizeHint() const
{
    return QSize(100, 60);
}

void ColorPanelFader::setBarSpace(int barSpace)
{
    if (this->barSpace != barSpace) {
        this->barSpace = barSpace;
        layout->setSpacing(barSpace);
    }
}

void ColorPanelFader::setGroupSpace(int groupSpace)
{
    if (this->groupSpace != groupSpace) {
        this->groupSpace = groupSpace;
        layout->setSpacing(barSpace);
        spacer1->changeSize(groupSpace, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
        spacer2->changeSize(groupSpace, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
    }
}

void ColorPanelFader::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}
