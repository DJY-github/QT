#pragma execution_character_set("utf-8")

#include "oventimer.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdatetime.h"
#include "qmath.h"
#include "qpixmap.h"
#include "qdebug.h"

const double DegreesPerMinute = 7.0;
const double DegreesPerSecond = DegreesPerMinute / 60;
const int MaxMinutes = 45;
const int MaxSeconds = MaxMinutes * 60;
const int UpdateInterval = 1;

OvenTimer::OvenTimer(QWidget *parent) : QWidget(parent)
{
    finishTime = QDateTime::currentDateTime();

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));

    finishTimer = new QTimer(this);
    finishTimer->setSingleShot(true);
    connect(finishTimer, SIGNAL(timeout()), this, SIGNAL(timeout()));
    connect(finishTimer, SIGNAL(timeout()), updateTimer, SLOT(stop()));

    setFont(QFont("Arial", 8));
}

OvenTimer::~OvenTimer()
{
    if (updateTimer->isActive()) {
        updateTimer->stop();
    }

    if (finishTimer->isActive()) {
        finishTimer->stop();
    }
}

void OvenTimer::mousePressEvent(QMouseEvent *event)
{
    QPointF point = event->pos() - rect().center();
    double theta = qAtan2(-point.x(), point.y()) * 180.0 / M_PI;
    setDuration(getDuration() + int(theta / DegreesPerSecond));    
}

void OvenTimer::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setViewport((width - side) / 2, (height - side) / 2, side, side);
    painter.setWindow(-50, -50, 100, 100);
    draw(&painter);
}

void OvenTimer::draw(QPainter *painter)
{
    static const int triangle[3][2] = {
        {-2, -49}, {+2, -49}, {0, -47}
    };

    QPen thickPen(palette().foreground(), 1.5);
    QPen thinPen(palette().foreground(), 0.5);

    painter->setPen(thinPen);
    painter->setBrush(palette().foreground());
    painter->drawPolygon(QPolygon(3, &triangle[0][0]));

    QConicalGradient coneGradient(0, 0, -90.0);
    coneGradient.setColorAt(0.0, Qt::darkGray);
    coneGradient.setColorAt(0.5, Qt::white);
    coneGradient.setColorAt(1.0, Qt::darkGray);

    painter->setBrush(coneGradient);
    painter->drawEllipse(-46, -46, 92, 92);

    QRadialGradient haloGradient(0, 0, 20, 0, 0);
    haloGradient.setColorAt(0.0, Qt::lightGray);
    haloGradient.setColorAt(0.8, Qt::darkGray);
    haloGradient.setColorAt(0.9, Qt::white);
    haloGradient.setColorAt(1.0, Qt::black);

    painter->setPen(Qt::NoPen);
    painter->setBrush(haloGradient);
    painter->drawEllipse(-20, -20, 40, 40);

    QLinearGradient knobGradient(-7, -25, 7, -25);
    knobGradient.setColorAt(0.0, Qt::black);
    knobGradient.setColorAt(0.3, Qt::lightGray);
    knobGradient.setColorAt(0.8, Qt::white);
    knobGradient.setColorAt(1.0, Qt::black);

    painter->setPen(Qt::NoPen);
    painter->setBrush(knobGradient);
    painter->rotate(getDuration()*DegreesPerSecond);
    painter->drawRoundedRect(-7, -25, 14, 50, 10, 10);

    for (int i = 0; i <= MaxMinutes; ++i) {
        painter->save();
        painter->rotate(-i * DegreesPerMinute);

        if (i % 5 == 0) {
            painter->setPen(thickPen);
            painter->drawLine(0, -41, 0, -44);
            painter->drawText(-15, -41, 30, 30, Qt::AlignHCenter | Qt::AlignTop, QString::number(i));
        } else {
            painter->setPen(thinPen);
            painter->drawLine(0, -42, 0, -44);
        }

        painter->restore();
    }
}

int OvenTimer::getDuration() const
{
    int secs = QDateTime::currentDateTime().secsTo(finishTime);
    if (secs < 0) {
        secs = 0;
    }
    return secs;
}

QSize OvenTimer::sizeHint() const
{
    return QSize(200, 200);
}

QSize OvenTimer::minimumSizeHint() const
{
    return QSize(50, 50);
}

void OvenTimer::setDuration(int secs)
{
    secs = qBound(0, secs, MaxSeconds);

    finishTime = QDateTime::currentDateTime().addSecs(secs);
    if (secs > 0) {
        updateTimer->start(UpdateInterval * 1000);
        finishTimer->start(secs * 1000);
    } else {
        updateTimer->stop();
        finishTimer->stop();
    }

    update();
}
