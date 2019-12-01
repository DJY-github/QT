#ifndef FRMWAVE_H
#define FRMWAVE_H

#include <QWidget>

namespace Ui {
class frmWave;
}

class frmWave : public QWidget
{
    Q_OBJECT

public:
    explicit frmWave(QWidget *parent = 0);
    ~frmWave();

private:
    Ui::frmWave *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMWAVE_H
