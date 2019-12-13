#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QDialog>

#include <QButtonGroup>
#include <QList>
#include <QLineEdit>

namespace Ui {
class KeyBoard;
}

class KeyBoard : public QDialog
{
    Q_OBJECT

public:
    explicit KeyBoard(QWidget *parent = 0, QLineEdit *LineEdit = 0);
    ~KeyBoard();
    QString outputStr;

protected:
    QString findChinese(QString PinYin);
    void setHanziBt();

private slots:
    void on_caps_Bt_clicked();
    void slot_numClicked(QAbstractButton *bt);
    void slot_carClicked(QAbstractButton *bt);
    void slot_hanziBtClicked(QAbstractButton *bt);

    void on_zh_us_Bt_clicked();
    void on_delBt_clicked();
    void on_nextBt_clicked();
    void on_prevBt_clicked();
    void on_closeBt_clicked();

private:
    Ui::KeyBoard *ui;

    bool isCap; // 大小写控制

    QButtonGroup *carGroup;
    QList<QAbstractButton *> carList;
    QList<QAbstractButton *> zhList;

    QStringList zikuList; // 字库一行一行分割

    int pageAll; // 总页数
    int curPage; // 当前页
    QStringList pageList; // 查找出的字符串10个10个分割

    QLineEdit *lineEdit;

    void loadziku(); // 加载中文字库
};

#endif // KEYBOARD_H
