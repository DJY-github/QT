﻿#ifndef CUSTOMPIE_H
#define CUSTOMPIE_H

/**
 * 自定义饼图控件 整理:feiyangqingyun(QQ:517216493) 2019-5-21
 * 1:可设置文字颜色
 * 2:可设置边框颜色
 * 3:可设置颜色集合
 * 4:可设置某个区域是否弹出
 * 5:可设置是否显示百分比
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT CustomPie : public QWidget
#else
class CustomPie : public QWidget
#endif

{
    Q_OBJECT
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)

public:
    CustomPie(QWidget *parent = 0);
    ~CustomPie();

protected:
    void paintEvent(QPaintEvent *);
    void drawPie(QPainter *painter);

private:
    bool explodedAll;           //是否全部展开
    int explodedIndex;          //展开的索引

    bool showPercent;           //是否显示百分比
    double holeSize;            //空心占比

    QColor textColor;           //文字颜色
    QColor borderColor;         //边框颜色
    QList<QColor> colors;       //颜色集合

    QList<QString> labels;      //标签集合
    QList<double> values;       //值集合

private:
    //获取总值
    double getSumValue();
    //根据偏移值获取偏移点坐标
    QPoint getOffsetPoint(double angel, int offset = 6);

public:
    QColor getTextColor()       const;
    QColor getBorderColor()     const;

    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

public Q_SLOTS:
    //设置是否全部展开+展开的索引
    void setExplodedAll(bool explodedAll);
    void setExplodedIndex(int index);

    //设置是否启用默认颜色
    void setDefaultColor(bool defaultColor);

    //设置文字颜色+边框颜色
    void setTextColor(const QColor &textColor);
    void setBorderColor(const QColor &borderColor);

    //设置颜色集合
    void setColors(const QList<QColor> &colors);

    //初始化饼图
    void initPie();
    //添加饼图数据
    void appendPie(const QString &label, double value, const QString &tip = "");
    //设置数据
    void setDataPie();
    //重新设置百分比
    void loadPercent();
    //清除饼图
    void clearPie();
    //设置空心占比
    void setHoleSize(double holeSize);

};

#endif // CUSTOMPIE_H
