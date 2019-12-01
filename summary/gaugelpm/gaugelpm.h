﻿#ifndef GAUGELPM_H
#define GAUGELPM_H

/**
 * PLM仪表盘控件 作者:feiyangqingyun(QQ:517216493) 2018-8-17
 * 1:可设置范围值,支持负数值
 * 2:可设置背景颜色
 * 3:可设置进度颜色
 * 4:可设置文字颜色
 * 5:可设置标题文字
 * 6:可设置单位文字
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT GaugeLpm : public QWidget
#else
class GaugeLpm : public QWidget
#endif

{
    Q_OBJECT
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)

    Q_PROPERTY(QString title READ getTitle WRITE setTitle)
    Q_PROPERTY(QString unit READ getUnit WRITE setUnit)

    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QColor percentColor READ getPercentColor WRITE setPercentColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

public:
    explicit GaugeLpm(QWidget *parent = 0);
    ~GaugeLpm();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void drawCircle(QPainter *painter, int radius, const QColor &color1,const QColor &color2);
    void drawPercent(QPainter *painter);
    void drawLine(QPainter *painter);
    void drawPointer(QPainter *painter);
    void drawText(QPainter *painter);

private:
    double minValue;                //最小值
    double maxValue;                //最大值
    double value;                   //目标值

    QString title;                  //标题
    QString unit;                   //单位

    QColor bgColor;                 //背景颜色
    QColor percentColor;            //进度颜色
    QColor textColor;               //文字颜色

    bool mousePress;                //记录鼠标是否按下
    bool inCenter;                  //在圆中心内
    QPointF lastPoint;              //鼠标按下时坐标

private:
    double twoPtDistance(const QPointF &pt1, const QPointF &pt2);

public:
    double getMinValue()            const;
    double getMaxValue()            const;
    double getValue()               const;

    QString getTitle()              const;
    QString getUnit()               const;

    QColor getBgColor()             const;
    QColor getPercentColor()        const;
    QColor getTextColor()           const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置范围值
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    //设置最大最小值
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    //设置目标值
    void setValue(double value);
    void setValue(int value);

    //设置标题+单位
    void setTitle(const QString &title);
    void setUnit(const QString &unit);

    //设置背景颜色
    void setBgColor(const QColor &bgColor);
    //设置进度颜色
    void setPercentColor(const QColor &percentColor);
    //设置文字颜色
    void setTextColor(const QColor &textColor);

Q_SIGNALS:
    void valueChanged(int value);
    void clicked();
};

#endif // GAUGELPM_H
