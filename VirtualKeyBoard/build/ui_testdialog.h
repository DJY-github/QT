/********************************************************************************
** Form generated from reading UI file 'testdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTDIALOG_H
#define UI_TESTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testDialog
{
public:
    QLineEdit *lineEdit;

    void setupUi(QWidget *testDialog)
    {
        if (testDialog->objectName().isEmpty())
            testDialog->setObjectName(QStringLiteral("testDialog"));
        testDialog->resize(400, 300);
        lineEdit = new QLineEdit(testDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(50, 60, 108, 25));
        lineEdit->setFocusPolicy(Qt::ClickFocus);

        retranslateUi(testDialog);

        QMetaObject::connectSlotsByName(testDialog);
    } // setupUi

    void retranslateUi(QWidget *testDialog)
    {
        testDialog->setWindowTitle(QApplication::translate("testDialog", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class testDialog: public Ui_testDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
