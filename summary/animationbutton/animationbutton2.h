﻿#ifndef ANIMATIONBUTTON2_H
#define ANIMATIONBUTTON2_H

/**
 * 动画图片按钮控件 作者:feiyangqingyun(QQ:517216493) 2016-10-16
 * 本控件来源于网络(原作者:what951006(http://blog.csdn.net/what951006/article/details/51542497))
 * 1:可设置普通状态图片
 * 2:可设置进入状态图片
 * 3:可设置离开状态图片
 * 4:按照比例自动居中绘制
 */

#include <QWidget>
#include <QVariant>

class QPropertyAnimation;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT AnimationButton2 : public QWidget
#else
class AnimationButton2 : public QWidget
#endif

{
	Q_OBJECT
    Q_PROPERTY(QString normalImage READ getNormalImage WRITE setNormalImage)
    Q_PROPERTY(QString enterImage READ getEnterImage WRITE setEnterImage)
    Q_PROPERTY(QString leaveImage READ getLeaveImage WRITE setLeaveImage)

public:
	explicit AnimationButton2(QWidget *parent = 0);
	~AnimationButton2();

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void paintEvent(QPaintEvent *);

private:
	bool enter;                         //是否进入
	bool leave;                         //是否离开
	int enterIndex;                     //进入图片索引
	int leaveIndex;                     //离开图片索引

	QPropertyAnimation *enterAnimation; //进入动画
	QPropertyAnimation *leaveAnimation; //离开动画

	QList<QPixmap> listPixEnter;        //进入图片队列
	QList<QPixmap> listPixLeave;        //离开图片队列
	QPixmap pixNormal;                  //默认图片

	QString normalImage;                //默认状态图片地址
	QString enterImage;                 //进入状态图片地址
	QString leaveImage;                 //离开状态图片地址

private slots:
	void enterImageChanged(QVariant index);
	void leaveImageChanged(QVariant index);

public:
    QString getNormalImage()        const;
    QString getEnterImage()         const;
    QString getLeaveImage()         const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
	//设置普通状态图片
	void setNormalImage(QString normalImage);
	//设置进入状态图片
	void setEnterImage(QString enterImage);
	//设置离开状态图片
	void setLeaveImage(QString leaveImage);
};

#endif // ANIMATIONBUTTON2_H
