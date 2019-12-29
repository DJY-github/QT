#ifndef FRMOTHER_H
#define FRMOTHER_H

#include <QWidget>

namespace Ui {
class frmOther;
}

class frmOther : public QWidget
{
    Q_OBJECT

public:
    explicit frmOther(QWidget *parent = 0);
    ~frmOther();

private:
    Ui::frmOther *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMOTHER_H
