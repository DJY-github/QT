#ifndef FRMGAUGECIRCLE_H
#define FRMGAUGECIRCLE_H

#include <QWidget>

namespace Ui {
class frmGaugeCircle;
}

class frmGaugeCircle : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeCircle(QWidget *parent = 0);
    ~frmGaugeCircle();

private:
    Ui::frmGaugeCircle *ui;

private slots:
    void initForm();
};

#endif // FRMGAUGECIRCLE_H
