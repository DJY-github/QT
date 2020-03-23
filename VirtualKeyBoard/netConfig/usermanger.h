#ifndef USERMANGER_H
#define USERMANGER_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class userManger;
}

class userManger : public QDialog
{
    Q_OBJECT

public:
    explicit userManger(QWidget *parent = 0);
    ~userManger();
signals:


private slots:
    void on_pushButtonConfirm_clicked();

private:
    Ui::userManger *ui;
    QSqlTableModel *model;
};

#endif // USERMANGER_H
