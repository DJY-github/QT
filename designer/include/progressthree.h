﻿#ifndef PROGRESSTHREE_H
#define PROGRESSTHREE_H

/**
 * 多态进度条控件 作者:feiyangqingyun(QQ:517216493) 2019-4-30
 * 1:可设置三种状态不同的值
 * 2:可设置三种状态不同的颜色
 * 3:可设置圆角角度
 * 4:可设置启用自动圆角
 * 5:可设置边框宽度+颜色
 * 6:可设置是否显示值或者百分比
 * 7:可设置字体自适应大小
 * 8:可设置背景颜色+文字颜色
 * 9:精准计算圆角角度,解决了QSS中border-radius当进度小于圆角角度出现方形的BUG
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT ProgressThree : public QWidget
#else
class ProgressThree : public QWidget
#endif

{
    Q_OBJECT
    Q_PROPERTY(int value1 READ getValue1 WRITE setValue1)
    Q_PROPERTY(int value2 READ getValue2 WRITE setValue2)
    Q_PROPERTY(int value3 READ getValue3 WRITE setValue3)

    Q_PROPERTY(QColor color1 READ getColor1 WRITE setColor1)
    Q_PROPERTY(QColor color2 READ getColor2 WRITE setColor2)
    Q_PROPERTY(QColor color3 READ getColor3 WRITE setColor3)

    Q_PROPERTY(int radius READ getRadius WRITE setRadius)
    Q_PROPERTY(bool autoRadius READ getAutoRadius WRITE setAutoRadius)

    Q_PROPERTY(bool showValue READ getShowValue WRITE setShowValue)
    Q_PROPERTY(bool showPercent READ getShowPercent WRITE setShowPercent)
    Q_PROPERTY(bool autoFont READ getAutoFont WRITE setAutoFont)

    Q_PROPERTY(double borderWidth READ getBorderWidth WRITE setBorderWidth)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)

    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

public:
    explicit ProgressThree(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawValue(QPainter *painter);
    void drawValue1(QPainter *painter);
    void drawValue2(QPainter *painter);
    void drawValue3(QPainter *painter);
    void drawBorder(QPainter *painter);

private:
    int value1;                 //值1
    int value2;                 //值2
    int value3;                 //值3

    QColor color1;              //颜色1
    QColor color2;              //颜色2
    QColor color3;              //颜色3

    int radius;                 //圆角角度
    bool autoRadius;            //自动圆角

    bool showValue;             //显示对应的值
    bool showPercent;           //显示对应的百分比
    bool autoFont;              //自动字体大小

    double borderWidth;         //边框宽度
    QColor borderColor;         //边框颜色

    QColor bgColor;             //背景颜色
    QColor textColor;           //文字颜色

    int width1;                 //值1宽度
    int width2;                 //值2宽度
    int width3;                 //值3宽度   

public:
    int getValue1()             const;
    int getValue2()             const;
    int getValue3()             const;

    QColor getColor1()          const;
    QColor getColor2()          const;
    QColor getColor3()          const;

    int getRadius()             const;
    bool getAutoRadius()        const;

    bool getShowValue()         const;
    bool getShowPercent()       const;
    bool getAutoFont()          const;

    double getBorderWidth()     const;
    QColor getBorderColor()     const;

    QColor getBgColor()         const;
    QColor getTextColor()       const;

    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

public Q_SLOTS:
    //设置三个值
    void setValue1(int value1);
    void setValue2(int value2);
    void setValue3(int value3);

    //设置三个颜色
    void setColor1(const QColor &color1);
    void setColor2(const QColor &color2);
    void setColor3(const QColor &color3);

    //设置圆角+自动圆角
    void setRadius(int radius);
    void setAutoRadius(bool autoRadius);

    //设置显示值+显示百分比+自动字体大小
    void setShowValue(bool showValue);
    void setShowPercent(bool showPercent);
    void setAutoFont(bool autoFont);

    //设置边框宽度+颜色
    void setBorderWidth(double borderWidth);
    void setBorderColor(const QColor &borderColor);

    //设置背景颜色+文字颜色
    void setBgColor(const QColor &bgColor);
    void setTextColor(const QColor &textColor);
};

#endif // PROGRESSTHREE_H
