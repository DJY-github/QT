#ifndef FRMLIGHTPOINT_H
#define FRMLIGHTPOINT_H

#include <QWidget>

class LightPoint;

namespace Ui {
class frmLightPoint;
}

class frmLightPoint : public QWidget
{
    Q_OBJECT

public:
    explicit frmLightPoint(QWidget *parent = 0);
    ~frmLightPoint();

private:
    Ui::frmLightPoint *ui;
    QList<LightPoint *> widgets;

private slots:
    void initForm();
};

#endif // FRMLIGHTPOINT_H
