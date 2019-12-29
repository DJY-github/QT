#ifndef FRMSLIDER_H
#define FRMSLIDER_H

#include <QWidget>

namespace Ui {
class frmSlider;
}

class frmSlider : public QWidget
{
    Q_OBJECT

public:
    explicit frmSlider(QWidget *parent = 0);
    ~frmSlider();

private:
    Ui::frmSlider *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMSLIDER_H
