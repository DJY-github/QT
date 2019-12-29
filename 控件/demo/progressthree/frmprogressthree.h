#ifndef FRMPROGRESSTHREE_H
#define FRMPROGRESSTHREE_H

#include <QWidget>

namespace Ui
{
class frmProgressThree;
}

class frmProgressThree : public QWidget
{
	Q_OBJECT

public:
    explicit frmProgressThree(QWidget *parent = 0);
    ~frmProgressThree();

private:
    Ui::frmProgressThree *ui;

private slots:
    void initForm();
    void on_horizontalSlider1_valueChanged(int value);
    void on_horizontalSlider2_valueChanged(int value);
    void on_horizontalSlider3_valueChanged(int value);
    void on_ckShowValue_stateChanged(int arg1);
    void on_ckShowPercent_stateChanged(int arg1);
    void on_ckAutoFont_stateChanged(int arg1);    
};

#endif // FRMPROGRESSTHREE_H
