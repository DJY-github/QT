﻿#ifndef XLISTWIDGET_H
#define XLISTWIDGET_H

/**
 * 会议室面板控件 作者:feiyangqingyun(QQ:517216493) 2019-3-3
 * 1:可设置会议室个数
 * 2:可设置文字颜色+背景颜色
 * 3:可设置鼠标选中文字颜色+鼠标选中背景颜色
 * 4:可设置鼠标悬停文字颜色+鼠标悬停背景颜色
 * 5:可设置右键菜单单个菜单禁用启用
 * 6:可设置节点的最小宽度高度
 * 7:可设置节点字符串集合
 * 8:可设置节点个数,自动生成节点
 * 9:可设置滚动条位置左侧右侧+宽度+颜色
 */

#include <QListWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT XListWidget : public QListWidget
#else
class XListWidget : public QListWidget
#endif

{
    Q_OBJECT
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QColor selectTextColor READ getSelectTextColor WRITE setSelectTextColor)
    Q_PROPERTY(QColor selectBgColor READ getSelectBgColor WRITE setSelectBgColor)
    Q_PROPERTY(QColor hoverTextColor READ getHoverTextColor WRITE setHoverTextColor)
    Q_PROPERTY(QColor hoverBgColor READ getHoverBgColor WRITE setHoverBgColor)

    Q_PROPERTY(QString itemTexts READ getItemTexts WRITE setItemTexts)
    Q_PROPERTY(QPixmap normalPixmap READ getNormalPixmap WRITE setNormalPixmap)
    Q_PROPERTY(QPixmap selectPixmap READ getSelectPixmap WRITE setSelectPixmap)
    Q_PROPERTY(QPixmap hoverPixmap READ getHoverPixmap WRITE setHoverPixmap)

    Q_PROPERTY(int itemCount READ getItemCount WRITE setItemCount)
    Q_PROPERTY(int itemWidth READ getItemWidth WRITE setItemWidth)
    Q_PROPERTY(int itemHeight READ getItemHeight WRITE setItemHeight)    

    Q_PROPERTY(int scrollWidth READ getScrollWidth WRITE setScrollWidth)
    Q_PROPERTY(bool scrollLeft READ getScrollLeft WRITE setScrollLeft)
    Q_PROPERTY(QColor scrollColor READ getScrollColor WRITE setScrollColor)

    Q_PROPERTY(bool enableEdit READ getEnableEdit WRITE setEnableEdit)
    Q_PROPERTY(bool enableAdd READ getEnableAdd WRITE setEnableAdd)
    Q_PROPERTY(bool enableDelete READ getEnableDelete WRITE setEnableDelete)

public:
    explicit XListWidget(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);
    void leaveEvent(QEvent *);

private:
    QColor textColor;           //文字颜色
    QColor bgColor;             //背景颜色
    QColor selectTextColor;     //选中文字颜色
    QColor selectBgColor;       //选中背景颜色
    QColor hoverTextColor;      //悬停文字颜色
    QColor hoverBgColor;        //悬停背景颜色

    QString itemTexts;          //节点文本集合
    QPixmap normalPixmap;       //正常图标
    QPixmap selectPixmap;       //选中图标
    QPixmap hoverPixmap;        //悬停图标

    int itemCount;              //节点个数
    int itemWidth;              //节点宽度
    int itemHeight;             //节点高度

    int scrollWidth;            //滚动条宽度
    bool scrollLeft;            //滚动条在左侧
    QColor scrollColor;         //滚动条颜色

    bool enableEdit;            //编辑菜单是否启用
    bool enableAdd;             //添加菜单是否启用
    bool enableDelete;          //删除菜单是否启用

    QAction *actionEdit;        //编辑菜单
    QAction *actionAdd;         //添加菜单
    QAction *actionDelete;      //删除菜单
    QListWidgetItem *hoverItem; //悬停节点
    QScrollBar *scrollBar;      //悬浮滚动条

private slots:
    void initForm();
    void initAction();
    void initStyle();
    void initScroll();
    void initPixmap();
    void initItem();
    void itemClicked(QListWidgetItem *item);
    void itemEntered(QListWidgetItem *item);
    void menuClicked();

public:
    QColor getTextColor()       const;
    QColor getBgColor()         const;
    QColor getSelectTextColor() const;
    QColor getSelectBgColor()   const;
    QColor getHoverTextColor()  const;
    QColor getHoverBgColor()    const;

    QString getItemTexts()      const;
    QPixmap getNormalPixmap()   const;
    QPixmap getSelectPixmap()   const;
    QPixmap getHoverPixmap()    const;

    int getItemCount()          const;
    int getItemWidth()          const;
    int getItemHeight()         const;

    int getScrollWidth()        const;
    bool getScrollLeft()        const;
    QColor getScrollColor()     const;

    bool getEnableEdit()        const;
    bool getEnableAdd()         const;
    bool getEnableDelete()      const;

    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

public Q_SLOTS:
    //设置文字颜色
    void setTextColor(const QColor &textColor);
    //设置背景颜色
    void setBgColor(const QColor &bgColor);
    //设置选中文字颜色
    void setSelectTextColor(const QColor &selectTextColor);
    //设置选中背景颜色
    void setSelectBgColor(const QColor &selectBgColor);
    //设置悬停文字颜色
    void setHoverTextColor(const QColor &hoverTextColor);
    //设置悬停背景颜色
    void setHoverBgColor(const QColor &hoverBgColor);

    //设置节点集合
    void setItemTexts(const QString &itemTexts);
    //设置正常图标
    void setNormalPixmap(const QPixmap &normalPixmap);
    //设置选中图标
    void setSelectPixmap(const QPixmap &selectPixmap);
    //设置悬停图标
    void setHoverPixmap(const QPixmap &hoverPixmap);

    //设置节点个数
    void setItemCount(int itemCount);
    //设置节点宽度
    void setItemWidth(int itemWidth);
    //设置节点高度
    void setItemHeight(int itemHeight);

    //设置滚动条宽度
    void setScrollWidth(int scrollWidth);
    //设置滚动条位置
    void setScrollLeft(bool scrollLeft);
    //设置滚动条颜色
    void setScrollColor(const QColor &scrollColor);

    //设置编辑菜单启用禁用
    void setEnableEdit(bool enableEdit);
    //设置添加菜单启用禁用
    void setEnableAdd(bool enableAdd);
    //设置删除菜单启用禁用
    void setEnableDelete(bool enableDelete);

Q_SIGNALS:
    void itemClicked(int index, const QString &text);
    void menuClicked(const QString &text);
};

#endif // XLISTWIDGET_H
