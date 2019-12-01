#ifndef FRMWAVEDATA_H
#define FRMWAVEDATA_H

#include <QWidget>

namespace Ui {
class frmWaveData;
}

class frmWaveData : public QWidget
{
    Q_OBJECT

public:
    explicit frmWaveData(QWidget *parent = 0);
    ~frmWaveData();

private:
    Ui::frmWaveData *ui;

private slots:
    void initForm();
};

#endif // FRMWAVEDATA_H
