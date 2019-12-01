#ifndef FRMRULERBAR_H
#define FRMRULERBAR_H

#include <QWidget>

namespace Ui
{
class frmRulerBar;
}

class frmRulerBar : public QWidget
{
	Q_OBJECT

public:
    explicit frmRulerBar(QWidget *parent = 0);
    ~frmRulerBar();

private:
    Ui::frmRulerBar *ui;

private slots:
	void initForm();
    void updateValue();
};

#endif // FRMRULERBAR_H
