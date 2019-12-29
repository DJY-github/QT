#ifndef FRMANTLINE_H
#define FRMANTLINE_H

#include <QWidget>

namespace Ui
{
class frmAntLine;
}

class frmAntLine : public QWidget
{
	Q_OBJECT

public:
    explicit frmAntLine(QWidget *parent = 0);
    ~frmAntLine();

private:
    Ui::frmAntLine *ui;

private slots:
	void initForm();
};

#endif // FRMANTLINE_H
