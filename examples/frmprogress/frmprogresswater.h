#ifndef FRMPROGRESSWATER_H
#define FRMPROGRESSWATER_H

#include <QWidget>

namespace Ui {
class frmProgressWater;
}

class frmProgressWater : public QWidget
{
    Q_OBJECT

public:
    explicit frmProgressWater(QWidget *parent = 0);
    ~frmProgressWater();

private:
    Ui::frmProgressWater *ui;

private slots:
    void initForm();

private slots:
    void on_sliderBorderWidth_valueChanged(int value);
    void on_sliderWaterHeight_valueChanged(int value);
    void on_sliderWaterDensity_valueChanged(int value);
    void on_ckReverse_stateChanged(int arg1);
    void on_cboxPercentStyle_currentIndexChanged(const QString &arg1);
    void on_btnPause_clicked();
};

#endif // FRMPROGRESSWATER_H
