#ifndef FRMGAUGECOLOR_H
#define FRMGAUGECOLOR_H

#include <QWidget>

namespace Ui {
class frmGaugeColor;
}

class frmGaugeColor : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeColor(QWidget *parent = 0);
    ~frmGaugeColor();

private:
    Ui::frmGaugeColor *ui;

private slots:
    void initForm();
    void on_cboxPointerStyle_currentIndexChanged(int index);
    void on_ckAnimation_stateChanged(int arg1);
};

#endif // FRMGAUGECOLOR_H
