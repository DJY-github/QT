/********************************************************************************
** Form generated from reading UI file 'demo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMO_H
#define UI_DEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Demo
{
public:
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;

    void setupUi(QWidget *Demo)
    {
        if (Demo->objectName().isEmpty())
            Demo->setObjectName(QStringLiteral("Demo"));
        Demo->resize(545, 300);
        lineEdit = new QLineEdit(Demo);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 190, 281, 20));
        lineEdit_2 = new QLineEdit(Demo);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(60, 70, 211, 25));
        lineEdit_3 = new QLineEdit(Demo);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(50, 120, 211, 25));

        retranslateUi(Demo);

        QMetaObject::connectSlotsByName(Demo);
    } // setupUi

    void retranslateUi(QWidget *Demo)
    {
        Demo->setWindowTitle(QApplication::translate("Demo", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Demo: public Ui_Demo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO_H
