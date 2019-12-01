#ifndef FRMOVENTIMER_H
#define FRMOVENTIMER_H

#include <QWidget>

namespace Ui
{
class frmOvenTimer;
}

class frmOvenTimer : public QWidget
{
	Q_OBJECT

public:
    explicit frmOvenTimer(QWidget *parent = 0);
    ~frmOvenTimer();

private:
    Ui::frmOvenTimer *ui;

private slots:
    void initForm();
};

#endif // FRMOVENTIMER_H
