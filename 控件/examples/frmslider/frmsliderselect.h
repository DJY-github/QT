#ifndef FRMSLIDERSELECT_H
#define FRMSLIDERSELECT_H

#include <QWidget>

class SliderSelect;

namespace Ui
{
class frmSliderSelect;
}

class frmSliderSelect : public QWidget
{
	Q_OBJECT

public:
    explicit frmSliderSelect(QWidget *parent = 0);
    ~frmSliderSelect();

private:
    Ui::frmSliderSelect *ui;
    QList<SliderSelect *> sliders;

private slots:
    void initForm();

private slots:
    void valueChanged(int leftValue, int rightValue);
    void rangeChanged(int rangeValue);
};

#endif // FRMSLIDERSELECT_H
