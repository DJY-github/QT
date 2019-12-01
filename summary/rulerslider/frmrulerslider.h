#ifndef FRMRULERSLIDER_H
#define FRMRULERSLIDER_H

#include <QWidget>

namespace Ui
{
class frmRulerSlider;
}

class frmRulerSlider : public QWidget
{
	Q_OBJECT

public:
    explicit frmRulerSlider(QWidget *parent = 0);
    ~frmRulerSlider();

private:
    Ui::frmRulerSlider *ui;

private slots:
    void initForm();
};

#endif // FRMRULERSLIDER_H
