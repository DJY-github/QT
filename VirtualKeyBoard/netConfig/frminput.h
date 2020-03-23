#ifndef FRMINPUT_H
#define FRMINPUT_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QtSql>

namespace Ui
{
    class frmInput;
}

class frmInput : public QWidget
{
    Q_OBJECT

public:
    explicit frmInput(QWidget *parent = 0);
    ~frmInput();

    static frmInput *Instance() {
        if (!_instance) {
            _instance = new frmInput;
        }
        return _instance;
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void contextMenuEvent(QContextMenuEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void focusChanged(QWidget *, QWidget *nowWidget);
    void btn_clicked();             //按键处理
    void change_style();            //切换样式处理

private:
    Ui::frmInput *ui;
    static frmInput *_instance;

    int deskWidth;                  //桌面宽度
    int deskHeight;                 //桌面高度
    int frmWidth;                   //窗体宽度
    int frmHeight;                  //窗体高度

    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下
    void InitStyle();               //初始化无边框窗体
    void InitForm();                //初始化窗体数据
    void InitProperty();            //初始化属性    

    QMenu *menuStyle;               //样式选择右键菜单
    QLineEdit *currentLineEdit;     //当前焦点的文本框
    QString currentType;            //当前输入法类型
    void changeType(QString type);  //改变输入法类型
    void changeLetter(bool isUpper);//改变字母大小写

    QList<QLabel *>labCh;           //汉字标签数组
    QStringList allPY;              //所有拼音链表
    QStringList currentPY;          //当前拼音链表
    int currentPY_index;            //当前拼音索引
    int currentPY_count;            //当前拼音数量
    void selectChinese();           //查询汉字
    void showChinese();             //显示查询到的汉字
    void setChinese(int index);     //设置当前汉字
    void clearChinese();            //清空当前汉字信息

    void changeStyle(QString topColor,QString bottomColor,QString borderColor,QString textColor);

};

#endif // FRMINPUT_H
