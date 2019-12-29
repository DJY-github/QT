#ifndef FRMSWITCHBUTTON_H
#define FRMSWITCHBUTTON_H

#include <QWidget>

namespace Ui
{
class frmSwitchButton;
}

class frmSwitchButton : public QWidget
{
	Q_OBJECT

public:
	explicit frmSwitchButton(QWidget *parent = 0);
	~frmSwitchButton();

private:
	Ui::frmSwitchButton *ui;

private slots:
    void initForm();
    void initBtn1();
    void initBtn2();
    void initBtn3();
};

#endif // frmSwitchButton_H
