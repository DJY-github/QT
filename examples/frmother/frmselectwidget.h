#ifndef FRMSELECTWIDGET_H
#define FRMSELECTWIDGET_H

#include <QWidget>

class SelectWidget;

namespace Ui {
class frmSelectWidget;
}

class frmSelectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmSelectWidget(QWidget *parent = 0);
    ~frmSelectWidget();

private:
    Ui::frmSelectWidget *ui;
    QList<SelectWidget *> selectWidgets;

private slots:
    void initForm();
    void clearFocus();
    void widgetPressed(QWidget *widget);
    void widgetRelease(QWidget *widget);
};

#endif // FRMSELECTWIDGET_H
