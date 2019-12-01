#ifndef FRMGAUGE_H
#define FRMGAUGE_H

#include <QWidget>

namespace Ui {
class frmGauge;
}

class frmGauge : public QWidget
{
    Q_OBJECT

public:
    explicit frmGauge(QWidget *parent = 0);
    ~frmGauge();

private:
    Ui::frmGauge *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMGAUGE_H
