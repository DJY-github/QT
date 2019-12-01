#ifndef FRMTEXTWRITE_H
#define FRMTEXTWRITE_H

#include <QWidget>

namespace Ui
{
class frmTextWrite;
}

class frmTextWrite : public QWidget
{
	Q_OBJECT

public:
	explicit frmTextWrite(QWidget *parent = 0);
	~frmTextWrite();

private:
	Ui::frmTextWrite *ui;
	QString content;
	int len;

private slots:
    void initForm();
	void changeText();
};

#endif // FRMTEXTWRITE_H
