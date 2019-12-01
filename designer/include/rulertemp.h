﻿#ifndef RULERTEMP_H
#define RULERTEMP_H

/**
 * 柱状温度计控件 作者:feiyangqingyun(QQ:517216493) 2016-11-4
 * 1:可设置精确度(小数点后几位)和间距
 * 2:可设置背景色/柱状颜色/线条颜色
 * 3:可设置长线条步长及短线条步长
 * 4:可启用动画及动画步长
 * 5:可设置范围值
 * 6:支持负数刻度值
 * 7:支持任意窗体大小缩放
 * 8:可设置柱状条位置 左侧 居中 右侧
 * 9:可设置刻度尺位置 无 左侧 右侧 两侧
 * 10:可设置用户设定目标值
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT RulerTemp : public QWidget
#else
class RulerTemp : public QWidget
#endif

{
    Q_OBJECT
    Q_ENUMS(BarPosition)
    Q_ENUMS(TickPosition)

    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)

    Q_PROPERTY(int precision READ getPrecision WRITE setPrecision)
    Q_PROPERTY(int longStep READ getLongStep WRITE setLongStep)
    Q_PROPERTY(int shortStep READ getShortStep WRITE setShortStep)
    Q_PROPERTY(int space READ getSpace WRITE setSpace)

    Q_PROPERTY(bool animation READ getAnimation WRITE setAnimation)
    Q_PROPERTY(double animationStep READ getAnimationStep WRITE setAnimationStep)

    Q_PROPERTY(bool showUserValue READ getShowUserValue WRITE setShowUserValue)
    Q_PROPERTY(double userValue READ getUserValue WRITE setUserValue)
    Q_PROPERTY(QColor userValueColor READ getUserValueColor WRITE setUserValueColor)

    Q_PROPERTY(QColor bgColorStart READ getBgColorStart WRITE setBgColorStart)
    Q_PROPERTY(QColor bgColorEnd READ getBgColorEnd WRITE setBgColorEnd)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)
    Q_PROPERTY(QColor barBgColor READ getBarBgColor WRITE setBarBgColor)
    Q_PROPERTY(QColor barColor READ getBarColor WRITE setBarColor)

    Q_PROPERTY(BarPosition barPosition READ getBarPosition WRITE setBarPosition)
    Q_PROPERTY(TickPosition tickPosition READ getTickPosition WRITE setTickPosition)

public:
    enum BarPosition {
        BarPosition_Left = 0,       //左侧显示
        BarPosition_Right = 1,      //右侧显示
        BarPosition_Center = 2      //居中显示
    };

    enum TickPosition {
        TickPosition_Null = 0,      //不显示
        TickPosition_Left = 1,      //左侧显示
        TickPosition_Right = 2,     //右侧显示
        TickPosition_Both = 3       //两侧显示
    };

    explicit RulerTemp(QWidget *parent = 0);
    ~RulerTemp();

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawBarBg(QPainter *painter);
    void drawRuler(QPainter *painter, int type);
    void drawBar(QPainter *painter);
    void drawValue(QPainter *painter);

private:
    double minValue;                //最小值
    double maxValue;                //最大值
    double value;                   //目标值

    int precision;                  //精确度,小数点后几位
    int longStep;                   //长线条等分步长
    int shortStep;                  //短线条等分步长
    int space;                      //间距

    bool animation;                 //是否启用动画显示
    double animationStep;           //动画显示时步长

    bool showUserValue;             //显示用户设定值
    double userValue;               //用户设定值
    QColor userValueColor;          //用户设定值颜色

    QColor bgColorStart;            //背景渐变开始颜色
    QColor bgColorEnd;              //背景渐变结束颜色
    QColor lineColor;               //线条颜色
    QColor barBgColor;              //柱状背景色
    QColor barColor;                //柱状颜色

    BarPosition barPosition;        //柱状条位置
    TickPosition tickPosition;      //刻度尺位置

    int barWidth;                   //水银柱宽度
    int barHeight;                  //水银柱高度
    int radius;                     //水银柱底部圆半径
    int targetX;                    //目标X坐标
    QRectF barRect;                 //柱状区域
    QRectF circleRect;              //底部圆区域

    bool reverse;                   //是否倒退
    double currentValue;            //当前值
    QTimer *timer;                  //定时器绘制动画

private slots:
    void updateValue();

public:
    double getMinValue()            const;
    double getMaxValue()            const;
    double getValue()               const;

    int getPrecision()              const;
    int getLongStep()               const;
    int getShortStep()              const;
    int getSpace()                  const;

    bool getAnimation()             const;
    double getAnimationStep()       const;

    bool getShowUserValue()         const;
    double getUserValue()           const;
    QColor getUserValueColor()      const;

    QColor getBgColorStart()        const;
    QColor getBgColorEnd()          const;
    QColor getLineColor()           const;
    QColor getBarBgColor()          const;
    QColor getBarColor()            const;

    BarPosition getBarPosition()    const;
    TickPosition getTickPosition()  const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置最大最小值-范围值
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    //设置最大最小值
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    //设置目标值
    void setValue(double value);
    void setValue(int value);

    //设置精确度
    void setPrecision(int precision);

    //设置线条等分步长
    void setLongStep(int longStep);
    void setShortStep(int shortStep);

    //设置间距
    void setSpace(int space);

    //设置是否启用动画显示
    void setAnimation(bool animation);
    //设置动画显示的步长
    void setAnimationStep(double animationStep);

    //设置是否显示用户设定值
    void setShowUserValue(bool showUserValue);

    //设置用户值
    void setUserValue(double userValue);
    void setUserValue(int userValue);

    //设置用户设定值颜色
    void setUserValueColor(const QColor &userValueColor);

    //设置背景颜色
    void setBgColorStart(const QColor &bgColorStart);
    void setBgColorEnd(const QColor &bgColorEnd);

    //设置线条颜色
    void setLineColor(const QColor &lineColor);

    //设置柱状颜色
    void setBarBgColor(const QColor &barBgColor);
    void setBarColor(const QColor &barColor);

    //设置柱状条位置
    void setBarPosition(const BarPosition &barPosition);

    //设置刻度尺位置
    void setTickPosition(const TickPosition &tickPosition);

Q_SIGNALS:
    void valueChanged(double value);
};

#endif // RULERTEMP_H
