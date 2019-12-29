#ifndef FRMGAUGEPERCENT_H
#define FRMGAUGEPERCENT_H

#include <QWidget>

namespace Ui {
class frmGaugePercent;
}

class frmGaugePercent : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugePercent(QWidget *parent = 0);
    ~frmGaugePercent();

private:
    Ui::frmGaugePercent *ui;

private slots:
    void initForm();
};

#endif // FRMGAUGEPERCENT_H
