#ifndef FRMGAUGEPANEL_H
#define FRMGAUGEPANEL_H

#include <QWidget>

namespace Ui {
class frmGaugePanel;
}

class frmGaugePanel : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugePanel(QWidget *parent = 0);
    ~frmGaugePanel();

private:
    Ui::frmGaugePanel *ui;

private slots:
    void initForm();
    void on_horizontalSlider3_valueChanged(int value);
};

#endif // FRMGAUGEPANEL_H
