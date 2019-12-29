#ifndef FRMROUNDLOGO_H
#define FRMROUNDLOGO_H

#include <QWidget>

namespace Ui
{
class frmRoundLogo;
}

class frmRoundLogo : public QWidget
{
	Q_OBJECT

public:
    explicit frmRoundLogo(QWidget *parent = 0);
    ~frmRoundLogo();

private:
    Ui::frmRoundLogo *ui;

private slots:
	void initForm();
};

#endif // FRMROUNDLOGO_H
