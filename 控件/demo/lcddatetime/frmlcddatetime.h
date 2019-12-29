#ifndef FRMLCDDATETIME_H
#define FRMLCDDATETIME_H

#include <QWidget>

namespace Ui
{
class frmLcdDateTime;
}

class frmLcdDateTime : public QWidget
{
	Q_OBJECT

public:
    explicit frmLcdDateTime(QWidget *parent = 0);
    ~frmLcdDateTime();

private:
    Ui::frmLcdDateTime *ui;

private slots:
    void initForm();
};

#endif // FRMLCDDATETIME_H
