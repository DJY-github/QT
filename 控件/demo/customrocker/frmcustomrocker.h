#ifndef FRMCUSTOMROCKER_H
#define FRMCUSTOMROCKER_H

#include <QWidget>

namespace Ui {
class frmCustomRocker;
}

class frmCustomRocker : public QWidget
{
    Q_OBJECT

public:
    explicit frmCustomRocker(QWidget *parent = 0);
    ~frmCustomRocker();

private:
    Ui::frmCustomRocker *ui;

private slots:
    void moveAngle(double angle);
    void on_ckOnline_stateChanged(int arg1);
};

#endif // FRMCUSTOMROCKER_H
