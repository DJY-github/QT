#ifndef FRMRULERLINE_H
#define FRMRULERLINE_H

#include <QWidget>

namespace Ui
{
class frmRulerLine;
}

class frmRulerLine : public QWidget
{
	Q_OBJECT

public:
    explicit frmRulerLine(QWidget *parent = 0);
    ~frmRulerLine();

private:
    Ui::frmRulerLine *ui;

private slots:
    void initForm();
};

#endif // FRMRULERLINE_H
