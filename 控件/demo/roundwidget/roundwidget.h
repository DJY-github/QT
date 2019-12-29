﻿#ifndef ROUNDWIDGET_H
#define ROUNDWIDGET_H

/**
 * 旋转圆窗体 作者:feiyangqingyun(QQ:517216493) 2016-11-22
 */

#include <QWidget>
#include <QHash>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT RoundWidget : public QWidget
#else
class RoundWidget : public QWidget
#endif

{
	Q_OBJECT
public:
	explicit RoundWidget(QWidget *parent = 0);
    ~RoundWidget();

protected:
	void resizeEvent(QResizeEvent *);
	void showEvent(QShowEvent *);

private:
	QHash<int, QWidget *> widgets;
	QWidget *w1;
	QWidget *w2;
	QWidget *w3;
	QWidget *w4;
	QWidget *w5;
	QWidget *w6;

    QTimer *timer;

	int radius;
	int circle;
	int offset;

private slots:
	void initWidget();
	void updateValue();

public:
    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;
};

#endif // ROUNDWIDGET_H
