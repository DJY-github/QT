#ifndef FRMPROGRESSPLAY_H
#define FRMPROGRESSPLAY_H

#include <QWidget>

namespace Ui
{
class frmProgressPlay;
}

class frmProgressPlay : public QWidget
{
	Q_OBJECT

public:
    explicit frmProgressPlay(QWidget *parent = 0);
    ~frmProgressPlay();

private:
    Ui::frmProgressPlay *ui;

private slots:
    void initForm();
    void on_horizontalSlider1_valueChanged(int value);
    void on_horizontalSlider2_valueChanged(int value);
    void on_horizontalSlider3_valueChanged(int value);
};

#endif // FRMPROGRESSPLAY_H
