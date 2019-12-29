#ifndef FRMPANELITEM_H
#define FRMPANELITEM_H

#include <QWidget>

class PanelItem;

namespace Ui {
class frmPanelItem;
}

class frmPanelItem : public QWidget
{
    Q_OBJECT

public:
    explicit frmPanelItem(QWidget *parent = 0);
    ~frmPanelItem();

private:
    Ui::frmPanelItem *ui;
    QList<PanelItem *> items;

private slots:
    void initForm();

private slots:
    void on_btnDisable_clicked();
    void on_btnEnable_clicked();
    void on_btnAlarm_clicked();
    void on_btnNormal_clicked();
    void on_cboxAlignment_activated(int index);
    void on_cboxColor_activated(int index);
};

#endif // FRMPANELITEM_H
