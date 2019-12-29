#ifndef FRMIMAGE_H
#define FRMIMAGE_H

#include <QWidget>

namespace Ui {
class frmImage;
}

class frmImage : public QWidget
{
    Q_OBJECT

public:
    explicit frmImage(QWidget *parent = 0);
    ~frmImage();

private:
    Ui::frmImage *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMIMAGE_H
