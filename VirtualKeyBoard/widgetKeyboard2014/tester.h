#ifndef TESTER_H
#define TESTER_H

#include <QWidget>
#include "keyboard/widgetKeyBoard.h"
#include "examplemyfocus.h"


namespace Ui
{
    class Tester;
}

class Tester : public QWidget
{
    Q_OBJECT

public:
    Tester(QWidget *parent = 0);
    ~Tester();

private:    
    Ui::Tester      *ui;
    widgetKeyBoard  *myKeyboard;

protected:
    //
    // override:
    void closeEvent(QCloseEvent * event);

private slots:
    //void on_Tester_destroyed();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
};

#endif // TESTER_H
