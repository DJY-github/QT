#ifndef FRMPAINTER_H
#define FRMPAINTER_H

#include <QWidget>

namespace Ui {
class frmPainter;
}

class frmPainter : public QWidget
{
    Q_OBJECT

public:
    explicit frmPainter(QWidget *parent = 0);
    ~frmPainter();

private:
    Ui::frmPainter *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMPAINTER_H
