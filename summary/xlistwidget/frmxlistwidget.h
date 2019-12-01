#ifndef FRMXLISTWIDGET_H
#define FRMXLISTWIDGET_H

#include <QWidget>

namespace Ui
{
class frmXListWidget;
}

class frmXListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmXListWidget(QWidget *parent = 0);
    ~frmXListWidget();

private:
    Ui::frmXListWidget *ui;

private slots:
    void initForm();
    void itemClicked(int index, const QString &text);
    void menuClicked(const QString &text);
};

#endif // FRMXLISTWIDGET_H
