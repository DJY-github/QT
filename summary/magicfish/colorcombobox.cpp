#pragma execution_character_set("utf-8")

#include "colorcombobox.h"
#include "qdebug.h"
#
ColorComboBox::ColorComboBox(QWidget *parent) : QComboBox(parent)
{
    showColorName = true;
    this->initItems();
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
}

void ColorComboBox::currentIndexChanged(int index)
{
    if (index >= 0) {
        this->colorName = QColor::colorNames().at(index);
        emit colorChanged(colorName);
        emit colorChanged(QColor(colorName));
    }
}

bool ColorComboBox::getShowColorName() const
{
    return this->showColorName;
}

QString ColorComboBox::getColorName() const
{
    return this->colorName;
}

void ColorComboBox::setShowColorName(bool showColorName)
{
    if (this->showColorName != showColorName) {
        this->showColorName = showColorName;
    }
}

void ColorComboBox::setColorName(const QString &colorName)
{
    if (this->count() == 0) {
        return;
    }

    if (this->colorName != colorName) {
        this->colorName = colorName;
        int index = QColor::colorNames().indexOf(colorName);
        this->setCurrentIndex(index);
    }
}

void ColorComboBox::initItems()
{
    this->clear();
    QStringList colorList = QColor::colorNames();
    foreach (QString strColor, colorList) {
        QPixmap pix(this->iconSize());
        pix.fill(strColor);
        this->addItem(QIcon(pix), showColorName ? strColor : "");
    }
}
