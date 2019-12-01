#ifndef FRMIMAGEPOWER_H
#define FRMIMAGEPOWER_H

#include <QWidget>

namespace Ui {
class frmImagePower;
}

class frmImagePower : public QWidget
{
    Q_OBJECT

public:
    explicit frmImagePower(QWidget *parent = 0);
    ~frmImagePower();

private:
    Ui::frmImagePower *ui;

private slots:
    void initForm();
};

#endif // FRMIMAGEPOWER_H
