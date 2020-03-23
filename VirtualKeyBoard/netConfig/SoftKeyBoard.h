
#ifndef SOFTKEYBOARD_H
#define SOFTKEYBOARD_H

#include <QtGui>
#include <QtCore>
#include <QPoint>
#include <QPushButton>
#include <map>
#include <vector>
#include "ui_SoftKeyBoard.h"

class SoftKeyBoard : public QWidget
{
    Q_OBJECT

public:
    SoftKeyBoard(QWidget * parent);

signals:
    void characterGenerated(int character);

protected:
    bool event(QEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private slots:
    void saveFocusWidget(QWidget *oldFocus, QWidget *newFocus);
    void buttonClicked(QWidget *w);
    void on_btn_caplock__clicked();
    void on_btn_shift__clicked();

private:
    //初始化字库
    bool InitChinese();
    bool GetBtnText(QWidget * widget,QString & text,int start,int count);
    void LanguageInit();

private:
    Ui::SoftKeyBoard ui;
    QWidget * m_lastFocusedWidget_;
    QSignalMapper m_signalMapper_;
    QPushButton * m_btns_[65];
    //用于拖动窗口
    QPoint m_ptPress_;
    bool m_bLeftBtnPress_;
    //语言，false:英文，true：中文
    bool m_bIsChinese_;
    bool m_bIsUppercase_;
    bool m_bShiftPressed_;
    //汉字库 key:拼音 value:字
    std::map<QString,std::vector<QString> >m_map_;
    //拼音
    QString m_strPingying_;
    //选中的文字位置
    int m_currentPos_;
    //当前页
    int m_currentPage_;
};
#endif
