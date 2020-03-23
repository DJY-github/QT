#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

class QCompleter;
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    QString passWord;
    ~Login();
    QCompleter *completer;
signals:
    void passWordIsRight();
private slots:
    void on_pushButtonLogin_clicked();
private:
    Ui::Login *ui;
};


#endif // LOGIN_H


