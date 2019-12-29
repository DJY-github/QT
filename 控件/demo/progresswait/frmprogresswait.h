#ifndef FRMPROGRESSWAIT_H
#define FRMPROGRESSWAIT_H

#include <QWidget>

namespace Ui
{
class frmProgressWait;
}

class frmProgressWait : public QWidget
{
	Q_OBJECT

public:
    explicit frmProgressWait(QWidget *parent = 0);
    ~frmProgressWait();

private:
    Ui::frmProgressWait *ui;

private slots:
    void initForm();
};

#endif // frmProgressWait_H
