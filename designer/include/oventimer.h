﻿#ifndef OVENTIMER_H
#define OVENTIMER_H

#include <QWidget>
#include <QDateTime>

class QTimer;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT OvenTimer : public QWidget
#else
class OvenTimer : public QWidget
#endif

{
    Q_OBJECT
public:
    OvenTimer(QWidget *parent = 0);
    ~OvenTimer();

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void draw(QPainter *painter);

private:
    int duration;
    QDateTime finishTime;

    QTimer *updateTimer;
    QTimer *finishTimer;

public:
    int getDuration()               const;
    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    void setDuration(int secs);

Q_SIGNALS:
    void timeout();
};

#endif
