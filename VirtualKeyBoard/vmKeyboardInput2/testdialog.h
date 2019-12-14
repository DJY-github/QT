#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QWidget>

namespace Ui {
class testDialog;
}

class testDialog : public QWidget
{
    Q_OBJECT

public:
    explicit testDialog(QWidget *parent = 0);
    ~testDialog();

private:
    Ui::testDialog *ui;
};

#endif // TESTDIALOG_H
