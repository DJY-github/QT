#ifndef FRMGAUGEPROGRESS_H
#define FRMGAUGEPROGRESS_H

#include <QWidget>

class GaugeProgress;

namespace Ui {
class frmGaugeProgress;
}

class frmGaugeProgress : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeProgress(QWidget *parent = 0);
    ~frmGaugeProgress();

private:
    Ui::frmGaugeProgress *ui;
    QList<GaugeProgress *> gauges;

private slots:
    void initForm();
    void on_ckShowPointer_stateChanged(int arg1);
    void on_ckShowValue_stateChanged(int arg1);
    void on_cboxPointerStyle_currentIndexChanged(int index);
};

#endif // FRMGAUGEPROGRESS_H
