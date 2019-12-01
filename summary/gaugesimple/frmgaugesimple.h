#ifndef FRMGAUGESIMPLE_H
#define FRMGAUGESIMPLE_H

#include <QWidget>

namespace Ui {
class frmGaugeSimple;
}

class frmGaugeSimple : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeSimple(QWidget *parent = 0);
    ~frmGaugeSimple();

private:
    Ui::frmGaugeSimple *ui;

private slots:
    void initForm();
    void on_cboxPointerStyle_currentIndexChanged(int index);
    void on_ckAnimation_stateChanged(int arg1);
};

#endif // FRMGAUGESIMPLE_H
