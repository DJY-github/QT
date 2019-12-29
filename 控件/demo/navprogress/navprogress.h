﻿#ifndef NAVPROGRESS_H
#define NAVPROGRESS_H

/**
 * 导航进度条控件 作者:feiyangqingyun(QQ:517216493) 2016-11-29
 * 1:可设置前景色/背景色/当前值前景色/当前值背景色
 * 2:可设置最大步数及当前第几步
 * 3:可设置导航标签队列文字信息
 * 4:可设置三种风格样式 京东订单流程样式/淘宝订单流程样式/支付宝订单流程样式
 * 5:文字自适应大小
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT NavProgress : public QWidget
#else
class NavProgress : public QWidget
#endif

{
    Q_OBJECT
    Q_ENUMS(NavStyle)

    Q_PROPERTY(int maxStep READ getMaxStep WRITE setMaxStep)
    Q_PROPERTY(int currentStep READ getCurrentStep WRITE setCurrentStep)
    Q_PROPERTY(NavStyle navStyle READ getNavStyle WRITE setNavStyle)

    Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
    Q_PROPERTY(QColor foreground READ getForeground WRITE setForeground)
    Q_PROPERTY(QColor currentBackground READ getCurrentBackground WRITE setCurrentBackground)
    Q_PROPERTY(QColor currentForeground READ getCurrentForeground WRITE setCurrentForeground)

public:
    enum NavStyle {
        NavStyle_JD = 0,    //京东订单流程样式
        NavStyle_TB = 1,    //淘宝订单流程样式
        NavStyle_ZFB = 2    //支付宝订单流程样式
    };

    explicit NavProgress(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void drawBg_JD(QPainter *painter);
    void drawText_JD(QPainter *painter);
    void drawCurrentBg_JD(QPainter *painter);
    void drawCurrentText_JD(QPainter *painter);
    void drawBg_TB(QPainter *painter);
    void drawText_TB(QPainter *painter);
    void drawCurrentBg_TB(QPainter *painter);
    void drawBg_ZFB(QPainter *painter);
    void drawText_ZFB(QPainter *painter);
    void drawCurrentBg_ZFB(QPainter *painter);

private:
    QStringList topInfo;            //导航顶部标签数据
    QStringList bottomInfo;         //导航底部标签数据

    int maxStep;                    //最大步数
    int currentStep;                //当前第几步
    NavStyle navStyle;              //导航样式

    QColor background;              //背景色
    QColor foreground;              //前景色
    QColor currentBackground;       //当前背景色
    QColor currentForeground;       //当前前景色

    QFont iconFont;                 //图形字体

public:
    QStringList getTopInfo()        const;
    QStringList getBottomInfo()     const;

    int getMaxStep()                const;
    int getCurrentStep()            const;
    NavStyle getNavStyle()          const;

    QColor getBackground()          const;
    QColor getForeground()          const;
    QColor getCurrentBackground()   const;
    QColor getCurrentForeground()   const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置导航顶部标签数据
    void setTopInfo(const QStringList &topInfo);
    //设置导航底部标签数据
    void setBottomInfo(const QStringList &bottomInfo);

    //设置最大步数
    void setMaxStep(int maxStep);
    //设置当前第几步
    void setCurrentStep(int currentStep);
    //设置导航样式
    void setNavStyle(const NavStyle &navStyle);

    //设置前景色
    void setBackground(const QColor &background);
    //设置前景色
    void setForeground(const QColor &foreground);
    //设置当前前景色
    void setCurrentBackground(const QColor &currentBackground);
    //设置当前前景色
    void setCurrentForeground(const QColor &currentForeground);
};

#endif // NAVPROGRESS_H
