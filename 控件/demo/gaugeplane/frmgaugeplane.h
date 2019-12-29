#ifndef FRMGAUGEPLANE_H
#define FRMGAUGEPLANE_H

#include <QWidget>

namespace Ui {
class frmGaugePlane;
}

class frmGaugePlane : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugePlane(QWidget *parent = 0);
    ~frmGaugePlane();

private:
    Ui::frmGaugePlane *ui;

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_verticalSlider_valueChanged(int value);
};

#endif // FRMWKBUTTON_H
