#ifndef FRMRULERTEMP_H
#define FRMRULERTEMP_H

#include <QWidget>

namespace Ui
{
class frmRulerTemp;
}

class frmRulerTemp : public QWidget
{
	Q_OBJECT

public:
    explicit frmRulerTemp(QWidget *parent = 0);
    ~frmRulerTemp();

private:
    Ui::frmRulerTemp *ui;

private slots:
	void initForm();
    void updateValue();
};

#endif // FRMRULERTEMP_H
