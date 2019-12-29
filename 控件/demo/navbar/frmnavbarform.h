#ifndef FRMNAVBARFORM_H
#define FRMNAVBARFORM_H

#include <QWidget>

namespace Ui
{
class frmNavBarForm;
}

class frmNavBarForm : public QWidget
{
	Q_OBJECT

public:
    explicit frmNavBarForm(QWidget *parent = 0);
    ~frmNavBarForm();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmNavBarForm *ui;

private slots:
	void initForm();
    void currentItemChanged(int index, const QString &item);
    void setIndex();
};

#endif // FRMNAVBARFORM_H
