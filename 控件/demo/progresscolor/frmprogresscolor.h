#ifndef FRMPROGRESSCOLOR_H
#define FRMPROGRESSCOLOR_H

#include <QWidget>

namespace Ui
{
class frmProgressColor;
}

class frmProgressColor : public QWidget
{
	Q_OBJECT

public:
	explicit frmProgressColor(QWidget *parent = 0);
	~frmProgressColor();

private:
	Ui::frmProgressColor *ui;

private slots:
    void initForm();
};

#endif // FRMPROGRESSCOLOR_H
