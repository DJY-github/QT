#ifndef FRMMAGICMOUSE_H
#define FRMMAGICMOUSE_H

#include <QWidget>

namespace Ui {
class frmMagicMouse;
}

class frmMagicMouse : public QWidget
{
    Q_OBJECT

public:
    explicit frmMagicMouse(QWidget *parent = 0);
    ~frmMagicMouse();

private:
    Ui::frmMagicMouse *ui;

private slots:
    void initForm();
};

#endif // FRMMAGICMOUSE_H
