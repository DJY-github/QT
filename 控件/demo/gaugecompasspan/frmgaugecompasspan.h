#ifndef FRMGAUGECOMPASSPAN_H
#define FRMGAUGECOMPASSPAN_H

#include <QWidget>

namespace Ui {
class frmGaugeCompassPan;
}

class frmGaugeCompassPan : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeCompassPan(QWidget *parent = 0);
    ~frmGaugeCompassPan();

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::frmGaugeCompassPan *ui;
};

#endif // FRMGAUGECOMPASSPAN_H
