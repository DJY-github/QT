#ifndef FRMCUSTOMPIE_H
#define FRMCUSTOMPIE_H

#include <QWidget>

namespace Ui {
class frmCustomPie;
}

class frmCustomPie : public QWidget
{
    Q_OBJECT

public:
    explicit frmCustomPie(QWidget *parent = 0);
    ~frmCustomPie();

private:
    Ui::frmCustomPie *ui;

private slots:
    void initForm();
};

#endif // FRMCUSTOMPIE_H
