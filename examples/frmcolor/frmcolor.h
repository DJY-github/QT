#ifndef FRMCOLOR_H
#define FRMCOLOR_H

#include <QWidget>

namespace Ui {
class frmColor;
}

class frmColor : public QWidget
{
    Q_OBJECT

public:
    explicit frmColor(QWidget *parent = 0);
    ~frmColor();

private:
    Ui::frmColor *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMCOLOR_H
