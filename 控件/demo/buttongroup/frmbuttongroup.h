#ifndef FRMBUTTONGROUP_H
#define FRMBUTTONGROUP_H

#include <QWidget>
class QButtonGroup;
namespace Ui {
class frmButtonGroup;
}

class frmButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit frmButtonGroup(QWidget *parent = 0);
    ~frmButtonGroup();

private:
    Ui::frmButtonGroup *ui;

private slots:
    void initForm();
    void setIndex();

};

#endif // FRMBUTTONGROUP_H
