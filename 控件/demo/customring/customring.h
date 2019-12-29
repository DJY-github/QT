﻿#ifndef CUSTOMRING_H
#define CUSTOMRING_H

/**
 * 自定义环形图控件 整理:feiyangqingyun(QQ:517216493) 2019-7-28
 * 原作者:雨田哥(QQ:3246214072)
 * 1:可设置是否显示标题+标题文字+标题高度
 * 2:可设置是否显示图例+图例高度
 * 3:可设置背景颜色+文字颜色+高亮颜色+标识颜色
 * 4:可设置外圆颜色+中间圆颜色+内圆颜色
 * 5:可设置外圆数据集合+内圆数据集合
 * 6:鼠标悬停突出显示区域并高亮显示文字
 * 7:每个区域都可设置对应的颜色+文字描述+百分比
 * 8:支持直接字符串设置文字集合和百分比集合
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT CustomRing : public QWidget
        #else
class CustomRing : public QWidget
        #endif

{
    Q_OBJECT
    Q_PROPERTY(bool showTitle READ getShowTitle WRITE setShowTitle)
    Q_PROPERTY(int titleHeight READ getTitleHeight WRITE setTitleHeight)
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)

    Q_PROPERTY(bool showLegend READ getShowLegend WRITE setShowLegend)
    Q_PROPERTY(int legendHeight READ getLegendHeight WRITE setLegendHeight)

    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor highColor READ getHighColor WRITE setHighColor)
    Q_PROPERTY(QColor flagColor READ getFlagColor WRITE setFlagColor)

    Q_PROPERTY(QColor outCircleColor READ getOutCircleColor WRITE setOutCircleColor)
    Q_PROPERTY(QColor midCircleColor READ getMidCircleColor WRITE setMidCircleColor)
    Q_PROPERTY(QColor inCircleColor READ getInCircleColor WRITE setInCircleColor)

    Q_PROPERTY(QString outPieInfos READ getOutPieInfos WRITE setOutPieInfos)
    Q_PROPERTY(QString inPieInfos READ getInPieInfos WRITE setInPieInfos)

public:
    struct RingData {
        int offset;         //鼠标移上去往外边突出显示的偏移距离
        int percent;        //百分比
        QColor color;       //背景色
        QString text;       //文本
        QPainterPath path;  //区域路径

        RingData()
        {
            offset = 0;
            percent = 0;
            color = QColor(0, 192, 133);
            text = "";
        }
    };

    CustomRing(QWidget *parent = 0);
    ~CustomRing();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawOutCircle(QPainter *painter);
    void drawOutPie(QPainter *painter, qreal scale, QPoint center);
    void drawMidCircle(QPainter *painter);
    void drawInPie(QPainter *painter, qreal scale, QPoint center);
    void drawInCircle(QPainter *painter);
    void drawTitle(QPainter *painter);
    void drawLegendText(QPainter *painter, qreal scale);

private:
    bool showTitle;             //显示标题
    int titleHeight;            //标题高度
    QString title;              //标题

    bool showLegend;            //显示图例
    int legendHeight;           //图例高度

    QColor bgColor;             //背景颜色
    QColor textColor;           //文字颜色
    QColor highColor;           //高亮颜色
    QColor flagColor;           //标题左侧标识颜色

    QColor outCircleColor;      //外圆颜色
    QColor midCircleColor;      //中间圆颜色
    QColor inCircleColor;       //里边圆颜色

    QString outPieInfos;        //外边饼图数据
    QString inPieInfos;         //里边饼图数据
    QList<QColor> outPieColors; //饼图颜色集合,在设置字符串时候用
    QList<QColor> inPieColors;  //饼图颜色集合,在设置字符串时候用

    QList<RingData> outPieInfo; //外边饼图数据
    QList<RingData> inPieInfo;  //里边饼图数据

public:
    bool getShowTitle()         const;
    int getTitleHeight()        const;
    QString getTitle()          const;

    bool getShowLegend()        const;
    int getLegendHeight()       const;

    QColor getBgColor()         const;
    QColor getTextColor()       const;
    QColor getHighColor()       const;
    QColor getFlagColor()       const;

    QColor getOutCircleColor()  const;
    QColor getMidCircleColor()  const;
    QColor getInCircleColor()   const;

    QString getOutPieInfos()    const;
    QString getInPieInfos()     const;

    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

public Q_SLOTS:
    //显示标题+标题栏高度+标题文字
    void setShowTitle(bool showTitle);
    void setTitleHeight(int titleHeight);
    void setTitle(const QString &title);

    //显示图例+图例高度+图例颜色
    void setShowLegend(bool showLegend);
    void setLegendHeight(int legendHeight);

    //设置背景颜色+文字颜色+高亮颜色+标识颜色
    void setBgColor(const QColor &bgColor);
    void setTextColor(const QColor &textColor);
    void setHighColor(const QColor &highColor);
    void setFlagColor(const QColor &flagColor);

    //设置外圆颜色+中间圆颜色+里边圆颜色
    void setOutCircleColor(const QColor &outCircleColor);
    void setMidCircleColor(const QColor &midCircleColor);
    void setInCircleColor(const QColor &inCircleColor);

    //字符串形式设置数据
    void setOutPieInfos(const QString &outPieInfos);
    void setInPieInfos(const QString &inPieInfos);

    //设置颜色集合
    void setOutPieColors(const QList<QColor> &outPieColors);
    void setInPieColors(const QList<QColor> &inPieColors);

    //清空+设置饼图数据
    void clearOutPie();
    void clearInPie();
    void appendOutPie(const RingData &data);
    void appendInPie(const RingData &data);
};

#endif // CUSTOMRING_H
