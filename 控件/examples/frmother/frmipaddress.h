#ifndef FRMADDRESS_H
#define FRMADDRESS_H

#include <QWidget>

namespace Ui {
class frmIPAddress;
}

class frmIPAddress : public QWidget
{
    Q_OBJECT

public:
    explicit frmIPAddress(QWidget *parent = 0);
    ~frmIPAddress();

private:
    Ui::frmIPAddress *ui;

private:
    void setSystemDateTime(const QString &year, const QString &month, const QString &day,
                           const QString &hour, const QString &min, const QString &sec);

private slots:
    void initForm();
    void on_btnSetIP_clicked();
    void on_btnGetIP_clicked();
    void on_btnClear_clicked();
    void on_btnSetDate_clicked();
    void on_btnSetTime_clicked();
    void on_btnSetDateTime_clicked();
};

#endif // FRMADDRESS_H
