#ifndef FRMTUMBLERDATETIME_H
#define FRMTUMBLERDATETIME_H

#include <QWidget>

namespace Ui {
class frmTumblerDateTime;
}

class frmTumblerDateTime : public QWidget
{
    Q_OBJECT

public:
    explicit frmTumblerDateTime(QWidget *parent = 0);
    ~frmTumblerDateTime();

private:
    Ui::frmTumblerDateTime *ui;

private slots:
    void initForm();
};

#endif // FRMTUMBLERDATETIME_H
