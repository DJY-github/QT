#include <QtCore>
#include "SoftKeyBoardContext.h"

SoftKeyBoardContext::SoftKeyBoardContext(QWidget * parent)
{
    keyboardSize_ = QSize(1188,420);
    windowsSize_ = parent->size();
    keyboard_ = new SoftKeyBoard(parent);
    connect(keyboard_, SIGNAL(characterGenerated(int)), SLOT(sendCharacter(int)));
}

SoftKeyBoardContext::~SoftKeyBoardContext()
{
}

bool SoftKeyBoardContext::filterEvent(const QEvent* event)
{
    if (event->type() == QEvent::RequestSoftwareInputPanel)
    {
        updatePosition();
        keyboard_->show();
        return true;
    }
    else if (event->type() == QEvent::CloseSoftwareInputPanel)
    {
        keyboard_->hide();
        return true;
    }
    return false;
}

QString SoftKeyBoardContext::identifierName()
{
    return "SoftKeyBoardContext";
}

void SoftKeyBoardContext::reset()
{

}

bool SoftKeyBoardContext::isComposing() const
{
    return false;
}

QString SoftKeyBoardContext::language()
{
    return "en_US";
}

void SoftKeyBoardContext::sendCharacter(int key)
{
    QPointer<QWidget> w = focusWidget();
    if (w)
    {
        QKeyEvent keyPress(QEvent::KeyPress, key, Qt::NoModifier, QString(key));
        QApplication::sendEvent(w, &keyPress);
    }
}

void SoftKeyBoardContext::updatePosition()
{
    QWidget *widget = focusWidget();
    if (!widget)
        return;
    QRect rect = widget->geometry();
    keyboard_->move(rect.left(), rect.bottom());
}
