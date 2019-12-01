#ifndef FRMADSWIDGET2_H
#define FRMADSWIDGET2_H

#include <QWidget>

namespace Ui {
class frmAdsWidget2;
}

class frmAdsWidget2 : public QWidget
{
    Q_OBJECT

public:
    explicit frmAdsWidget2(QWidget *parent = 0);
    ~frmAdsWidget2();

private:
    Ui::frmAdsWidget2 *ui;

private slots:
    void initForm();
    void on_cboxNavPosition_currentIndexChanged(int index);
    void on_cboxNavStyle_currentIndexChanged(int index);
    void on_ckHoverStop_stateChanged(int arg1);
};

#endif // FRMADSWIDGET2_H
