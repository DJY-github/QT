#ifndef FRMTELWIDGET_H
#define FRMTELWIDGET_H

#include <QWidget>

namespace Ui {
class frmTelWidget;
}

class frmTelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmTelWidget(QWidget *parent = 0);
    ~frmTelWidget();

private:
    Ui::frmTelWidget *ui;

private slots:
    void initForm();
    void telClicked(const QString &name, const QString &type, const QString &tel);
    void on_btnAdd_clicked();
};

#endif // FRMTELWIDGET_H
