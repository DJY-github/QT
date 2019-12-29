#ifndef FRMPROGRESSBUTTON_H
#define FRMPROGRESSBUTTON_H

#include <QWidget>

namespace Ui
{
class frmProgressButton;
}

class frmProgressButton : public QWidget
{
	Q_OBJECT

public:
    explicit frmProgressButton(QWidget *parent = 0);
    ~frmProgressButton();

private:
    Ui::frmProgressButton *ui;

private slots:
    void initForm();
};

#endif // FRMPROGRESSBUTTON_H
