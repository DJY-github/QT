#ifndef FRMIMAGEANIMATION_H
#define FRMIMAGEANIMATION_H

#include <QWidget>

namespace Ui {
class frmImageAnimation;
}

class frmImageAnimation : public QWidget
{
    Q_OBJECT

public:
    explicit frmImageAnimation(QWidget *parent = 0);
    ~frmImageAnimation();

protected:
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *);

private:
    Ui::frmImageAnimation *ui;

private slots:
    void initForm();
    void on_cboxType_activated(int index);
};

#endif // FRMIMAGEANIMATION_H
