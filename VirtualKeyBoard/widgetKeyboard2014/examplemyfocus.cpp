#include "examplemyfocus.h"

exampleMyFocus::exampleMyFocus(widgetKeyBoard *keyBoard, QWidget *parent) : QLineEdit(parent), m_keyBoard(keyBoard)
{
    this->setEchoMode(QLineEdit::Password);
}


void exampleMyFocus::focusInEvent ( QFocusEvent * event )
{
    this->m_keyBoard->focusThis(this); // modifies focus for keyboard
    QLineEdit::focusInEvent(event);    
}
