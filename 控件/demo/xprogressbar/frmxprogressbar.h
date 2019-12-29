#ifndef FRMXPROGRESSBAR_H
#define FRMXPROGRESSBAR_H

#include <QWidget>

namespace Ui
{
class frmXProgressBar;
}

class frmXProgressBar : public QWidget
{
	Q_OBJECT

public:
    explicit frmXProgressBar(QWidget *parent = 0);
    ~frmXProgressBar();

private:
    Ui::frmXProgressBar *ui;

private slots:
    void initForm();
    void on_horizontalSlider_valueChanged(int value);
};

#endif // FRMXPROGRESSBAR_H
