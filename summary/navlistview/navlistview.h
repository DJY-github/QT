﻿#ifndef NAVLISTVIEW_H
#define NAVLISTVIEW_H

/**
 * 树状导航栏控件 作者:feiyangqingyun(QQ:517216493) 2018-8-15
 * 1:设置节点数据相当方便,按照对应格式填入即可,分隔符,
 * 2:可设置提示信息 是否显示+宽度
 * 3:可设置行分隔符 是否显示+高度+颜色
 * 4:可设置选中节点线条突出显示+颜色+左侧右侧位置
 * 5:可设置选中节点三角形突出显示+颜色+左侧右侧位置
 * 6:可设置父节点的 选中颜色+悬停颜色+默认颜色
 * 7:可设置子节点的 选中颜色+悬停颜色+默认颜色
 * 8:可设置父节点文字的 图标边距+左侧距离+字体大小+高度
 * 9:可设置子节点文字的 图标边距+左侧距离+字体大小+高度
 * 10:可设置节点展开模式 单击+双击+禁用
 */

#include <QStyledItemDelegate>
#include <QAbstractListModel>
#include <QListView>
#include <QStringList>

class NavListView;

class NavDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    NavDelegate(QObject *parent);
    ~NavDelegate();

protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const ;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    NavListView *nav;
    QFont iconFont;
};


class NavModel : public QAbstractListModel
{
    Q_OBJECT
public:
    NavModel(QObject *parent);
    ~NavModel();

public:
    struct TreeNode {
        int level;                  //层级,父节点-1,子节点-2
        bool expand;                //是否打开子节点
        bool last;                  //是否末尾元素
        QChar icon;                 //左侧图标
        QString text;               //显示的节点文字
        QString tip;                //右侧描述文字
        QString parentText;         //父节点名称
        QList<TreeNode *> children; //子节点集合
    };

    struct ListNode {
        QString text;               //节点文字
        TreeNode *treeNode;         //节点指针
    };

protected:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QList<TreeNode *> treeNode;
    QList<ListNode> listNode;

public Q_SLOTS:
    void setItems(const QStringList &items);
    void expand(const QModelIndex &index);

private:
    void refreshList();
};

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT NavListView : public QListView
#else
class NavListView : public QListView
#endif

{
    Q_OBJECT
    Q_ENUMS(ExpendMode)

    Q_PROPERTY(QString items READ getItems WRITE setItems)
    Q_PROPERTY(bool rightIconVisible READ getRightIconVisible WRITE setRightIconVisible)
    Q_PROPERTY(bool tipVisible READ getTipVisible WRITE setTipVisible)
    Q_PROPERTY(int tipWidth READ getTipWidth WRITE setTipWidth)

    Q_PROPERTY(bool separateVisible READ getSeparateVisible WRITE setSeparateVisible)
    Q_PROPERTY(int separateHeight READ getSeparateHeight WRITE setSeparateHeight)
    Q_PROPERTY(QColor separateColor READ getSeparateColor WRITE setSeparateColor)

    Q_PROPERTY(bool lineLeft READ getLineLeft WRITE setLineLeft)
    Q_PROPERTY(bool lineVisible READ getLineVisible WRITE setLineVisible)
    Q_PROPERTY(int lineWidth READ getLineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)

    Q_PROPERTY(bool triangleLeft READ getTriangleLeft WRITE setTriangleLeft)
    Q_PROPERTY(bool triangleVisible READ getTriangleVisible WRITE setTriangleVisible)
    Q_PROPERTY(int triangleWidth READ getTriangleWidth WRITE setTriangleWidth)
    Q_PROPERTY(QColor triangleColor READ getTriangleColor WRITE setTriangleColor)

    Q_PROPERTY(int parentIconMargin READ getParentIconMargin WRITE setParentIconMargin)
    Q_PROPERTY(int parentMargin READ getParentMargin WRITE setParentMargin)
    Q_PROPERTY(int parentFontSize READ getParentFontSize WRITE setParentFontSize)
    Q_PROPERTY(int parentHeight READ getParentHeight WRITE setParentHeight)
    Q_PROPERTY(QColor parentBgNormalColor READ getParentBgNormalColor WRITE setParentBgNormalColor)
    Q_PROPERTY(QColor parentBgSelectedColor READ getParentBgSelectedColor WRITE setParentBgSelectedColor)
    Q_PROPERTY(QColor parentBgHoverColor READ getParentBgHoverColor WRITE setParentBgHoverColor)
    Q_PROPERTY(QColor parentTextNormalColor READ getParentTextNormalColor WRITE setParentTextNormalColor)
    Q_PROPERTY(QColor parentTextSelectedColor READ getParentTextSelectedColor WRITE setParentTextSelectedColor)
    Q_PROPERTY(QColor parentTextHoverColor READ getParentTextHoverColor WRITE setParentTextHoverColor)

    Q_PROPERTY(int childIconMargin READ getChildIconMargin WRITE setChildIconMargin)
    Q_PROPERTY(int childMargin READ getChildMargin WRITE setChildMargin)
    Q_PROPERTY(int childFontSize READ getChildFontSize WRITE setChildFontSize)
    Q_PROPERTY(int childHeight READ getChildHeight WRITE setChildHeight)
    Q_PROPERTY(QColor childBgNormalColor READ getChildBgNormalColor WRITE setChildBgNormalColor)
    Q_PROPERTY(QColor childBgSelectedColor READ getChildBgSelectedColor WRITE setChildBgSelectedColor)
    Q_PROPERTY(QColor childBgHoverColor READ getChildBgHoverColor WRITE setChildBgHoverColor)
    Q_PROPERTY(QColor childTextNormalColor READ getChildTextNormalColor WRITE setChildTextNormalColor)
    Q_PROPERTY(QColor childTextSelectedColor READ getChildTextSelectedColor WRITE setChildTextSelectedColor)
    Q_PROPERTY(QColor childTextHoverColor READ getChildTextHoverColor WRITE setChildTextHoverColor)

    Q_PROPERTY(ExpendMode expendMode READ getExpendMode WRITE setExpendMode)

public:
    //节点展开模式
    enum ExpendMode {
        ExpendMode_SingleClick = 0, //单击模式
        ExpendMode_DoubleClick = 1, //双击模式
        ExpendMode_NoClick = 2,     //不可单击双击
    };

    NavListView(QWidget *parent = 0);
    ~NavListView();

private:
    NavModel *model;                //数据模型
    NavDelegate *delegate;          //数据委托
    QStringList parentItem;         //父节点数据集合
    QList<QStringList> childItem;   //子节点数据

    QString items;                  //节点集合
    bool rightIconVisible;          //右侧图标是否显示
    bool tipVisible;                //是否显示提示信息
    int tipWidth;                   //提示信息宽度

    bool separateVisible;           //是否显示行分隔符
    int separateHeight;             //行分隔符高度
    QColor separateColor;           //行分隔符颜色

    bool lineLeft;                  //是否显示在左侧
    bool lineVisible;               //是否显示线条
    int lineWidth;                  //线条宽度
    QColor lineColor;               //线条颜色

    bool triangleLeft;              //是否显示在左侧
    bool triangleVisible;           //是否显示三角形
    int triangleWidth;              //三角形宽度
    QColor triangleColor;           //三角形颜色

    int parentIconMargin;           //父节点图标边距
    int parentMargin;               //父节点边距
    int parentFontSize;             //父节点字体大小
    int parentHeight;               //父节点高度
    QColor parentBgNormalColor;     //父节点正常背景色
    QColor parentBgSelectedColor;   //父节点选中背景色
    QColor parentBgHoverColor;      //父节点悬停背景色
    QColor parentTextNormalColor;   //父节点正常文字颜色
    QColor parentTextSelectedColor; //父节点选中文字颜色
    QColor parentTextHoverColor;    //父节点悬停文字颜色

    int childIconMargin;            //子节点图标边距
    int childMargin;                //子节点边距
    int childFontSize;              //子节点字体大小
    int childHeight;                //子节点高度
    QColor childBgNormalColor;      //子节点正常背景色
    QColor childBgSelectedColor;    //子节点选中背景色
    QColor childBgHoverColor;       //子节点悬停背景色
    QColor childTextNormalColor;    //子节点正常文字颜色
    QColor childTextSelectedColor;  //子节点选中文字颜色
    QColor childTextHoverColor;     //子节点悬停文字颜色

    ExpendMode expendMode;          //节点展开模式 单击/双击/禁用

private slots:
    void pressed(const QModelIndex &data);
    void setData(const QStringList &listItems);

public:
    QString getItems()              const;
    bool getRightIconVisible()      const;
    bool getTipVisible()            const;
    int getTipWidth()               const;

    bool getSeparateVisible()       const;
    int getSeparateHeight()         const;
    QColor getSeparateColor()       const;

    bool getLineLeft()              const;
    bool getLineVisible()           const;
    int getLineWidth()              const;
    QColor getLineColor()           const;

    bool getTriangleLeft()          const;
    bool getTriangleVisible()       const;
    int getTriangleWidth()          const;
    QColor getTriangleColor()       const;

    int getParentIconMargin()       const;
    int getParentMargin()           const;
    int getParentFontSize()         const;
    int getParentHeight()           const;
    QColor getParentBgNormalColor() const;
    QColor getParentBgSelectedColor()const;
    QColor getParentBgHoverColor()  const;
    QColor getParentTextNormalColor()const;
    QColor getParentTextSelectedColor()const;
    QColor getParentTextHoverColor()const;

    int getChildIconMargin()        const;
    int getChildMargin()            const;
    int getChildFontSize()          const;
    int getChildHeight()            const;
    QColor getChildBgNormalColor()  const;
    QColor getChildBgSelectedColor()const;
    QColor getChildBgHoverColor()   const;
    QColor getChildTextNormalColor()const;
    QColor getChildTextSelectedColor()const;
    QColor getChildTextHoverColor() const;

    ExpendMode getExpendMode()      const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置节点数据
    void setItems(const QString &items);
    //设置选中指定行
    void setCurrentRow(int row);
    //设置父节点右侧图标是否显示
    void setRightIconVisible(bool rightIconVisible);

    //设置提示信息 是否显示+宽度
    void setTipVisible(bool tipVisible);
    void setTipWidth(int tipWidth);

    //设置行分隔符 是否显示+高度+颜色
    void setSeparateVisible(bool separateVisible);
    void setSeparateHeight(int separateHeight);
    void setSeparateColor(const QColor &separateColor);

    //设置线条 位置+可见+宽度+颜色
    void setLineLeft(bool lineLeft);
    void setLineVisible(bool lineVisible);
    void setLineWidth(int lineWidth);
    void setLineColor(const QColor &lineColor);

    //设置三角形 位置+可见+宽度+颜色
    void setTriangleLeft(bool triangleLeft);
    void setTriangleVisible(bool triangleVisible);
    void setTriangleWidth(int triangleWidth);
    void setTriangleColor(const QColor &triangleColor);

    //设置父节点 图标边距+左侧边距+字体大小+节点高度+颜色集合
    void setParentIconMargin(int parentIconMargin);
    void setParentMargin(int parentMargin);
    void setParentFontSize(int parentFontSize);
    void setParentHeight(int parentHeight);
    void setParentBgNormalColor(const QColor &parentBgNormalColor);
    void setParentBgSelectedColor(const QColor &parentBgSelectedColor);
    void setParentBgHoverColor(const QColor &parentBgHoverColor);
    void setParentTextNormalColor(const QColor &parentTextNormalColor);
    void setParentTextSelectedColor(const QColor &parentTextSelectedColor);
    void setParentTextHoverColor(const QColor &parentTextHoverColor);

    //设置子节点 图标边距+左侧边距+字体大小+节点高度+颜色集合
    void setChildIconMargin(int childIconMargin);
    void setChildMargin(int childMargin);
    void setChildFontSize(int childFontSize);
    void setChildHeight(int childHeight);
    void setChildBgNormalColor(const QColor &childBgNormalColor);
    void setChildBgSelectedColor(const QColor &childBgSelectedColor);
    void setChildBgHoverColor(const QColor &childBgHoverColor);
    void setChildTextNormalColor(const QColor &childTextNormalColor);
    void setChildTextSelectedColor(const QColor &childTextSelectedColor);
    void setChildTextHoverColor(const QColor &childTextHoverColor);

    //设置节点展开模式
    void setExpendMode(const ExpendMode &expendMode);

Q_SIGNALS:
    void pressed(const QString &text, const QString &parentText);
    void pressed(int index, int parentIndex);
    void pressed(int childIndex);
};

#endif // NAVLISTVIEW_H
