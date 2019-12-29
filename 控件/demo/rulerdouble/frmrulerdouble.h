#ifndef FRMRULERDOUBLE_H
#define FRMRULERDOUBLE_H

#include <QWidget>

namespace Ui
{
class frmRulerDouble;
}

class frmRulerDouble : public QWidget
{
	Q_OBJECT

public:
    explicit frmRulerDouble(QWidget *parent = 0);
    ~frmRulerDouble();

private:
    Ui::frmRulerDouble *ui;

private slots:
	void initForm();
};

#endif // FRMRULERDOUBLE_H
