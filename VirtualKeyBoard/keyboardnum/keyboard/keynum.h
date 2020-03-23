#ifndef KEYNUM_H
#define KEYNUM_H

#include <QWidget>

namespace Ui {
class Keynum;
}

class Keynum : public QWidget
{
    Q_OBJECT

public:
    explicit Keynum(QWidget *parent = 0);
    ~Keynum();

private:
    Ui::Keynum *ui;
};

#endif // KEYNUM_H
