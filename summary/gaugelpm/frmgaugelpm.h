#ifndef FRMGAUGELPM_H
#define FRMGAUGELPM_H

#include <QWidget>

namespace Ui {
class frmGaugeLpm;
}

class frmGaugeLpm : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeLpm(QWidget *parent = 0);
    ~frmGaugeLpm();

private:
    Ui::frmGaugeLpm *ui;

private slots:
    void initForm();

};

#endif // FRMGAUGELPM_H
