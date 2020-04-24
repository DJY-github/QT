/***************************************************************************
 **
 **  Copyright (C) 2018 MaMinJie <canpool@163.com>
 **  Contact: https://github.com/canpool
 **
 **  This program is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with this program.  If not, see http://www.gnu.org/licenses/.
 **
****************************************************************************/
#ifndef FANCYNAVBUTTON_H
#define FANCYNAVBUTTON_H

#include <QToolButton>
#include <QIcon>
#include <QColor>

class FancyNavButton : public QToolButton
{
    Q_OBJECT
public:
    explicit FancyNavButton(QWidget *parent = nullptr);

    enum ButtonType { Button, Action};

    void select(bool selected);

    void setType(ButtonType type) { m_type = type;}
    ButtonType type() const { return m_type;}

    void setHoverColor(const QColor &color) { m_hoverColor = color;}
    QColor hoverColor() const { return m_hoverColor;}

    void setPressColor(const QColor &color) { m_pressColor = color;}
    QColor pressColor() const { return m_pressColor;}

    void setTextColor(const QColor &color);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);
    void painterInfo(QColor &color);

private:
    bool m_isMouseOver;
    bool m_isMousePress;
    ButtonType m_type;

    QColor m_hoverColor;
    QColor m_pressColor;
};

#endif // FANCYNAVBUTTON_H
