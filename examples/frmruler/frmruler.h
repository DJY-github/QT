#ifndef FRMRULER_H
#define FRMRULER_H

#include <QWidget>

namespace Ui {
class frmRuler;
}

class frmRuler : public QWidget
{
    Q_OBJECT

public:
    explicit frmRuler(QWidget *parent = 0);
    ~frmRuler();

private:
    Ui::frmRuler *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMRULER_H
