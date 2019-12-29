#ifndef FRMMAGICPOOLFISH_H
#define FRMMAGICPOOLFISH_H

#include <QWidget>

class MagicFish;

namespace Ui
{
    class frmMagicPoolFish;
}

class frmMagicPoolFish : public QWidget
{
    Q_OBJECT

public:
    explicit frmMagicPoolFish(QWidget *parent = 0);
    ~frmMagicPoolFish();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::frmMagicPoolFish *ui;

    MagicFish *fish;            //魔法鱼
    QPoint posPress;            //按下处的坐标
    QPainterPath path;          //移动的路径

    double moveStep;            //每次移动的步长
    QTimer *timerMove;          //移动定时器

private:
    double getLength(const QPointF &pos1, const QPointF &pos2);
    double calcAngle(const QPointF &center, const QPointF &head, const QPointF &touch);
    QPointF calcPoint(const QPointF &pos, double length, double angle);
    double qDegreesToRadians(double degrees);
    double qRadiansToDegrees(double radians);

private slots:
    void initForm();
    void updateMove();
};

#endif // FRMMAGICPOOLFISH_H
