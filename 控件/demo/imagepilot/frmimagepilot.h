#ifndef FRMIMAGEPILOT_H
#define FRMIMAGEPILOT_H

#include <QWidget>

namespace Ui {
class frmImagePilot;
}

class frmImagePilot : public QWidget
{
    Q_OBJECT

public:
    explicit frmImagePilot(QWidget *parent = 0);
    ~frmImagePilot();

private:
    Ui::frmImagePilot *ui;

private slots:
    void initForm();
};

#endif // FRMIMAGEPILOT_H
