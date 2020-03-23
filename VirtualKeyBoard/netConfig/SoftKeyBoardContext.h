#ifndef SOFTKEYBOARDCONTEXT_H
#define SOFTKEYBOARDCONTEXT_H

#include <QtGui/QInputContext>
#include "SoftKeyBoard.h"
#include <QDebug>

class MainWindow;

class SoftKeyBoardContext : public QInputContext
{
    Q_OBJECT

public:
    SoftKeyBoardContext(QWidget * parent);
    ~SoftKeyBoardContext();

    bool filterEvent(const QEvent* event);
    QString identifierName();
    QString language();
    bool isComposing() const;
    void reset();

private slots:
    void sendCharacter(int key);

private:
    void updatePosition();

private:
    SoftKeyBoard *keyboard_;
    /**
     * @brief keyboardSize_ 键盘界面的大小
     */
    QSize keyboardSize_;
    /**
     * @brief windowsSize_ 整个窗口的大小 1920*1080
     */
    QSize windowsSize_;
};

#endif 
