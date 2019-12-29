#include "frmmagicpoolfish.h"
#include "ui_frmmagicpoolfish.h"
#include "magicfish.h"
#include "qevent.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

frmMagicPoolFish::frmMagicPoolFish(QWidget *parent) : QWidget(parent), ui(new Ui::frmMagicPoolFish)
{
    ui->setupUi(this);
    this->initForm();
}

frmMagicPoolFish::~frmMagicPoolFish()
{
    if (timerMove->isActive()) {
        timerMove->stop();
    }

    delete ui;
}

bool frmMagicPoolFish::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->magicPool) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            posPress = mouseEvent->pos();
            moveStep = 0.0;

            QPointF fish_middle = fish->geometry().center();
            QPointF fish_head = fish->geometry().topLeft() + fish->getHeadPos();

            double angle = calcAngle(fish_middle, fish_head, posPress);
            double delta = calcAngle(fish_middle, fish_middle + QPointF(1, 0), fish_head);

            QPointF c = calcPoint(fish_middle, 17 * fish->getHeadLen(), angle / 2 + delta);
            QPointF p(fish->width() / 2, fish->height() / 2);

            path = QPainterPath();
            path.moveTo(this->fish->geometry().topLeft());
            path.cubicTo(fish_head - p, c - p, this->posPress - p);

            fish->setFinMove(true);
            fish->setWave(2.5);
            timerMove->start();
        }
    }

    return QWidget::eventFilter(watched, event);
}

double frmMagicPoolFish::getLength(const QPointF &pos1, const QPointF &pos2)
{
    return qSqrt((pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) + (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()));
}

double frmMagicPoolFish::calcAngle(const QPointF &center, const QPointF &head, const QPointF &touch)
{
    double offset = (head.x() - center.x()) * (touch.x() - center.x()) + (head.y() - center.y()) * (touch.y() - center.y());
    double cos = (offset) / qSqrt((head.x() - center.x()) * (head.x() - center.x()) + (head.y() - center.y()) * (head.y() - center.y())) /
                 qSqrt((touch.x() - center.x()) * (touch.x() - center.x()) + (touch.y() - center.y()) * (touch.y() - center.y()));
    double angle = qRadiansToDegrees(qAcos(cos));

    double direction = (center.x() - touch.x()) * (head.y() - touch.y()) - (center.y() - touch.y()) * (head.x() - touch.x());
    if(direction == 0) {
        return (offset >= 0 ? 0 : 180);
    } else {
        return (direction > 0 ? -angle : angle);
    }
}

QPointF frmMagicPoolFish::calcPoint(const QPointF &pos, double length, double angle)
{
    double x = qCos(qDegreesToRadians(angle)) * length;
    double y = qSin(qDegreesToRadians(angle - 180)) * length;
    return QPointF(pos + QPointF(x, y));
}

double frmMagicPoolFish::qDegreesToRadians(double degrees)
{
    return degrees * double(M_PI / 180);
}

double frmMagicPoolFish::qRadiansToDegrees(double radians)
{
    return radians * double(180 / M_PI);
}

void frmMagicPoolFish::initForm()
{
    ui->magicPool->installEventFilter(this);

    //实例化小鱼作为鼠标跟踪对象
    fish = new MagicFish(ui->magicPool);
    fish->setFixedSize(100, 100);

    //启动定时器移动对象
    timerMove = new QTimer(this);
    timerMove->setInterval(20);
    connect(timerMove, SIGNAL(timeout()), this, SLOT(updateMove()));
}

void frmMagicPoolFish::updateMove()
{
    //更新小鱼的坐标,产生游动效果
    double tmp = 0.00;
    if(moveStep >= 0.85) {
        tmp = qSin(qDegreesToRadians(moveStep * 180)) * 0.02;
        fish->setFinMove(false);
        fish->setWave(1.0);
    } else {
        tmp = 0.015 + qCos(qDegreesToRadians(moveStep * 90)) * 0.02;
        fish->setWave(1.0 / (moveStep + 0.1));
    }

    moveStep += tmp;
    if(moveStep >= 1.0 || (1 - moveStep) <= 0.003) {
        moveStep = 0.0;
        path = QPainterPath();
        timerMove->stop();
    } else {
        QPointF p = path.pointAtPercent(moveStep);
        double angle = path.angleAtPercent(moveStep);
        fish->setCurrentAngle(angle);
        fish->move(p.x(), p.y());
    }
}
