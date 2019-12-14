/********************************************************************************
** Form generated from reading UI file 'vitrualkeyboard.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VITRUALKEYBOARD_H
#define UI_VITRUALKEYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vitrualkeyboard
{
public:
    QLineEdit *lineEdit;
    QDateTimeEdit *dateTimeEdit;
    QDateEdit *dateEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *vitrualkeyboard)
    {
        if (vitrualkeyboard->objectName().isEmpty())
            vitrualkeyboard->setObjectName(QStringLiteral("vitrualkeyboard"));
        vitrualkeyboard->resize(800, 480);
        lineEdit = new QLineEdit(vitrualkeyboard);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(110, 70, 113, 26));
        lineEdit->setFocusPolicy(Qt::StrongFocus);
        dateTimeEdit = new QDateTimeEdit(vitrualkeyboard);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(110, 190, 194, 27));
        dateTimeEdit->setFocusPolicy(Qt::WheelFocus);
        dateEdit = new QDateEdit(vitrualkeyboard);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setGeometry(QRect(200, 250, 110, 27));
        dateEdit->setFocusPolicy(Qt::WheelFocus);
        pushButton = new QPushButton(vitrualkeyboard);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(250, 130, 80, 26));
        pushButton_2 = new QPushButton(vitrualkeyboard);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 350, 80, 25));
        pushButton_3 = new QPushButton(vitrualkeyboard);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(320, 360, 80, 25));

        retranslateUi(vitrualkeyboard);

        QMetaObject::connectSlotsByName(vitrualkeyboard);
    } // setupUi

    void retranslateUi(QWidget *vitrualkeyboard)
    {
        vitrualkeyboard->setWindowTitle(QApplication::translate("vitrualkeyboard", "vitrualkeyboard", Q_NULLPTR));
        pushButton->setText(QApplication::translate("vitrualkeyboard", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("vitrualkeyboard", "widget", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("vitrualkeyboard", "dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class vitrualkeyboard: public Ui_vitrualkeyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VITRUALKEYBOARD_H
