#ifndef FRMGAUGECAR_H
#define FRMGAUGECAR_H

#include <QWidget>

namespace Ui {
class frmGaugeCar;
}

class frmGaugeCar : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeCar(QWidget *parent = 0);
    ~frmGaugeCar();

private:
    Ui::frmGaugeCar *ui;

private slots:
    void initForm();
    void on_cboxPieStyle_currentIndexChanged(int index);
    void on_cboxPointerStyle_currentIndexChanged(int index);
    void on_ckAnimation_stateChanged(int arg1);
};

#endif // FRMGAUGECAR_H
