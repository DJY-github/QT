#ifndef FRMGAUGEMINI_H
#define FRMGAUGEMINI_H

#include <QWidget>

class GaugeMini;
class QLabel;

namespace Ui {
class frmGaugeMini;
}

class frmGaugeMini : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeMini(QWidget *parent = 0);
    ~frmGaugeMini();

private:
    Ui::frmGaugeMini *ui;
    QList<GaugeMini *> gauges;
    QList<QLabel *> labs;

private slots:
    void initForm();
    void valueChanged(double value);

private slots:
    void on_ckDouble_stateChanged(int arg1);
    void on_cboxPointerStyle_currentIndexChanged(int index);
};

#endif // FRMGAUGEMINI_H
