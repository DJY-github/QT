#ifndef FRMNAVBAR_H
#define FRMNAVBAR_H

#include <QWidget>

class NavBar;

namespace Ui
{
class frmNavBar;
}

class frmNavBar : public QWidget
{
	Q_OBJECT

public:
    explicit frmNavBar(QWidget *parent = 0);
    ~frmNavBar();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::frmNavBar *ui;

private slots:
	void initForm();
    void setIndex();
};

#endif // FRMNAVBAR_H
