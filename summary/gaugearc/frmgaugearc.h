#ifndef FRMGAUGEARC_H
#define FRMGAUGEARC_H

#include <QWidget>

namespace Ui {
class frmGaugeArc;
}

class frmGaugeArc : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeArc(QWidget *parent = 0);
    ~frmGaugeArc();

private:
    Ui::frmGaugeArc *ui;

private slots:
    void initForm();
    void on_cboxPointerStyle_currentIndexChanged(int index);
    void on_ckAnimation_stateChanged(int arg1);
};

#endif // FRMGAUGEARC_H
