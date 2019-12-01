#ifndef FRMGAUGEDIAL_H
#define FRMGAUGEDIAL_H

#include <QWidget>

namespace Ui {
class frmGaugeDial;
}

class frmGaugeDial : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeDial(QWidget *parent = 0);
    ~frmGaugeDial();

private:
    Ui::frmGaugeDial *ui;

private slots:
    void initForm();
    void on_cboxPointerStyle_currentIndexChanged(int index);
    void on_ckShowValue_stateChanged(int arg1);
};

#endif // FRMGAUGEDIAL_H
