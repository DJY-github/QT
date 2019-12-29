#ifndef FRMNAVPROGRESS_H
#define FRMNAVPROGRESS_H

#include <QWidget>

namespace Ui
{
class frmNavProgress;
}

class frmNavProgress : public QWidget
{
	Q_OBJECT

public:
	explicit frmNavProgress(QWidget *parent = 0);
	~frmNavProgress();

private:
	Ui::frmNavProgress *ui;

private slots:
	void initForm();
};

#endif // FRMNAVPROGRESS_H
