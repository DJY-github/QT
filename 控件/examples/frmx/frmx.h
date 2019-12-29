#ifndef FRMX_H
#define FRMX_H

#include <QWidget>

namespace Ui {
class frmX;
}

class frmX : public QWidget
{
    Q_OBJECT

public:
    explicit frmX(QWidget *parent = 0);
    ~frmX();

private:
    Ui::frmX *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMX_H
