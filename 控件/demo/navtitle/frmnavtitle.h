#ifndef FRMNAVTITLE_H
#define FRMNAVTITLE_H

#include <QWidget>

class NavTitle;

namespace Ui
{
class frmNavTitle;
}

class frmNavTitle : public QWidget
{
    Q_OBJECT

public:
    explicit frmNavTitle(QWidget *parent = 0);
    ~frmNavTitle();

private:
    Ui::frmNavTitle *ui;

private slots:
    void initForm();
    void mousePressed(int index);
    void mouseReleased(int index);

};

#endif // FRMNAVTITLE_H
