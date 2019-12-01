﻿#ifndef NAVLABEL_H
#define NAVLABEL_H

/**
 * 导航标签控件 作者:feiyangqingyun(QQ:517216493) 2016-11-28
 * 1:可设置前景色和背景色
 * 2:可设置箭头位置方向 左右上下
 * 3:可设置箭头大小
 * 4:可设置显示倒三角
 * 5:可设置倒三角长度/位置/颜色
 */

#include <QLabel>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT NavLabel : public QLabel
#else
class NavLabel : public QLabel
#endif

{
    Q_OBJECT
    Q_ENUMS(ArrowPosition)
    Q_ENUMS(TrianglePosition)
    Q_PROPERTY(int borderRadius READ getBorderRadius WRITE setBorderRadius)
    Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
    Q_PROPERTY(QColor foreground READ getForeground WRITE setForeground)

    Q_PROPERTY(bool showArrow READ getShowArrow WRITE setShowArrow)
    Q_PROPERTY(int arrowSize READ getArrowSize WRITE setArrowSize)
    Q_PROPERTY(ArrowPosition arrowPosition READ getArrowPosition WRITE setArrowPosition)

    Q_PROPERTY(bool showTriangle READ getShowTriangle WRITE setShowTriangle)
    Q_PROPERTY(int triangleLen READ getTriangleLen WRITE setTriangleLen)
    Q_PROPERTY(TrianglePosition trianglePosition READ getTrianglePosition WRITE setTrianglePosition)
    Q_PROPERTY(QColor triangleColor READ getTriangleColor WRITE setTriangleColor)

public:
    enum ArrowPosition {
        ArrowPosition_Left = 0,     //向左箭头
        ArrowPosition_Right = 1,    //向右箭头
        ArrowPosition_Top = 2,      //向上箭头
        ArrowPosition_Bottom = 3    //向下箭头
    };

    enum TrianglePosition {
        TrianglePosition_Left = 0,  //左侧
        TrianglePosition_Right = 1, //右侧
        TrianglePosition_Top = 2,   //顶部
        TrianglePosition_Bottom = 3 //底部
    };

    explicit NavLabel(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawText(QPainter *painter);
    void drawTriangle(QPainter *painter);

private:
    int borderRadius;                   //边框圆角角度
    QColor background;                  //背景色
    QColor foreground;                  //前景色

    bool showArrow;                     //显示箭头
    int arrowSize;                      //箭头大小
    ArrowPosition arrowPosition;        //箭头位置

    bool showTriangle;                  //显示倒三角
    int triangleLen;                    //倒三角边长
    TrianglePosition trianglePosition;  //倒三角位置
    QColor triangleColor;               //倒三角颜色

    QRect bgRect;                       //绘制区域

public:
    int getBorderRadius()               const;
    QColor getBackground()              const;
    QColor getForeground()              const;

    bool getShowArrow()                 const;
    int getArrowSize()                  const;
    ArrowPosition getArrowPosition()    const;

    bool getShowTriangle()              const;
    int getTriangleLen()                const;
    TrianglePosition getTrianglePosition()const;
    QColor getTriangleColor()           const;

    QSize sizeHint()                    const;
    QSize minimumSizeHint()             const;

public Q_SLOTS:
    //设置边框圆角角度
    void setBorderRadius(int borderRadius);
    //设置前景色
    void setBackground(const QColor &background);
    //设置前景色
    void setForeground(const QColor &foreground);

    //设置显示箭头
    void setShowArrow(bool showArrow);
    //设置箭头大小
    void setArrowSize(int arrowSize);
    //设置箭头位置
    void setArrowPosition(const ArrowPosition &arrowPosition);

    //设置显示倒三角
    void setShowTriangle(bool showTriangle);
    //设置倒三角边长
    void setTriangleLen(int triangleLen);
    //设置倒三角位置
    void setTrianglePosition(const TrianglePosition &trianglePosition);
    //设置倒三角颜色
    void setTriangleColor(const QColor &triangleColor);

Q_SIGNALS:
    void clicked();
};

#endif // NAVLABEL_H
