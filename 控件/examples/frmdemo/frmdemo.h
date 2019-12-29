#ifndef FRMDEMO_H
#define FRMDEMO_H

#include <QWidget>

namespace Ui {
class frmDemo;
}

class frmDemo : public QWidget
{
    Q_OBJECT

public:
    explicit frmDemo(QWidget *parent = 0);
    ~frmDemo();

private:
    Ui::frmDemo *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMDEMO_H
