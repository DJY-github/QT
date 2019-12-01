#ifndef FRMCOLORBUTTON_H
#define FRMCOLORBUTTON_H

#include <QWidget>

namespace Ui {
class frmColorButton;
}

class frmColorButton : public QWidget
{
    Q_OBJECT

public:
    explicit frmColorButton(QWidget *parent = 0);
    ~frmColorButton();

private:
    Ui::frmColorButton *ui;
    QFont iconFont;

private slots:
    void initForm();
};

#endif // FRMCOLORBUTTON_H
