#ifndef FRMCOLORPANELBTN_H
#define FRMCOLORPANELBTN_H

#include <QWidget>

namespace Ui {
class frmColorPanelBtn;
}

class frmColorPanelBtn : public QWidget
{
    Q_OBJECT

public:
    explicit frmColorPanelBtn(QWidget *parent = 0);
    ~frmColorPanelBtn();

private:
    Ui::frmColorPanelBtn *ui;

private slots:
    void colorChanged(const QColor &color);
};

#endif // FRMCOLORPANELBTN_H
