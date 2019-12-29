#ifndef FRMCOLORPANELHSB_H
#define FRMCOLORPANELHSB_H

#include <QWidget>

namespace Ui {
class frmColorPanelHSB;
}

class frmColorPanelHSB : public QWidget
{
    Q_OBJECT

public:
    explicit frmColorPanelHSB(QWidget *parent = 0);
    ~frmColorPanelHSB();

private:
    Ui::frmColorPanelHSB *ui;

private slots:
    void colorChangedHSB(const QColor &color, double hue, double sat);
    void colorChangedBar(const QColor &color, double value, double percent);
};

#endif // FRMCOLORPANELHSB_H
