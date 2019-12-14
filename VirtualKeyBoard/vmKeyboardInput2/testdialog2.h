#ifndef TESTDIALOG2_H
#define TESTDIALOG2_H

#include <QDialog>

namespace Ui {
class testDialog2;
}

class testDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit testDialog2(QWidget *parent = 0);
    ~testDialog2();

private:
    Ui::testDialog2 *ui;
};

#endif // TESTDIALOG2_H
