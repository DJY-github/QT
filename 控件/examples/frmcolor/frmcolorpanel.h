#ifndef FRMCOLORPANEL_H
#define FRMCOLORPANEL_H

#include <QWidget>

namespace Ui
{
    class frmColorPanel;
}

class frmColorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit frmColorPanel(QWidget *parent = 0);
    ~frmColorPanel();

private:
    Ui::frmColorPanel *ui;

private slots:
    void initForm();

private slots:
    void colorChangedFader(const QColor &color, double hue, double sat, double bright);
    void colorChangedHSB(const QColor &color, double hue, double sat);
    void colorChangedBar(const QColor &color, double value, double percent);
    void colorChangedBtn(const QColor &color);
    void setColor(const QColor &color);
    void buttonClicked();
};

#endif // FRMCOLORPANEL_H
