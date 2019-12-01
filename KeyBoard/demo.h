#ifndef DEMO_H
#define DEMO_H

#include <QWidget>

namespace Ui {
class Demo;
}

class Demo : public QWidget
{
    Q_OBJECT

public:
    explicit Demo(QWidget *parent = 0);
    ~Demo();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::Demo *ui;

    void callKeyBoard();
};

#endif // DEMO_H
