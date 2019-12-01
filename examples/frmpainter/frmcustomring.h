#ifndef FRMCUSTOMRING_H
#define FRMCUSTOMRING_H

#include <QWidget>

namespace Ui {
class frmCustomRing;
}

class frmCustomRing : public QWidget
{
    Q_OBJECT

public:
    explicit frmCustomRing(QWidget *parent = 0);
    ~frmCustomRing();

private:
    Ui::frmCustomRing *ui;

private slots:
    void initForm();
};

#endif // FRMCUSTOMRING_H
