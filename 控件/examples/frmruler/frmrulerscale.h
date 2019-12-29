#ifndef FRMRULERSCALE_H
#define FRMRULERSCALE_H

#include <QWidget>

namespace Ui
{
class frmRulerScale;
}

class frmRulerScale : public QWidget
{
	Q_OBJECT

public:
    explicit frmRulerScale(QWidget *parent = 0);
    ~frmRulerScale();

private:
    Ui::frmRulerScale *ui;

private slots:
	void initForm();
};

#endif // FRMRULERSCALE_H
