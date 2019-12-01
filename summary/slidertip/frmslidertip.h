#ifndef FRMSLIDERTIP_H
#define FRMSLIDERTIP_H

#include <QWidget>

namespace Ui
{
class frmSliderTip;
}

class frmSliderTip : public QWidget
{
	Q_OBJECT

public:
    explicit frmSliderTip(QWidget *parent = 0);
    ~frmSliderTip();

private:
    Ui::frmSliderTip *ui;

private slots:
    void initForm();
};

#endif // FRMSLIDERTIP_H
