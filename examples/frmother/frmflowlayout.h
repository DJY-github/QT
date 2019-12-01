#ifndef FRMFLOWLAYOUT_H
#define FRMFLOWLAYOUT_H

#include <QWidget>

namespace Ui {
class frmFlowLayout;
}

class frmFlowLayout : public QWidget
{
    Q_OBJECT

public:
    explicit frmFlowLayout(QWidget *parent = 0);
    ~frmFlowLayout();

private:
    Ui::frmFlowLayout *ui;

private slots:
    void initForm();
};

#endif // FRMFLOWLAYOUT_H
