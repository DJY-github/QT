#ifndef FRMPINYIN_H
#define FRMPINYIN_H

#include <QWidget>

namespace Ui {
class frmPinYin;
}

class frmPinYin : public QWidget
{
    Q_OBJECT

public:
    explicit frmPinYin(QWidget *parent = 0);
    ~frmPinYin();

private:
    Ui::frmPinYin *ui;

private slots:
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
};

#endif // FRMPINYIN_H
