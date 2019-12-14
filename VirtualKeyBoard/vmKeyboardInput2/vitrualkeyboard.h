#ifndef VITRUALKEYBOARD_H
#define VITRUALKEYBOARD_H

#include <QWidget>
#include "testdialog.h"
#include "testdialog2.h"
namespace Ui {
class vitrualkeyboard;
}

class vitrualkeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit vitrualkeyboard(QWidget *parent = 0);
    ~vitrualkeyboard();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::vitrualkeyboard *ui;
    testDialog *test;
};

#endif // VITRUALKEYBOARD_H
