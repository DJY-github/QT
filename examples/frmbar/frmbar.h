#ifndef FRMBAR_H
#define FRMBAR_H

#include <QWidget>

namespace Ui {
class frmBar;
}

class frmBar : public QWidget
{
    Q_OBJECT

public:
    explicit frmBar(QWidget *parent = 0);
    ~frmBar();

private:
    Ui::frmBar *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMBAR_H
