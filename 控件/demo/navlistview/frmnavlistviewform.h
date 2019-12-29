#ifndef FRMNAVLISTVIEWFORM_H
#define FRMNAVLISTVIEWFORM_H

#include <QWidget>
#include <QModelIndex>

namespace Ui
{
class frmNavListViewForm;
}

class frmNavListViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit frmNavListViewForm(QWidget *parent = 0);
    ~frmNavListViewForm();

private:
    Ui::frmNavListViewForm *ui;

private slots:
    void initForm();

private slots:
    void on_navListView_pressed(const QModelIndex &index);
};

#endif // FRMNAVLISTVIEWFORM_H
