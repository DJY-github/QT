#ifndef FRMNAV_H
#define FRMNAV_H

#include <QWidget>

namespace Ui {
class frmNav;
}

class frmNav : public QWidget
{
    Q_OBJECT

public:
    explicit frmNav(QWidget *parent = 0);
    ~frmNav();

private:
    Ui::frmNav *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMNAV_H
