#ifndef FRMANIMATIONBUTTON_H
#define FRMANIMATIONBUTTON_H

#include <QWidget>

namespace Ui {
class frmAnimationButton;
}

class frmAnimationButton : public QWidget
{
    Q_OBJECT

public:
    explicit frmAnimationButton(QWidget *parent = 0);
    ~frmAnimationButton();

private:
    Ui::frmAnimationButton *ui;

private slots:
    void initForm();
};

#endif // FRMANIMATIONBUTTON_H
