#pragma execution_character_set("utf-8")

#include "colorpanelbtn.h"
#include "qlayout.h"
#include "qpushbutton.h"
#include "qdebug.h"

ColorPanelBtn::ColorPanelBtn(QWidget *parent) : QWidget(parent)
{
    colors << "#FEFEFE" << "#EEEEEF" << "#DCDDDD" << "#C9CACA" << "#B6B6B7" << "#A1A1A1" << "#8B8B8C" << "#757475" << "#5F5D5D" << "#474443" << "#303030";
    colors << "#00A2E9" << "#009B4C" << "#FFF000" << "#E62129" << "#E40082" << "#B04B87" << "#F08519" << "#F4B3B3" << "#897870" << "#D2CDE6" << "#A79CCB";
    colors << "#758FC8" << "#7C6FB0" << "#9288B1" << "#566892" << "#5E5872" << "#7789A4" << "#008FD7" << "#A0D9F6" << "#B8CEDA" << "#98AAB4" << "#75838A";
    colors << "#50585D" << "#5B7877" << "#4B8D7F" << "#769C9B" << "#5BA997" << "#5FA776" << "#62C3D0" << "#56AAB7" << "#B9CCBC" << "#D5EAD8" << "#A6D4AE";
    colors << "#99A99C" << "#9AA780" << "#BCC774" << "#BBC99A" << "#ACCE22" << "#D9E483" << "#5F5C50" << "#8B8979" << "#B6B49E" << "#B6B281" << "#DED572";
    colors << "#FFF582" << "#FFF9B1" << "#FFFCDB" << "#B39B77" << "#D59961" << "#DAB96B" << "#EF8641" << "#F6AE45" << "#F5B06E" << "#FDD100" << "#FBD7A3";
    colors << "#89765B" << "#AC6249" << "#D0753B" << "#EF8762" << "#F5B193" << "#FADAC9" << "#AF8283" << "#CF7771" << "#FF696B" << "#CF788A" << "#E61D4C";
    colors << "#EF8781" << "#E95A6F" << "#D49D9E" << "#876474" << "#AC6484" << "#F4B5D0" << "#D49EB6" << "#B39FA8" << "#D8C0CB" << "#B3719D" << "#CA5599";
    colors << "#CD81B3" << "#B593B3" << "#D0A9CD" << "#745E73" << "#977B95" << "#A878B1" << "#A72185" << "#934787" << "#804E9A" << "#7B5882" << "#714588";

    space = 2;
    columnCount = 11;
    borderRadius = 0;
    borderWidth = 2;
    borderColor = QColor("#C0392B");

    gridLayout = new QGridLayout;
    gridLayout->setSpacing(space);
    gridLayout->setMargin(0);
    this->setLayout(gridLayout);
    this->initStyle();
    this->initBtn();    
}

void ColorPanelBtn::initStyle()
{
    QString qss = QString("QPushButton{border:none;border-radius:%1px;}"
                          "QPushButton:hover{border:%2px solid %3;}")
                  .arg(borderRadius).arg(borderWidth).arg(borderColor.name());
    this->setStyleSheet(qss);
}

void ColorPanelBtn::initBtn()
{
    qDeleteAll(btns);
    btns.clear();

    int count = colors.count();
    int row = 0;
    int column = 0;
    int index = 0;
    for (int i = 0; i < count; i++) {
        QPushButton *btn = new QPushButton;
        connect(btn, SIGNAL(pressed()), this, SLOT(btnClicked()));
        btn->setObjectName("btn" + colors.at(i));
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btn->setStyleSheet(QString("QPushButton{background:%1;}").arg(colors.at(i)));

        gridLayout->addWidget(btn, row, column);
        column++;
        index++;

        if (index % columnCount == 0) {
            row++;
            column = 0;
        }

        btns.append(btn);
    }
}

void ColorPanelBtn::btnClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    QString objName = btn->objectName();
    emit colorChanged(QColor(objName.right(7)));
}

QStringList ColorPanelBtn::getColors() const
{
    return this->colors;
}

int ColorPanelBtn::getSpace() const
{
    return this->space;
}

int ColorPanelBtn::getColumnCount() const
{
    return this->columnCount;
}

int ColorPanelBtn::getBorderRadius() const
{
    return this->borderRadius;
}

int ColorPanelBtn::getBorderWidth() const
{
    return this->borderWidth;
}

QColor ColorPanelBtn::getBorderColor() const
{
    return this->borderColor;
}

QSize ColorPanelBtn::sizeHint() const
{
    return QSize(400, 300);
}

QSize ColorPanelBtn::minimumSizeHint() const
{
    return QSize(40, 30);
}

void ColorPanelBtn::setColors(const QStringList &colors)
{
    if (this->colors != colors) {
        this->colors = colors;
        this->initBtn();
    }
}

void ColorPanelBtn::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        this->gridLayout->setSpacing(space);
    }
}

void ColorPanelBtn::setColumnCount(int columnCount)
{
    if (this->columnCount != columnCount) {
        this->columnCount = columnCount;
        this->initBtn();
    }
}

void ColorPanelBtn::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        this->initStyle();
    }
}

void ColorPanelBtn::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        this->initStyle();
    }
}

void ColorPanelBtn::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        this->initStyle();
    }
}
