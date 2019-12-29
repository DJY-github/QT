#ifndef FRMPROGRESSPERCENT_H
#define FRMPROGRESSPERCENT_H

#include <QWidget>

class ProgressPercent;

namespace Ui {
class frmProgressPercent;
}

class frmProgressPercent : public QWidget
{
    Q_OBJECT

public:
    explicit frmProgressPercent(QWidget *parent = 0);
    ~frmProgressPercent();

private:
    Ui::frmProgressPercent *ui;
    QList<ProgressPercent *> bars;

private slots:
    void initForm();
    void rbtnClick();

private slots:
    void on_ckClockWise_stateChanged(int arg1);
    void on_ckBorderOut_stateChanged(int arg1);
};

#endif // FRMPROGRESSPERCENT_H
