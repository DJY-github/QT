#ifndef FRMGAUGEWEATHER_H
#define FRMGAUGEWEATHER_H

#include <QWidget>

namespace Ui {
class frmGaugeWeather;
}

class frmGaugeWeather : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeWeather(QWidget *parent = 0);
    ~frmGaugeWeather();

private:
    Ui::frmGaugeWeather *ui;

private slots:
    void initForm();
    void on_horizontalSlider1_valueChanged(int value);
    void on_horizontalSlider2_valueChanged(int value);
    void on_comboBox_currentIndexChanged(int index);
    void on_ckAnimation_stateChanged(int arg1);
};

#endif // FRMGAUGEWEATHER_H
