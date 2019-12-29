#ifndef FRMXSLIDER_H
#define FRMXSLIDER_H

#include <QWidget>

namespace Ui
{
class frmXSlider;
}

class frmXSlider : public QWidget
{
	Q_OBJECT

public:
    explicit frmXSlider(QWidget *parent = 0);
    ~frmXSlider();

private:
    Ui::frmXSlider *ui;

private slots:
    void initForm();
};

#endif // FRMXSLIDER_H
