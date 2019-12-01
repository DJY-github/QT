#ifndef FRMCOLORPANELFADER_H
#define FRMCOLORPANELFADER_H

#include <QWidget>

namespace Ui {
class frmColorPanelFader;
}

class frmColorPanelFader : public QWidget
{
    Q_OBJECT

public:
    explicit frmColorPanelFader(QWidget *parent = 0);
    ~frmColorPanelFader();

private:
    Ui::frmColorPanelFader *ui;

private slots:
    void colorChanged(const QColor &color, double hue, double sat, double bright);
};

#endif // FRMCOLORPANELFADER_H
