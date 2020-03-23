#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "login.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void showSetPage();

private slots:
    void on_pushButton_user_clicked();
    void saveAllButtonClicked();
    void resetButtonClicked();
    void on_pushButtonConfirm_clicked();


private:
    Ui::MainWindow *ui;
    Login *mLogin;
    void uiUserMangerInit();


};

#endif // MAINWINDOW_H
