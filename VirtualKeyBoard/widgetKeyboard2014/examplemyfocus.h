#ifndef EXAMPLEMYFOCUS_H
#define EXAMPLEMYFOCUS_H

#include <QLineEdit>
#include "keyboard/widgetKeyBoard.h"


class exampleMyFocus : public QLineEdit
{
    private:
        widgetKeyBoard *m_keyBoard;

    public:
        exampleMyFocus(widgetKeyBoard *keyBoard, QWidget *parent = NULL);

    protected:
        void focusInEvent (QFocusEvent * event);
};

#endif // EXAMPLEMYFOCUS_H
