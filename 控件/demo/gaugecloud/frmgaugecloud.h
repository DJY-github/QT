#ifndef FRMGAUGECLOUD_H
#define FRMGAUGECLOUD_H

#include <QWidget>

namespace Ui {
class frmGaugeCloud;
}

class frmGaugeCloud : public QWidget
{
    Q_OBJECT

public:
    explicit frmGaugeCloud(QWidget *parent = 0);
    ~frmGaugeCloud();

private:
    Ui::frmGaugeCloud *ui;

private slots:
    void initForm();

    //鼠标按下的区域,共9个,从0-8依次表示底部/左下角/左侧/左上角/顶部/右上角/右侧/右下角/中间
    void mousePressed(int position);
    //鼠标松开
    void mouseReleased(int position);
};

#endif // FRMGAUGEARC2_H
