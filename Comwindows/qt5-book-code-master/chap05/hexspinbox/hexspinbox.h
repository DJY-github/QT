#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QSpinBox>

QT_BEGIN_NAMESPACE
class QRegExpValidator;
QT_END_NAMESPACE

class HexSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    HexSpinBox(QWidget *parent = 0);

protected:
    QValidator::State validate(QString &text, int &pos) const;
    int valueFromText(const QString &text) const;
    QString textFromValue(int value) const;

private:
    QRegExpValidator *validator;
};

#endif
