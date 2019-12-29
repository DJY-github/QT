#ifndef FRMRULERPROGRESS_H
#define FRMRULERPROGRESS_H

#include <QWidget>

namespace Ui
{
class frmRulerProgress;
}

class frmRulerProgress : public QWidget
{
	Q_OBJECT

public:
    explicit frmRulerProgress(QWidget *parent = 0);
    ~frmRulerProgress();

private:
    Ui::frmRulerProgress *ui;

private slots:
    void initForm();
    void valueChanged(double value);
};

#endif // FRMRULERPROGRESS_H
