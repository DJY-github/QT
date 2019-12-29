#ifndef FRMGAUGEDECIBEL_H
#define FRMGAUGEDECIBEL_H

#include <QWidget>

namespace Ui {
class frmGaugeDecibel;
}

class frmGaugeDecibel : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeDecibel(QWidget *parent = 0);
    ~frmGaugeDecibel();
    void initForm();

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::frmGaugeDecibel *ui;
};

#endif // FRMGAUGEDECIBEL_H
